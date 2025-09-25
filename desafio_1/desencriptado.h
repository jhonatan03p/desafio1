#ifndef DESENCRIPTADO_H
#define DESENCRIPTADO_H
struct Entrada {
    int indice;
    unsigned char caracter;
};
char* descompresionRLE(char* comprimido);
void desencriptar(char* buffer,int tam,int n, unsigned char clave);
char* quitar00(char* buffer, int tam);
bool estapista(char* buffer, char pista[]);
void descomprimirLZ78(Entrada* datos,int n,char* salida,int maxLen);
#endif // DESENCRIPTADO_H
