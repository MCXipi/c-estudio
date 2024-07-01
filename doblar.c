#include <stdio.h>

/*Cada N caracteres agregar un '\n' siempre que el caracter en la posicion N-1 sea una letra.*/

#define MAX 1000
#define N 6 /*Asignacion voluntaria*/

void getline(char[], int);

void getline(char espacio[], int limite) {
    int indice, caracter;

    for (indice = 0; indice < limite - 1 && (caracter = getchar()) != EOF && caracter != '\n'; ++indice){
        if (espacio[indice - 1] != ' ' && espacio[indice - 1] != '\t' && ((indice + 1) % N) == 0) {/*Si el anterior no es espacio en blanco, y la columna en la que se está necesita doblarse*/
            espacio[indice] = '\n';
            ++indice;                       /*Poner el salto de linea y luego el caracter*/
            espacio[indice] = caracter;
        }
        else if (((indice + 1) % N) == 0){
            espacio[indice] = caracter;
            ++indice;                       /*Poner el caracter y luego el salto de linea para hacerlo valido*/
            espacio[indice] = '\n';
        }
        else 
            espacio[indice] = caracter;
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

/*Palabra a testear: "aaaaaaaaaaaaaaaaaaa"*/