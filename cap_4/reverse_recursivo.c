#include <stdio.h>
#include <string.h>

// [a, b, c, d, e, f] ----> Caso par
// 2 (c)     y 2 + 1 (d); 
// 2 - 1 (b) y 2 + 2 (e);
// 2 - 2 (a) y 2 + 3 (f);

// [a, b, c, d, e, f, g] -> Caso impar
//     3 (d)            ;
// 3 - 1 (c) y 3 + 1 (e);
// 3 - 2 (b) y 3 + 2 (f);
// 3 - 3 (a) y 3 + 3 (g);

int reverse(char s[]) {
   int center = (strlen(s) - 1)/2; // Indice central de la cadena.
   static int sep;
   int temp, i, j;

    if (center % 2 == 0) { // Si el arreglo tiene una longitud par

    }
    else { // Si el arreglo tiene una longitud impar

    }   
}

void main() {
    char test[] = "Deberia funcionar la prueba";

    printf("String original:  %s.\n", test);
    reverse(test);
    printf("String revertido: %s.\n\n", test);
}