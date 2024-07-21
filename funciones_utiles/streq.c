#include <stdio.h>
#include <string.h>

// Funcion para comparar dos cadenas. Devuelve 1 si lo son, 0 si no lo son. No considera el \n de la entrada.
void trim(char[]);

int streq(char s[], char base[]) {
    size_t i, len_base;

    len_base = strlen(base);

    trim(s);
    if (strlen(s) == len_base)
        for (i = 0; s[i] == base[i] && s[i] != '\0'; ++i)
            ;
    else
        return 0;
            
    if (i == len_base)
        return 1;
    else
        return 0;
}
