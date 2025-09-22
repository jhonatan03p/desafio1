#include <iostream>
#include <fstream>
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
    int n=3;
    int m=1;
    char encrp[]="EncriptadoX.txt";
    char pista[]="PistaX.txt";

    char contenido1[4000];
    char contenido2[50];
    while (m<=n){
        encrp[10]=m+48;
        pista[5]=m+48;

        cout<<encrp<<"   "<<pista<<endl;

        leerarchivo(encrp, contenido1);
        cout << "Encriptado: " << contenido1 << endl;

        leerarchivo(pista, contenido2);
        cout << "Pista: " << contenido2 << endl;

        m++;
    }
    return 0;
}
