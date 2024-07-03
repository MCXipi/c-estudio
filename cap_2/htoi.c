#include <stdio.h>

// Los caracteres hexadecimales son automaticamente caracteres los cuales se pueden convertir a enteros los cuales debo ir sumando de izquierda a derecha con el metodo que vi, multiplicando por 10 cada vez.

int htoi(char[]);

int htoi(char s[]) {
    int i, n;
    n = 0;

    for (i = 0; s[i] >= '\x30' && s[i] <= '\x57'; ++i)
        n = (n * 10) + (s[i] - '\x30'); // n * 10 le da espacio a esa unidad para que se sume, y s[i] - '\x30' es el entero equivalente a partir de la diferencia del codigo ASCII del digito y el 0.
    
    return n;
}

void main() {
    char test[4] = {'\x37', '\x34', '\x37'};
    printf("Entero equivalente: %d \n", htoi(test));
}

// Terminar: Ver como lo haria si es que viene con 0x.