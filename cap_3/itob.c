#include <stdio.h>

// Aprender como se representa de decimal a binario o a cualquier otra representacion.
// Debo guardar todos los restos de la division por la base, los cuales son el numero final invertido. Por esto utilizaré la funcion reverse

#define MAX 150
#define LOWER_ASCII 96
#define UPPER_ASCII 64

void reverse(char s[]) {
    int i, temp; // Indice que parte al principio
    size_t j; // Indice que viene del final

    for (i = 0, j = strlen(s) - 2; i < j; ++i, --j) { // strlen - 2 pues strlen - 1 lo vuelve indice, y strlen - 2 no cuenta '\n'
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    } 
}

// Si el resto es un numero mayor a 9 debo comenzar a utilizar las letras de la a a la z

void itob(int num, char s[], int base) {
    int resto, i;

    i = 0;
    do {
        resto = num % base;
        if (resto > 9 && resto - 9 <= 26) 
            resto = UPPER_ASCII + (resto - 9); // El resto mayor a 9 se vuelve el codigo ascii de las letras a-z con a = 10.
        else if (resto > 9 && resto - 9 > 26)
            resto = LOWER_ASCII + (resto - 35); // De esta manera permito una representacion cuya base maxima es 62, ya que el resto que sobrepasa los ASCII mayusculas (resto - 35) pasa a ser minusculas.
        else
            resto += '0';
        s[i++] = resto;
    } while ((num /= base) != 0);

    s[i++] = '\n';
    s[i] = '\0';
    reverse(s);
}

void main() {
    char test_convertido[MAX];
    int test_entero, base;

    test_entero = 516512;
    base = 16; // Una base N necesita N caracteres para su representacion

    itob(test_entero, test_convertido, base);

    printf("El numero original es %d, y el numero convertido a base %d es %s", test_entero, base, test_convertido);
}