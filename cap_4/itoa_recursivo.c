#include <stdio.h>
#include <string.h>

enum bool {FALSE, TRUE};

int itoa(int n, int negative, char s[]) {
    int i;

    if (n < 0) {
        s[0] = '-';
        n = -n;
        negative = TRUE; // Inicialmente negative = FALSE.
    }

    if (n / 10 > 0) { // Si aun es divisible por 10
        s[i = itoa(n / 10, negative, s)] = n % 10 + '0'; // El indice del digito de más a la derecha de n será el que retorna el llamado recursivo para n con un digito de la derecha menos
        s[++i] = '\0';
        return i;
    }
    else { // Si ya solo queda un n de un solo digito,
        (negative) ? (i = 1) : (i = 0); // Si el numero es negativo los indices comenzarán de 1, y si no, desde 0
        s[i] = n % 10 + '0'; // Se coloca el primer digito
        s[++i] = '\0';
        return i; // Se retorna el siguiente indice
    }
}

void main() {
    int negative = FALSE;
    int test = -1234567890;
    char s[12];
    itoa(test, negative, s);

    printf("Numero: %d. String: %s.\n", test, s);
}