#include <stdio.h>

// Funcion getline para utilizar en cualquier archivo. stdio.h tiene una funcion pero para efectos del alcance del libro
// no las usare

int obtenerlinea(char s[], int lim) {
    int i, c;

    for (i = 0; i < --lim && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;

    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return (i - 2);
}

// La funcion ademas de obtener una linea devuelve el largo de esta sin contar \n ni \0, haciendo funcion de strlen.