#include <stdio.h>

// Escriba una función invert(x,p,n) que regresa x con los n bits que
// principian en la posición p invertidos (esto es, 1 cambiado a 0 y viceversa), dejando
// los otros sin cambio.

// Considerando un x -> 11011010 (218), p -> 5, n -> 4, se consideran los bits 11 0110 10, esperando que dé 11100110 (230)

// Debo enmascarar x para limpiar los bits a cambiar, y utilizar un complemento de x y enmascararlo para dejar solo los bits a cambiar.

// mask = 00 0000 00 = 0
// x    = 11 0110 10 = x

// mask = 11 1111 11 = ~0
// x    = 11 0110 10 = x

// mask = 11 1100 00 = (~0) << n
// x    = 11 0110 10 = x

// mask = 00 0011 11 = ~((~0) << n)
// x    = 11 0110 10 = x

// maskA = 00 1111 00 = (~((~0) << n)) << p - n + 1
// x    = 11 0110 10 = x

// maskB = 11 0000 11 = ~((~((~0) << n)) << p - n + 1)
// x    = 11 0110 10 = x

// x = 11 0000 10 = maskB & x

// Luego hacemos lo mismo con el complemento de x

// ~x    = 00 1001 01 
// maskA = 00 1111 00 = (~((~0) << n)) << p - n + 1

// maskA = 00 1001 00 = maskA & ~x

// Finalmente

// x = x | maskA

int invert(int, int, int);

int invert(x, p, n) {
    int clean_out_mask, clean_in_mask, comp;

    clean_out_mask = ~((~0) << n) << (p - n + 1);
    clean_in_mask = ~clean_out_mask;
    comp = ~x;

    x = x & clean_in_mask;
    comp = comp & clean_out_mask;
    x = x | comp;

    return x;
}

void main() {
    int x, p, n;
    x = 183;
    p = 3;
    n = 3;
    printf("\nSe cambiaran los %d bits desde la posicion %d del numero %d\n", n, p, x);
    x = invert(x, p, n);
    printf("El nuevo numero es de %d\n", x);
}
