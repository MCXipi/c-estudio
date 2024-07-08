#include <stdio.h>

// En un sistema de números de complemento a dos, x & = (x -1 ) borra
// el bit 1 de más a la derecha en x. Explique el porqué. Utilice esta observación
// para escribir una versión más rápida de bitcount.

// Si el numero restado es par, entonces no hay ningun bit activo en la posicion 0 
// equivalente a 2 elevado a 0. En este caso, la resta de 1 lo deja como un numero 
// impar, donde el 1 está en la posicion 0 que es el que suma 1 al numero par. Por 
// el otro lado, un numero impar tiene ese mismo 1 activo en la posicion 0, y cuando 
// se resta un numero 1, pasa a ser par, por lo que se le asigna el 1 a la posicion 
// 1 y se quita de la posicion 0. La expresión como tal deriva en un trabajo binario
// en el cual, por cada operación de esta, un hay un 1 menos en la secuencia de bits.

int bitcount(unsigned int);

bitcount(x) {
    int c;

    for (x; x != 0; x &= (x - 1))
        ++c;
    return c;
}

void main() {
    unsigned int x, n;
    x = 565;
    
    n = bitcount(x);

    printf("\nn: %d\n", n);
}

// 565 1000110101
// 564 1000110100
// 565 & 564 1000110100 = 564 (-1)

// 564 1000110100
// 563 1000110011
// 563 & 564 1000110000 = 560 (-2)

// 560 1000110000
// 559 1000101111 
// 563 & 564 1000100000 = 544 (-3)

// 544 1000100000
// 543 1000011111
// 544 & 543 100000000 = 256

// 256 100000000
// 255 011111111

// 256 & 255 = 00000000

// Dado el numero resultante después del AND, siempre solo habrá 1 bit con 
// diferentes valores entre los numeros. Re loco. Restar 1 siempre cambiará 1 bit, 
// en cambio, tirar para la derecha elimina solamente el bit que está, y por ello se 
// debe comprobar si es 1 o 0.