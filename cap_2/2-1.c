#include <stdio.h>
#include <limits.h>
#include <float.h>

/*Para determinar los rangos de los tipos puedo considerar el hecho de que el overflow provoca regresar al inicio*/

void main() {
    printf("Valor minimo de char: %c. Valor maximo: %c\n", CHAR_MIN, CHAR_MAX);
    printf("Valor minimo de int: %d. Valor maximo: %d\n", INT_MIN, INT_MAX);
    printf("Valor minimo de long: %ld. Valor maximo: %ld\n", LONG_MIN, LONG_MAX);
    printf("Valor minimo de signed char: %d. Valor maximo: %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Valor minimo de short: %d. Valor maximo: %d\n", SHRT_MIN, SHRT_MAX);
    printf("Valor maximo de unsigned char: %u\n", UCHAR_MAX);
    printf("Valor maximo de unsigned int: %u\n", UINT_MAX);
    printf("Valor maximo de unsigned long: %u\n", ULONG_MAX);
    printf("Valor maximo de unsigned short: %u\n", USHRT_MAX);
    printf("Valor minimo de float: %.38lf. Valor maximo: %.38lf\n", FLT_MIN, FLT_MAX);
    //int está siendo considerado como long int de manera "natural"
    //float está siendo considerado un double float
    printf("\n\n");

    short int i;
    short int ultimo;
    short int primero;
    for (i = 0; i >= 0; ++i){
        ultimo = i;
    }
    primero = i;
    printf("Mayor int: %d. Menor int: %d\n", ultimo, primero);

    float x;
    float masgrande;
    float maschico;
    for (x = 1.0; x > 0; ++x){
        masgrande = x;
    }
    maschico = x;
    printf("Mayor float: %f. Menor float: %f\n", masgrande, maschico);

    for (x = 0.1; x < 1 && x > 0; x = x * 0.1)
        maschico = x;
    printf("%40f", maschico);
    

}