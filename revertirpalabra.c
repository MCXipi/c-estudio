#include <stdio.h>

/*Pedir una linea e invertir todos los caracteres*/

#define MAX 100

void getline(char[], int);

void getline(char espacio[], int limite) {
    int i, c, adelanto, retroceso;
    char cache;

    for (i = 0; i < limite - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        espacio[i] = c;
    if (c == '\n'){
        espacio[i] = c;
        retroceso = i - 1;
        ++i; 
    }
    espacio[i] = '\0';
    if (espacio[i - 1] != '\n')
        retroceso = i - 1;

    /*Misma base de siempre. Invertir caracteres*/
    adelanto = 0;
    for (retroceso; adelanto < retroceso; --retroceso){
        cache = espacio[adelanto];
        espacio[adelanto] = espacio[retroceso];
        espacio[retroceso] = cache;
        ++adelanto;
    }
}

void main() {
    char palabra[MAX];
    int i;

    getline(palabra, MAX);
    printf("%s", palabra);
}

