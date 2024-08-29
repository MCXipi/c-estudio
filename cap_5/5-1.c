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

// Copia del ejemplo para agregarle ejercicio 5-1.

int getint(int *pn) {
    int c, sign, pre;

    while (isspace(c = getch())) 
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); 
        return 0;
    }
    sign = (c == '-') ? -1 : 1; 
    if (c == '+' || c == '-') {
        pre = c;
        c = getch();
    }
    if (!isdigit(c)) {
        ungetch(pre); // Si solo guardo el caracter de signo permito la validez de entradas como "-     1" o "+     1" al usarse en ciclos
        return 0;
    } 

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + c - '0'; 
    *pn *= sign; 

    if (c != EOF)
        ungetch(c);
    return c;     
}

void main() {
    int n, result;
    result = getint(&n);
    if (result)
        printf("n = %d\n", n);
    else
        printf("error\n");
}