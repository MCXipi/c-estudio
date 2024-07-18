#include <stdio.h>
#include <ctype.h>

// Convertir un string numerico con punto flotante a un numero double.

double atof(char s[]) {
    int i, signo;
    double num;

    i = 0;
    num = 0.0;

    while (isspace(s[i++]))
        ;
    if (s[i] == '-') {
        signo = -1;
        ++i;
    }
    else if (s[i] == '+') {
        signo = 1;
        ++i;
    }

}

