#include <stdio.h>

/*Reemplazar los espacios en blancos por la minima cantidad de t y rellenar con blancos*/

#define MAX 1000

void getline(char[], int);

void getline(char espacio[], int limite) {
    int indice, caracter, inicio_comentario, fin_comentario;
    
    for (indice = 0; indice < limite - 1 && (caracter = getchar()) != EOF && caracter != '\n'; ++indice){
        espacio[indice] = caracter;
        if (espacio[indice] == '*' && espacio[indice - 1] == '/') /*Marca el inicio de un comentario*/
            inicio_comentario = indice - 2;
        if (espacio[indice] == '/' && espacio[indice - 1] == '*') /*Si se llega al final del comentario*/
            indice = inicio_comentario;
        
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
