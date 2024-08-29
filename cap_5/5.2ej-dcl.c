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

// Transcripcion del ejemplo para entenderlo.

int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch())) // Para saltar los espacios en blanco
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {// Si la entrada no es un numero
        ungetch(c); // Si no es caracter almacenalo en buffer y se retorna 0, terminando todo. -> ¿No permite trabajar más de dos llamadas seguidas, porque queda un caracter cualquier en el buffer?
        return 0;
    }
    sign = (c == '-') ? -1 : 1; // Como va por partes en la construccion del entero, ahora revisa el signo
    if (c == '+' || c == '-')
        c = getch(); // Si es un signo, seguir al otro caracter

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0'); // Transformar cada caracter de la cadena en entero
    *pn *= sign; // Aplicarle el signo

    if (c != EOF)
        ungetch(c); // Si los caracteres que quedan no son digitos pero tampoco EOF, guardalo en el buffer
    return c;       // Si es EOF, mándalo.
}

void main() {
    int n, result;
    result = getint(&n);
    if (result)
        printf("n = %d\n", n);
    else
        printf("error\n");
}