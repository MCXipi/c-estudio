#include <stdio.h>

// Escriba una función rightrot(x,n) que regresa el valor del entero
// x rotado a la derecha n posiciones de bits. -> Los que salen por la derecha entran por la izquierda.

// Debo guardar los n bits que se irán para la izquierda y volverlos a instalar al final de la secuencia de bits moviendo los n bits guardados una cantidad de l veces
// donde l es el numero de veces que se movio a la derecha el numero original hasta que se volviese un 0.

int rightrot(int, int);

int rightrot(x, n) {
    unsigned int save, l, copy; // Para evitar corrimiento aritmético le pongo unsigned.
    
    copy = x;
    for (l = 0; copy != 0; ++l)
        copy = copy >> 1; // Movemos a la derecha hasta conocer donde está el ultimo 1 del binario, es decir, el largo del binario.

    save = (x & ~((~0) << n)) << (l - n); // Creamos el save, que serán los bits que movimos a la derecha en posicion para ponerse en la izquierda.

    x = (x >> n) | save; // Movemos a x a la derecha las n veces y luego reemplazamos los que se movieron.
    return x;
}

void main() {
    int x, n;
    
    x = 29; // 00011101
    n = 4;
    printf("\nSe rotara %d veces a la derecha el numero %d. \n", n, x);
    x = rightrot(x, n);
    printf("El numero rotado ahora es %d", x); // Deberia dar 27, 00011011
}