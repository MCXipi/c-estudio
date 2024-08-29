#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Ejercicio 7-1.

int main (int argc, char *argv[]) {
    // Funcion que recibe argumentos de la linea de comandos. Y trata la entrada dependiendo de este.
    // Si el argumento es "lower", toda la entrada la vuelve minuscula y la lleva a la salida
    // Si es "upper" hace la salida mayusculas y la retorna a la salida
    // Si no hay argumentos extras retorna el texto igual, y si hay más argumentos de los necesarios manda error.
    
    int c;

    if (argc == 2)
        if (strcmp(argv[1], "lower") == 0)
            while((c = getchar()) != EOF)
                putchar(tolower(c));
        else if (strcmp(argv[1], "upper") == 0)
            while((c = getchar()) != EOF)
                putchar(toupper(c));
        else
            printf("Error: Argumento %s invalido.\n", argv[1]);

    else if (argc == 1)
        while((c = getchar()) != EOF)
                putchar(c);

    else
        printf("Error: Demasiados argumentos.\n");

    return 0;
}