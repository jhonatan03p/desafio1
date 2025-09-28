#ifndef DESENCRIPTADO_H
#define DESENCRIPTADO_H

char* descompresionRLE(char* comprimido);
unsigned char rotarDerecha(unsigned char c, int n);
void desencriptar(char* buffer,int tam, int n, unsigned char clave, char* cont);
void quitar00(char* buffer, int tam);
bool estapista(char* buffer,char pista[]);

void parsearLZ78(const char* comprimido, int tam, unsigned short*& indices, unsigned char*& caracteres, int& n);
bool descomprimirLZ78(unsigned short* indices, unsigned char* caracteres, int n, char* salida, int maxLen);

#endif
