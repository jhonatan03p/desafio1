#include <iostream>
#include <fstream>
#include "desencriptado.h"
using namespace std;

void leerarchivo(char* archivo, char* buffer){
    buffer[0] = '\0';

    ifstream arch(archivo, ios::binary);
    if (!arch.is_open()) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    char caracter;
    int pos = 0;

    while (arch.get(caracter) && pos < 3999) {
        if (caracter != '\r') {
            buffer[pos] = caracter;
            pos++;
        }
    }
    buffer[pos] = '\0';

    arch.close();
}

int main() {
    int n;
    cout << "Ingrese la cantidad de archivos a desencriptar:" << endl;
    cin >> n;
    int m=1;
    char encrp[]="EncriptadoX.txt";
    char pista[]="PistaX.txt";


    char contenido1[4000];
    char contenido2[50];

    while (m<=n){
         encrp[10]=m+48; // Numero de archivo encriptado a abrir
         pista[5]=m+48; // Numero de archivo de pista a abrir


        int tam=0;
        leerarchivo(encrp, contenido1);


        for(int i=0;contenido1[i]!='\0';i++){ // definicion de tamano del archivo
            tam++;
        }


        leerarchivo(pista, contenido2);
        bool bandera = false;
        cout<<"WHILEEEEEEE"<<endl;
       for (int key = 0; key <= 255 && !bandera; ++key) { // ciclo con la validacion de claves K
            //cout<<key<<endl;
            for (int var = 0; var < 8; ++var) { // ciclo para rotar los bits
                char* cont=new char[tam+1];
                desencriptar(contenido1,tam,var,key,cont);
                quitar00(cont,tam);
                char* mensaje=descompresionRLE(cont);
                delete[] cont;
                if(estapista(mensaje,contenido2)){
                    cout<<"RLE"<<endl;
                    cout<<"Rotacion:"<< var << endl;
                    cout << "Key: 0x" << hex << key << dec << endl;
                    bandera = true;
                    break;
                }
                delete[] mensaje;
            }
       }
       m++;
    }
    //char* mensaje="3A4B5C1D2R";
    return 0;
}
