#include <stdio.h>
#include <string.h>

int reverse(char *s) {
    static int pos; // Static pues así comienza en 0, se mantiene tras llamados, y no se inicializa por cada uno de estos.
    int temp;
    int last = (strlen(s) - 1); // Indice del ultimo caracter

    if (pos <= last - pos) { // Si la posicion estudiada desde la izquierda es menor o igual a la estudiada desde el final de la cadena
        temp = *(s + pos);
        *(s + pos) = *(s + last - pos);
        *(s + last - pos) = temp;
        ++pos;
        reverse(s);
    }
    return 0;
}