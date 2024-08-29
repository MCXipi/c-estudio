#include <stdio.h>

/*Hacer una funcion getline que filtre los '\n' y '\t', y las lineas vacias, y que luego main sea el que imprima*/

#define MAX 100

void getline(char[], int);

void getline(char espacio[], int limite) {
    int i, c, ultimocaracter;
    ultimocaracter = 0; /*Inicializacion para que sea compatible con lineas llenas de espacios*/

    for (i = 0; i < limite - 1 && (c = getchar()) != EOF && c != '\n'; ++i){
        espacio[i] = c;
        if (espacio[i] != '\t' && espacio[i] != ' ')
            ultimocaracter = i;
    }
    if (c == '\n'){
        espacio[i] = c;
        ++i; 
    }
    espacio[i] = '\0';

    if (espacio[ultimocaracter] != ' '){
        espacio[ultimocaracter + 1] = '\n';
        espacio[ultimocaracter + 2] = '\0';
        for (i; i > (ultimocaracter + 2); --i)
            espacio[i] = ' '; /*¿Está bien limpiar asi un puesto del array?*/
    }
    else
        for (i; i >= 0; --i)
            espacio[i] = ' '; /*¿Está bien limpiar asi un puesto del array?*/
}

void main() {
    char palabra[MAX];
    int i;

    getline(palabra, MAX);
    printf("%s", palabra);
}

/*Como puedo comprobar que esto de verdad funciona?*/