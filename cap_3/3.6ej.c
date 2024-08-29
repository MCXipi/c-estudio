#include <stdio.h>
#include <string.h>

// itoa versión del libro con una funcion reverse que invierte las palabras

void reverse(char s[]) {
    int i, temp; // Indice que parte al principio
    size_t j; // Indice que viene del final

    for (i = 0, j = strlen(s) - 2; i < j; ++i, --j) { // strlen - 2 pues strlen - 1 lo vuelve indice, y strlen - 2 no cuenta '\n'
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    } 
}

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    
    i = 0;
    do
        s[i++] = n % 10 + '0';
    while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';
    s[i++] = '\n';
    s[i] = '\0';
    reverse(s);
}

void main() {
    int test = 1023456789;
    char s[12];

    itoa(test, s);
    printf("Numero: %d. String: %s", test, s);
}