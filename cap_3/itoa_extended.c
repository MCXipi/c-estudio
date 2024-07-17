#include <stdio.h>
#include <string.h>

#define MAX 150

void reverse(char s[]) {
    int i, temp; // Indice que parte al principio
    size_t j; // Indice que viene del final

    for (i = 0, j = strlen(s) - 2; i < j; ++i, --j) { // strlen - 2 pues strlen - 1 lo vuelve indice, y strlen - 2 no cuenta '\n'
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    } 
}

void itoa_extended(int n, char s[], int b) {
    int i, sign;

    if ((sign = n) < 0)
        n = -(n + 1); 
    
    i = 0;
    do
        s[i++] = n % 10 + '0';
    while ((n /= 10) > 0);

    if (sign < 0) {
        s[i++] = '-';
        ++s[0]; 
    }

    // Comprobare si el numero de elementos es menor al campo minimo b, y si es asi le agregare los espacios en blanco que sean necesarios.
    if (i + 1 < b)
        do
            s[i++] = '0';
        while (i + 1 < b);
        
    s[i++] = '\n';
    s[i] = '\0';
    reverse(s);
}

void main() {
    int test = 6789;
    int b = 10;
    char s[MAX];

    itoa_extended(test, s, b);
    printf("Numero: %d. String: %s", test, s);
}