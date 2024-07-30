#include <stdio.h>

// Funcion getline para utilizar en cualquier archivo. stdio.h tiene una funcion pero para efectos del alcance del libro no las usare.

int saveline(char *s, int lim) {
    int i, c;

    for (i = 0; i < --lim && (c = getchar()) != EOF && c != '\n'; ++i, ++s)
        *s = c;

    if (c == '\n')
        *s = c;
    *++s = '\0';

    return i;
}

// La funcion ademas de obtener una linea devuelve el largo de esta sin contar \n ni \0, haciendo funcion de strlen.