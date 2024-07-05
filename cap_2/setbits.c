#include <stdio.h>

// Escriba una función setbits(x,p,n,y) que regresa x con los n bits
// que principian en la posición p iguales a los n bits más a la derecha de y, dejando
// los otros bits sin cambio.

// Los unicos bits que debo cambiar son los n bits, tomando como referencia los n bits más a la derecha de y. Por eso, los bits que debo trasladar son los de y, o
// habrá perdida de datos en x --> Debo mover a y p - n + 1 bits a la izquierda.

// x = 00110101 p = 4, n = 3.
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

//Para cambiar los bits de x:
// y = 000 011 00 y << p - n + 1
// x = 001 101 01



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
    int z;

    z = ~((~0) << n); // Quedan como 1 las posiciones de bits que queremos mantener intactos
    y = y & z; // Limpiamos los bits innecesarios y dejamos solo los que buscamos cambiar en X
    y = y << (p - n + 1); // Se colocan los bits a cambiar en posicion



    return x;
}

void main(){
    int x, y, p, n;

    p = 4;
    n = 3;
    x = 
    y = 
    x = setbits(x, p, n, y);
    printf("El nuevo x es: %d \n", x); 
}

