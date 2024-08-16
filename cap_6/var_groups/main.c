#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "getvar.c"

// Ejercicio 6-2.

#define MAXWORDLEN 100

int main (int argc, char *argv[]) {
    int n, i;
    char var[MAXWORDLEN];

    n = 6; // Valor por defecto.

    if (argc > 2) { // Si hay mas argumentos que los esperados, enviar modo de uso
        printf(".\\vargroups [-n] (0 <= n <= 6)\n");
        return -1;
    }
    else if (argc == 2) { // Si hay dos arguemtnos
        for (i = 1; *(argv[1] + i); ++i) // Para cada caracter en la opcion, pasado el caracter -, si hay mas de un digito, o no es digito, enviar uso.
            if (!isdigit(*(argv[1] + i)) || i > 1) {
                printf(".\\vargroups [-n] (0 <= n <= 6)\n");
                return -1;
            }
        else
            n = atoi(argv[1] + 1); // Si esta bien el argumento, escribir n.
    }

    while (getvar(var, MAXWORDLEN) != NULL) {
        printf("Var = %s\n", var);
    }

    return 0;
}
