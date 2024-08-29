#include <stdio.h>

#define swap(t, x, y) \
    do {              \
        t temp = x;   \
        x = y;        \
        y = temp;     \
    } while (0)

// Un do {...} while(0) sirve para hacer una ejecucion de una sola vez, en bloque, lo que permite crear una variable automatica temp que no interfiere con nada.

void main() {
    int x, y;
    x = 1;
    y = 0;

    printf("1. x = %d, y = %d\n", x, y);
    swap(int, x, y);
    printf("2. x = %d, y = %d\n", x, y);
}