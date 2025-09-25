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
    int n=1;
    int m=1;
    int* tam_pista=new int;
    char encrp[]="EncriptadoX.txt";
    char pista[]="PistaX.txt";


    char contenido1[4000];
    char contenido2[50];

    while (m<=n){
         encrp[10]=m+48;
         pista[5]=m+48;


        int tam=0;
        leerarchivo(encrp, contenido1);
        for(int i=0;contenido1[i]!='\0';i++){
            tam++;
        }
       char* cont=new char[tam+1];
        leerarchivo(pista, contenido2);

       cout << "Pista: " << contenido2 << endl;
        unsigned char clave =0x5A ;
        desencriptar(contenido1,tam,3,clave);
        cont=quitar00(contenido1,tam);
        cout<<cont<<endl;
        char* mensaje=descompresionRLE(cont);
        delete[] cont;
        cout<<mensaje<<endl;
        if(estapista(mensaje,contenido2)){
            cout<<"esta"<<endl;
        }
        else{
            cout<<"no esta"<<endl;
        }
        m++;

    }
    //char* mensaje="3A4B5C1D2R";
    return 0;
}
