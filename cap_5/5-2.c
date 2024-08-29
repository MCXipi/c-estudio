#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c;
}

int getch(void) {
    return (bufp > 0 ) ? buf[--bufp] : getchar();
}

int getfloat(long double *ps) {
    int c, sign, pre, exp;

    while (isspace(c = getch()))
        ; // Omito espacios

    if (!isdigit && c != EOF && c != '-' && c != '+') {
        ungetch(c); // Mismo trabajo si no es un numero
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        pre = c;
        c = getch(); // Mismo trabajo para el estudio del signo y de lo que viene
    }

    if (!isdigit(c)) {
        ungetch(pre); // Mismo trabajo si lo que viene despues del signo no es un digito
        return 0;
    }

    for (*ps = 0.0; isdigit(c); c = getch())
        *ps = 10.0 * *ps + c - '0'; // Mismo trabajo para la parte entera
    if (c == '.' || c == ',') {  // Si el caracter que lo frena todo es punto o coma
        c = getch();  // Obtener siguiente caracter
        for (*ps, exp = 1; isdigit(c); c = getch(), exp = exp * 10) // Y si el caracter y los siguientes son digitos, agregarlos y empezar a elaborar el divisor para la parte decimal
            *ps = 10.0 * *ps + c - '0';
        *ps /= exp; // Dividir por el divisor para la parte decimal y dejar el punto
    }
    *ps *= sign; // Establecer el signo

    if (c != EOF)
        ungetch(c); // Mismo tratamiento para EOF o cualquier otro caracter final, en el caso de un ciclo
    return c;
}

void main() {
    long double n;
    int result;
    result = getfloat(&n);
    if (result)
        printf("n = %.12g\n", n);
    else
        printf("error\n");
}