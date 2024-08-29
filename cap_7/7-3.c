#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define MAXLEN 150
// Ejemplo seccion 7.3 y ejercicio 7-3.

int minprintf(char *fmt, ...) {
    va_list ap; 
    char *p, *sval, temp[MAXLEN];
    void *pval;
    int ival, nc, prec;
    double dval;

    va_start(ap, fmt);
    nc = 0;
    for (p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch(*++p) {
            case 'd':
                ival = va_arg(ap, int);
                sprintf(temp, "%d", ival);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            case 'f':
                dval = va_arg(ap, double);
                sprintf(temp, "%f", dval);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; ++sval) {
                    putchar(*sval);
                    ++nc;
                }
                break;
            case 'o':
                ival = va_arg(ap, int);
                sprintf(temp, "%o", ival);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            case 'u':
                ival = va_arg(ap, unsigned int);
                sprintf(temp, "%u", ival);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            case 'x':
            case 'X':
                ival = va_arg(ap, int);
                sprintf(temp, "%X", ival);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            case 'c':
                sval = va_arg(ap, char);
                printf("%c", sval);
                ++nc;
                break;
            case 'p':
                pval = va_arg(ap, void*);
                sprintf(temp, "%p", pval);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            case 'E':
            case 'e':
                dval = va_arg(ap, double);
                sprintf(temp, "%e", dval);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            case 'G':
            case 'g':
                dval = va_arg(ap, double);
                for ( ; *ap != '.' || *ap != EOF; ++ap) // Contar exponente para adherirse a la documentacion de %g
                    ;
                for (prec = 0, ++ap; isdigit(*ap); ++prec, ++ap)
                    ;
                if (prec > 4)
                    sprintf(temp, "%e", dval);
                else
                    sprintf(temp, "%f", dval);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            case 'n':
                sprintf(temp, "%d", nc);
                nc += strlen(temp);
                printf("%s", temp);
                break;
            default:
                putchar(*p);
                ++nc;
                break;
        }
    }
    va_end(ap);
    return nc;
}