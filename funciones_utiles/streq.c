#include <stdio.h>
#include <string.h>
#include "trim.c"

// Funcion para comparar dos cadenas. Devuelve 1 si lo son, 0 si no lo son. No considera el \n de la entrada.

int streq(char *s, char *base) {
    size_t i, len_base;
    void trim(char *s);

    len_base = strlen(base);

    trim(s);
    if (strlen(s) == len_base)
        for (i = 0; *s == *base && *s != '\0'; ++i, ++s, ++base)
            ;
    else
        return 0;
            
    if (i == len_base)
        return 1;
    else
        return 0;
}
