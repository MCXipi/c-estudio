#include <stdio.h>

/* Buscamos imprimir la tabla de farenheit a celcius desde 0°F hasta los 300°F*/

float fahr, celcius, max, incremento;

fahr = 0.0;
max = 300.0;
incremento = 20.0;

main() {
    printf("fahrenheit\tcelcius\n");
    while(fahr <= max) {
        celcius = 5.0/9.0 * (fahr - 32.0);
        printf("%3.0f\t%12.2f\n", fahr, celcius);
        fahr = fahr + incremento;
    }
    printf("Hecho!\n");
}