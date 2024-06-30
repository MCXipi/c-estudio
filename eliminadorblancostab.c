#include <stdio.h>

/*Hacer una funcion getline que filtre los '\n' y '\t', y las lineas vacias, y que luego main sea el que imprima*/

#define MAX 100

void getline(char[], int);

void getline(char espacio[], int limite){
    int i, c, ultimocaracter, newline_pos, end_pos;
    ultimocaracter = 0; /*Inicializacion para que sea compatible con lineas llenas de espacios*/

    for (i = 0; i < limite - 1 && (c = getchar()) != EOF && c != '\n'; ++i){
        espacio[i] = c;
    }
    if (c == '\n'){
        espacio[i] == c;
        ++i; 
    }
    espacio[i] == '\0';

}