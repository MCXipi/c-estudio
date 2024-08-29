#include <stdio.h>

// Ejemplo de enum de la seccion 2.3

enum months {ENE = 1, FEB, MAR, ABRIL}; /*Se define la enumeracion como una secuencia que parte del 1*/

main() {
    enum months mes; /*Desde la enumeracion months se tomará uno de los elementos al que se le pone el apodo de mes*/
    mes = MAR; /*El elemento elegido es marzo.*/
    printf("%d\n", mes); /*3*/
}