#include <stdio.h>
#include <ctype.h>

// Debo retornar la posicion del primer caracter de s1 que esté en s2. Es decir, el indice del arreglo s1 el cual tiene un caracter igual al caracter estudiado en s2.
// Si no hay ninguno en comun debo regresar -1.

int any(char[], char[]);

int any(char s1[], char s2[]) {
    int i, j;

    for (i = 0; s2[i] != '\0'; ++i)
        for (j = 0; s1[j] != '\0'; ++j)
            if (tolower(s1[j]) == tolower(s2[i]))
                return j;
    
    return -1; // Si se sale de los 2 for con exito es porque no hay ninguno en común.
}

void main() {
    int resultado;
    char test1[] = "aloo";
    char test2[] = "dfgghdsfgsdefgo";

    resultado = any(test1, test2);
    if (resultado != -1)
        printf("Indice de caracter comun: %d\n", resultado);
    else
        printf("No hay caracteres en comun. \n");
}