#include "desencriptado.h"
#include <iostream>

using namespace std;
char* descompresionRLE(char* comprimido){
    int m ;
    int n=0;
    int tamaño=0;
    int ext=0;

    for (int i=0;comprimido[i]!='\0';i++){
        if (i%2==0){
            ext += (unsigned char)comprimido[i];
        }
    }
       // cout<<ext<<endl;
    char* mensaje = new char[ext + 1];

    for (int i=0;comprimido[i]!='\0';i++){

        if (i%2!=0){
            char caracter=comprimido[i];
            m=0;

            while(m<tamaño){
                mensaje[n]=caracter;
                m++;
                n++;

            }
        }

        else{
           tamaño=(unsigned char)comprimido[i];
        }
    }
    mensaje[n]='\0';
    return mensaje;
}

unsigned char rotarDerecha(unsigned char c, int n) {
    return (c >> n) | (c << (8 - n));
}


void desencriptar(char* buffer,int tam, int n, unsigned char clave) {
    int i = 0;
    while (i<tam) {
        unsigned char c = buffer[i];
        c = c ^ clave;
        c = rotarDerecha(c, n);
        buffer[i] = c;
        i++;
    }
    buffer[tam] = '\0';
}

char* quitar00(char* buffer,int tam){
    //Recordaar liberal cuando se deje de usar!!!
    int j=0;
    char* cadena = new char[tam + 1];

    for (int i=0;i<tam;i++){

        if (buffer[i]!='\0'){
            cadena[j]=buffer[i];
            j++;
        }
    }

    cadena[j]='\0';
    return cadena;
}

bool estapista(char* buffer,char pista[]){
    int tam_pis=0;
    int tam_buffer=0;
    bool match=true;

    for (int i=0;pista[i]!='\0';i++){
        tam_pis++;
    }
    char* comparar=new char[tam_pis+1];
    for (int i=0;buffer[i]!='\0';i++){
        tam_buffer++;
    }
    for (int inicio=0;inicio<=tam_buffer-tam_pis ;inicio++){
        int n=0;
        for (int i=inicio;i<inicio+tam_pis;i++){
            comparar[n]=buffer[i];
            n++;
    }
        comparar[n]='\0';
    char* p = pista;
    char* c = comparar;
    match = true;
    while (*p != '\0') {
        if (*p != *c) {
            match = false;
            break;
        }
        p++;
        c++;
    }
    if(match){
        delete[] comparar;
        return true;
    }
    }

    delete[] comparar;
    return false;
    }
void descomprimirLZ78(Entrada* datos, int n, char* salida, int maxLen) {
    const int MAX_DICT = 4096;        // tamaño máximo del diccionario
    char diccionario[MAX_DICT][256];  // cada cadena máx 255 chars
    int longitudes[MAX_DICT];
    int dictSize = 1; // índice 0 = vacío

    int pos = 0; // posición en salida

    for (int i = 0; i < n; i++) {
        int idx = datos[i].indice;
        unsigned char c = datos[i].caracter;

        if (idx >= dictSize) {
            cerr << "Índice inválido en entrada " << i << endl;
            continue;
        }

        int len = longitudes[idx];
        for (int j = 0; j < len && pos < maxLen - 1; j++) {
            salida[pos++] = diccionario[idx][j];
        }
        if (pos < maxLen - 1) {
            salida[pos++] = c;
        }

        if (dictSize < MAX_DICT) {
            for (int j = 0; j < len; j++) {
                diccionario[dictSize][j] = diccionario[idx][j];
            }
            diccionario[dictSize][len] = c;
            longitudes[dictSize] = len + 1;
            dictSize++;
        }
    }
    salida[pos] = '\0';
}



