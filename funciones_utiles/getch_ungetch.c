#include <stdio.h>

// Funcion getch y ungetch que se usan mucho pasado el capitulo 3.

#define MAXBUF 100

static int buf[MAXBUF], buf_i;

int getch (void) {
    return buf_i > 0 ? buf[--buf_i] : getchar();
}

void ungetch (int c) {
    if (buf_i < MAXBUF)
        buf[buf_i++] = c;
    else
        printf("Ungetch: Not enough space.\n");
}

