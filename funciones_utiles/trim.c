#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Funcion que quita el \n y \t del final de una cadena.
void trim(char s[]) {
    size_t l_index;

    for (l_index = (strlen(s) - 1); l_index > 0 && !isgraph(s[l_index]); --l_index)
        ;

    if (l_index >= 0)
        s[++l_index] = '\0';
    else
        printf("Error: Cadena vacia.\n");
}