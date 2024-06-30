#include <stdio.h>

/*Reemplazar las tabulaciones con n espacios en blanco señalados por '_', usando la funcion getline y main*/

#define MAX 100
#define N 8

void getline(char[], int);

void getline(char espacio[], int limite) {
    int indice, caracter, paro, reemplazo;

    paro = N;

    for (indice = 0; indice < limite - 1 && (caracter = getchar()) != EOF && caracter != '\n'; ++indice)
        if (caracter != '\t')
            espacio[indice] = caracter;
        else{
            for (reemplazo = indice; reemplazo < limite - 1 && reemplazo < indice + paro; ++reemplazo)
                espacio[indice] = '_';
            indice = reemplazo - 1;
        }

    if (caracter == '\n'){
        espacio[indice] = caracter;
        ++indice;
    }
    espacio[indice] = '\0';
}

void main() {
    char palabra[MAX];

    getline(palabra, MAX);

    printf("%s", palabra);
}