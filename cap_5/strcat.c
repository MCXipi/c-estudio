#include <stdio.h>

// Copiar lo de una cadena t en el final de una cadena s. Avanzar s hasta que sea 0 y luego de eso ir copiando todo lo de la cadena t.

void strcat (char *s, char *t) {
    // while (*s++) Esta escritura incrementa en 1 la direccion s aun cuando *s es nulo. La prueba de while no se detiene inmediatamente cuando falla en algo.
    //    ;

    for (; *s; ++s) // Ignorar todo lo de la cadena s, que no nos importa. En esta escritura no se aumenta s cuando es nulo y se deja s en el nulo.
        ;

    while (*s++ = *t++) // Copiar cada caracter en s hasta que *t == '\0' (NULL). Cuando *t es NULL aun asi se incrementa t en 1, pero no nos importa.
        ;
}

void main () {
    char *test_s = "ABC";
    char *test_t = "DE";
    strcat(test_s, test_t);
    printf("%s\n", test_s);    
}