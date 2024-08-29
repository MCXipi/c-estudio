#include <stdio.h>
#define MAX 1000

int getline(char[], int);

int getline(char stg[], int lim){
    int c, i; /*Para cada caracter y el indice*/

    i = 0;
    while ((c = getchar()) != EOF)
        if (i < lim - 1)
            if (c != '\n') {
                stg[i] = c;   // For sin usar && ni ||
                ++i;
            }
    
    if (c == '\n'){ /*Agrega '\n' al final del arreglo como normalmente habría pasado (?) -> Permite el salir del getchar cuando se termina la palabra de manera natural, sin concatenar palabaras ni necesitar EOF para salir del ciclo.*/
        stg[i] = c;
        ++i; /*Aumenta en uno el indice para agregar el fin del arreglo*/
    }
    stg[i] = '\0'; /*Agrega el fin de linea al arreglo de caracteres*/
    return i; /*Devolver el valor de la longitud absoluta de la palabra*/
}

void main() {
    char palabra[MAX];

    getline(palabra, MAX);

    printf("%s", palabra);
}

