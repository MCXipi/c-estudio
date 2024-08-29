#include <stdio.h>

// Escriba una función setbits(x,p,n,y) que regresa x con los n bits
// que principian en la posición p iguales a los n bits más a la derecha de y, dejando
// los otros bits sin cambio.

// Los unicos bits que debo cambiar son los n bits, tomando como referencia los n bits más a la derecha de y. Por eso, los bits que debo trasladar son los de y, o
// habrá perdida de datos en x --> Debo mover a y p - n + 1 bits a la izquierda.

// x = 001 101 01 p = 4, n = 3.
// y = 00011 011. 

// Puedo limpiar a y de los bits que no necesito, con el siguiente procedimiento
// z = 00000 000 0
// y = 00011 011 y

// z = 11111 111 ~0
// y = 00011 011 y

// z = 11111 000 (~0) << n 
// y = 00011 011 y

// z = 00000 111 ~((~0) << n) 
// y = 00011 011 y

// y = y & z = 00000 011 --> & hace que solo si AMBOS son 1, el resultado sea 1. NO que ambos sean iguales.

// Por otro lado, podemos limpiar los bits de X que deben ser reemplazados
// z = 000 000 00
// x = 001 101 01

// z = 111 111 11 ~0
// x = 001 101 01

// z = 111 000 00 (~0) << p + 1
// x = 001 101 01

// z = 000 111 11 ~((~0) << p)
// x = 001 101 01

// z = 000 001 11 (~((~0) << p)) >> p - n + 1
// x = 001 101 01

// z = 000 111 00 ((~((~0) << p)) >> p - n + 1) << p - n + 1
// x = 001 101 01

// z = 111 000 11 ~(((~((~0) << p)) >> p - n + 1) << p - n + 1)
// x = 001 101 01

// z & x = 001 000 01 x ahora limpio.

//ahora se tiene

// y = 000 011 00 (<< p - n + 1)
// x = 001 000 01

// x | y = 001 011 01 el nuevo x.
 

//void main(){
//    int x = 3; // 0000 0011
//    printf("x inicial: %d\n", x);
//    x = x >> 1; // 0000 0001
//    printf("x trasladado uno a la derecha: %d\n", x);
//    x = x << 1; // 0000 0001?
//    printf("x trasladado uno a la izquierda: %d\n", x); // O es 3 devuelta, o es 2. --> Es 2, por ende hay perdida, y para la izquierda no considera un limite.
//}

int setbits(int, int, int, int);

int setbits(x, p, n, y){
    int mask;
    mask = 0; // Funcionará como mascara, para limpiar y arreglar x e y y dejarlos listos.

    mask = ~((~0) << n); // Quedan como 1 las posiciones de bits que queremos mantener intactos
    y = y & mask; // Limpiamos los bits innecesarios y dejamos solo los que buscamos cambiar en X
    y = y << (p - n + 1); // Se colocan los bits a cambiar en posicion

    mask = 0;
    mask = ~((( ~( (~0) << (p + 1) )) >> (p - n + 1) ) << p - n + 1); // Se hace una mascara para limpiar los bits de x a limpiar
    x = mask & x;
 
    x = x | y; // Se ponen los bits de y en x.

    return x;
}

void main(){
    int x, y, p, n;

    p = 4;
    n = 3;
    x = 53; // 00110101
    y = 27; // 00011011
    printf("\nEl numero de bits a modificar es %d, a partir del %d, tomando desde la posicion %d, en un campo de %d bits.\n", x, y, p, n);
    x = setbits(x, p, n, y);
    printf("El nuevo x es: %d.\n", x); // Resultado debe ser 45, 00101101.
}

