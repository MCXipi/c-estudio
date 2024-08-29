#include <stdio.h>

// Experimentación que usé para entender la relacion int - char.

void main() {
    unsigned char unsigned_test = 0; /*Permite almacenar enteros entre 0 y 255*/
    signed char signed_test = 0; /*Permite almacenar enteros entre los vaalores entre -128 a 127*/

    printf("Unsigned as int: %d\n", unsigned_test); // Unsigned char como entero
    printf("Unsigned as char: %c\n", unsigned_test); // Unsigned char como char
    // Almacenar un entero en un char es lo mismo que indicar el codigo ASCII de un caracter al que le sería equivalente. Los digitos del 0 al 9 tienen son un unico caracter y tienen su codigo ASCII, pero numeros mayores al 9 ya son dos caracteres que producen overflow, haciendo que se regrese al inicio de "la cuenta", lo que significa que el char '10' es equivalente a un 0 en ASCII y asi.
    
    printf("Signed as int: %d\n", signed_test); // Signed char como entero
    printf("Signed as char: %c\n", signed_test); // Signed char como entero
    //Los signed char en negativo representan los codigos en ASCII desde el 255 hacia atrás. Si el entero que le coloco es positivo y mayor a 127, el overflow hace que la cuenta se regrese al valor -128 en adelante, después del primer valor aceptado. Finalmente, se podría decir que los valores negativos de los signed char representan en ASCII los caracteres especiales mayores a 127, y los valores positivos representan los caracteres "normales". Logicamente hablando, en unsigned char los caracteres especiales tienen su codigo después de los caracteres normales. En los signed char los caracteres especiales están antes que los caracteres normales en la recta.

    //int i;
    //for (i = 0; i > -255; --i)
        //printf("Signed as int: %d. Signed as char: %c\n", i, i);
}
