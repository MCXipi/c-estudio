#include <stdio.h>

#define SPACE 20

// Versiones propias de strncpy, strncat, y strncmp del header <string.h> para el ejercicio 5-5.

char *strncat (char *s, const char *ct, int n) {
    int c;

    for (; *s; s++) // Dejo a s en la posicion del caracter nulo de la cadena
        ;
    
    for (c = 0; c < n && (*s = *ct); c++, s++, ct++) // Levar una cuenta de caracteres copiados. Si esta es menor o igual a la cantidad de char a copiar, y lo copiado es algo, continuar
        ;
    
    return s; // Retornar el apuntador
}

char *strncopy (char *s, const char *ct, int n) {
    int c;

    for (c = 0; c < n && (*s = *ct); c++, s++, ct++) // Levar una cuenta de caracteres copiados. Si esta es menor o igual a la cantidad de char a copiar, y lo copiado es algo, continuar
        ;

    if (c < n && !*ct) // Si no se ha logrado copiar los n caracteres deseados
        for (c; c <= n; c++, s++)
            *s = '\0'; // Poner nulos hasta que se logren los n caracteres
        
    return s; //Retornar el apuntador s.
}

int strncmp (const char *cs, const char *ct, int n) {
    int c;

    for (c = 0; c < n && *cs == *ct; c++, cs++, ct++) // Mientras los caracteres sean iguales avanzar en las cadenas, hasta posiblemente alcanzar los n caracteres.
        ;

    if (c < n)  // Si no se han comparado los n caracteres es porque hubo alguna diferencia
        if (*cs < *ct) // Si entre los caracteres diferentes *cs es menor a *ct
            return -1; // Devolver algun numero negativo
        else
            return 1; // Si no, *cs es mayor, por ende, devolver algun positivo
    else
        return 0; // Si c == n, es porque los n caracteres son iguales; devuelve 0.
}

void main() {
    const char *ct = "abc";
    const char *cs = "ab";
    char s[SPACE] = ".abcdef";  
    int result;

    //strncat(s, ct, 2);
    //printf("El resultado de strcat es %s\n", s); // Deberia ser .abcdefab

    //strncopy(s, ct, 2);
    //printf("El resultado de strncopy es %s\n", s); // Deberia ser abbcdef

    result = strncmp(cs, ct, 2);
    printf("El resultado de strncmp es %d\n", result); // Deberia ser 0

}