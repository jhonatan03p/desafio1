#include "desencriptado.h"
#include <iostream>
using namespace std;

char* descompresionRLE(char* comprimido) {
    int m;
    int n = 0;
    int tamaño = 0;
    int ext = 0;

    for (int i = 0; comprimido[i] != '\0'; i++) {
        if (i % 2 == 0) {
            ext += (unsigned char)comprimido[i];
        }
    }

    char* mensaje = new char[ext + 1];

    for (int i = 0; comprimido[i] != '\0'; i++) {
        if (i % 2 != 0) {
            char caracter = comprimido[i];
            m = 0;
            while (m < tamaño) {
                mensaje[n] = caracter;
                m++;
                n++;
            }
        } else {
            tamaño = (unsigned char)comprimido[i];
        }
    }
    mensaje[n] = '\0';
    return mensaje;
}

unsigned char rotarDerecha(unsigned char c, int n) {
    return (c >> n) | (c << (8 - n));
}

void desencriptar(char* buffer, int tam, int n, unsigned char clave, char* cont) {
    for (int i = 0; i < tam; i++) {
        unsigned char c = buffer[i];
        c = c ^ clave;
        c = rotarDerecha(c, n);
        cont[i] = c;
    }
    cont[tam] = '\0';
}

void quitar00(char* buffer, int tam) {
    int j = 0;
    for (int i = 0; i < tam; i++) {
        if (buffer[i] != '\0') {
            buffer[j] = buffer[i];
            j++;
        }
    }
    buffer[j] = '\0';
}

bool estapista(char* buffer, char pista[]) {
    int tam_pis = 0, tam_buffer = 0;
    for (int i = 0; pista[i] != '\0'; i++) tam_pis++;
    for (int i = 0; buffer[i] != '\0'; i++) tam_buffer++;

    for (int inicio = 0; inicio <= tam_buffer - tam_pis; inicio++) {
        bool match = true;
        for (int j = 0; j < tam_pis; j++) {
            if (buffer[inicio + j] != pista[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

// --- PARSEAR Y DESCOMPRIMIR LZ78 ---
void parsearLZ78(const char* comprimido, int tam, unsigned short*& indices, unsigned char*& caracteres, int& n) {
    if (tam < 3) {
        indices = nullptr;
        caracteres = nullptr;
        n = 0;
        return;
    }
    n = tam / 3;
    indices = new unsigned short[n];
    caracteres = new unsigned char[n];

    int k = 0;
    for (int i = 0; i < n; i++) {
        unsigned char b1 = (unsigned char)comprimido[k++];
        unsigned char b2 = (unsigned char)comprimido[k++];
        unsigned short idx = ((unsigned short)b1 << 8) | b2;
        unsigned char c = (unsigned char)comprimido[k++];
        indices[i] = idx;
        caracteres[i] = c;
    }
}

bool descomprimirLZ78(unsigned short* indices, unsigned char* caracteres, int n, char* salida, int maxLen) {
    if (!indices || !caracteres || n <= 0 || !salida) return false;

    int cap = n + 2;
    char** dic = new char*[cap];
    int* largos = new int[cap];

    dic[0] = nullptr;
    largos[0] = 0;
    int dictSize = 1;
    int pos = 0;

    for (int i = 0; i < n; ++i) {
        int idx = indices[i];
        unsigned char c = caracteres[i];
        if (idx < 0 || idx >= dictSize) {
            for (int t = 1; t < dictSize; t++) delete[] dic[t];
            delete[] dic;
            delete[] largos;
            return false;
        }

        int len = largos[idx];
        if (pos + len + 1 >= maxLen) break;

        for (int j = 0; j < len; j++) salida[pos++] = dic[idx][j];
        salida[pos++] = (char)c;

        int newLen = len + 1;
        char* nueva = new char[newLen];
        for (int j = 0; j < len; j++) nueva[j] = dic[idx][j];
        nueva[len] = (char)c;

        dic[dictSize] = nueva;
        largos[dictSize] = newLen;
        dictSize++;
    }

    salida[pos] = '\0';
    for (int t = 1; t < dictSize; t++) delete[] dic[t];
    delete[] dic;
    delete[] largos;
    return true;
}
