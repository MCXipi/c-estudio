#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAXLEN 256

// Ejercicio 7-4

int minscanf (char *fmt, ...) {
    int el, *ipt;
    float *fpt;
    void *ppt;
    char *scpt, *pfmt, *pln;
    va_list arg;

    el = 0;

    va_start(arg, fmt);
    for (pfmt = fmt; *pfmt; ++pfmt) {
        if (*pfmt == '%') {
            switch(*++pfmt) {
                case 'd':
                case 'i':
                    ipt = va_arg(arg, int *);
                    scanf("%i", ipt);
                    break;
                case 'o':
                    ipt = va_arg(arg, int *);
                    scanf("%o", ipt);
                    break;
                case 'u':
                    ipt = va_arg(arg, unsigned int *);
                    scanf("%u", (unsigned int *) ipt);
                    break;
                case 'x':
                case 'X':
                    ipt = va_arg(arg, int *);
                    scanf("%X", ipt);
                    break;
                case 's':
                    scpt = va_arg(arg, char *);
                    scanf("%s", scpt);
                    break;
                case 'c':
                    scpt = va_arg(arg, char *);
                    scanf("%c", scpt);
                    break;
                case 'e':
                    fpt = va_arg(arg, float *);
                    scanf("%e", fpt);
                    break;
                case 'f':
                    fpt = va_arg(arg, float *);
                    scanf("%f", fpt);
                    break;
                case 'g':
                    fpt = va_arg(arg, float *);
                    scanf("%g", fpt);
                    break;
                default:
                    break;
            }
            ++el;
        }
    }
    va_end(arg);
    return el;
}

int main () {
    int entero, octal, hexadecimal, el;
    unsigned nosignado;
    char string[100], caracter;
    float ptoflotante;

    el = minscanf("%d/%u/%o/%x/%s/%c/%f", &entero, &nosignado, &octal, &hexadecimal, string, &caracter, &ptoflotante);
    printf("%d/%u/%o/%x/%s/%c/%f EL = %d\n", entero, nosignado, octal, hexadecimal, string, caracter, ptoflotante, el);
}