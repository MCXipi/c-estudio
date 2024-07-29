#include <stdio.h>

// Regresar 1 si la cadena t está al final de la cadena s. Si no, 0.

int strend(char *s, char *t) {
    char *first = t; // Guardar la direccion del primer caracter de t

    //for (; *s, *t; s++, t++) La coma no hace que hayan "dos for paralelos" y que uno siga mientras el otro ya haya terminado. Deben ser dos aparte.
    //    ;

    for (; *s; s++) 
        ;              // Dejar tanto la direccion t como la s en el caracter NULL (\0)
    for (; *t; t++)
        ;

    for (; t >= first && *s == *t; s--, --t) // Mientras el caracter en la direccion de t y s son iguales, quitar uno a la direccion de s y de t.
        ;

    if (first - 1 == t) // Si los caracteres finales eran iguales, t debio llegar a ser la direccion inicial - 1. En ese caso retorna 1.
        return 1;
    else
        return 0; // Si no, retorna 0.
}

void main () {
    int result;
    char *test_s = "ABCDEF";
    char *test_t = "EF";
    result = strend(test_s, test_t);
    printf("Resultado = %d\n", result);    
}