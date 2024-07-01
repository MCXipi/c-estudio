#include <stdio.h>

/*Mediante una funcion obtener los valores en celcius de una lista de temperaturas originalmente en farenheit con un incremento personalizado*/

fahr_celcius(int, int, int);

fahr_celcius(int fahr_min, int fahr_max, int incremento){
    int fahr;
    float celcius;

    printf("Fahrenheit       Celcius\n");
    for (fahr = fahr_min; fahr <= fahr_max; fahr = fahr + incremento){
        celcius = (5.0/9.0) * (fahr - 32.0);
        printf("%5d           %3.2f\n", fahr, celcius);
    }
}

main(){
    fahr_celcius(0, 300, 10);
}