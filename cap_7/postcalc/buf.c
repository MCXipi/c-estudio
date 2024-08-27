#include <stdio.h>

#define BUFSIZE 100

static double buf[BUFSIZE];
static double *buf_i = buf;

double *push (double n) {
    // Funcion que ingresa double n al buffer de la calculadora
    // Revisa si hay espacio disponible y guarda si hay.
    // Retorna puntero a espacio donde se almacenó, y NULL si no se pudo.

    if (BUFSIZE - (buf_i - buf) > 0) {
        *buf_i++ = n;
        return buf_i - 1;
    }
    else {
        printf("Buffer error - Not enough space.\n");
        return NULL;
    }
}

double pop () {
    // Funcion que obtiene el ultimo elemento en el buffer y lo retorna
    // Verifica si hay al menos un elemento guardado, y lo retorna. Si no, retorna 0.

    if (buf_i > buf)
        return *--buf_i;
    else 
        return 0.0;
}

double getlast () {
    // Funcion que retorna una copia del ultimo elemento en el buffer.
    // Verifica si hay al menos un elemento.

    if (buf_i > buf)
        return *(buf_i - 1);
    else 
        return 0.0;
}