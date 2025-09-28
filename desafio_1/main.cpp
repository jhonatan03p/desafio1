#include <iostream>
#include <fstream>
#include "desencriptado.h"
using namespace std;

int leerarchivo(const char* archivo, char* buffer) {
    ifstream arch(archivo, ios::binary);
    if (!arch.is_open()) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return 0;
    }

    arch.read(buffer, 4000);
    int tam = arch.gcount();
    arch.close();
    return tam;
}

int main() {
    int n;
    cout << "Ingrese la cantidad de archivos a desencriptar:" << endl;
    cin >> n;

    int m = 1;
    char encrp[] = "EncriptadoX.txt";
    char pista[] = "PistaX.txt";

    char contenido1[4000];
    char contenido2[50];

    while (m <= n) {
        encrp[10] = m + 48;  // archivo encriptado
        pista[5] = m + 48;   // archivo de pista

        int tam = leerarchivo(encrp, contenido1);
        int tamPista = leerarchivo(pista, contenido2);

        bool bandera = false;

        for (int key = 0; key <= 256 && !bandera; ++key) {
            for (int var = 0; var < 8; ++var) {
                char* cont = new char[tam + 1];
                desencriptar(contenido1, tam, var, key, cont);

                // --- Primero probamos RLE ---
                char* copia = new char[tam + 1];
                for (int i = 0; i < tam; i++) copia[i] = cont[i];
                copia[tam] = '\0';
                quitar00(copia, tam);

                char* mensajeRLE = descompresionRLE(copia);
                if (estapista(mensajeRLE, contenido2)) {
                    cout <<"======="<<encrp<<"======="<<endl<<mensajeRLE<<endl<<endl;
                    cout << "Descompresion: RLE" << endl;
                    cout << "Rotacion: " << var << endl;
                    cout << "Key: 0x" << hex << key << dec << endl<<endl;
                    bandera = true;
                }
                delete[] mensajeRLE;
                delete[] copia;

                // --- Si aún no se encontró, probamos LZ78 ---
                if (!bandera) {
                    unsigned short* indices = nullptr;
                    unsigned char* caracteres = nullptr;
                    int nEntradas = 0;

                    parsearLZ78(cont, tam, indices, caracteres, nEntradas);

                    if (nEntradas > 0) {
                        char* mensajeLZ = new char[5000]; // buffer de salida
                        if (descomprimirLZ78(indices, caracteres, nEntradas, mensajeLZ, 5000)) {
                            if (estapista(mensajeLZ, contenido2)) {
                                cout <<"======="<<encrp<<"======="<<endl<<mensajeLZ<<endl<<endl;
                                cout << "Descompresion: LZ78" << endl;
                                cout << "Rotacion: " << var << endl;
                                cout << "Key: 0x" << hex << key << dec << endl<<endl;
                                bandera = true;
                            }
                        }
                        delete[] mensajeLZ;
                    }
                    delete[] indices;
                    delete[] caracteres;
                }

                delete[] cont;
                if (bandera) break;
            }
            if (key==256){
                cerr<<encrp<<" no se ha podido desencriptar"<<endl;
            }
        }
        m++;
    }
    return 0;
}
