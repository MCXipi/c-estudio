#include <stdio.h>
#include <string.h>

#define MAX 150
// Debo hacer una funcion que revise desde el fin de la cadena si esta la ultima letra del patron buscado, hacia delante

int obtenerlinea(char s[], int lim);

int strindex(char s[], char t[]) {
    int largo_s, largo_t, i, j, k;

    printf("Ingresa linea a estudiar:\n");
    largo_s = obtenerlinea(s, MAX);
    printf("Ingresa patron a buscar:\n");
    largo_t = obtenerlinea(t, MAX);

    for (i = largo_s; i >= 0; --i) {
        for (j = i, k = largo_t; k >= 0 && t[k] == s[j]; --j, --k)
           ;
        if (k < 0)
            return j + 1;
    }
    return -1; 
}

void killjump(char s[]) {
    size_t i;

    i = strlen(s);
    while(s[i] != '\n')
        --i;
    s[i] = '\0';
}

void main() {
    char linea[MAX];
    char patron[MAX];
    int resultado;

    resultado = strindex(linea, patron);
    killjump(patron);
    printf("El patron %s se encuentra en la posicion %d\n", patron, resultado);
}