#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000

// Estructura para probar el análisis de nombres de variables
struct Person {
    char name[MAXLEN];
    int age;
    float height;
};

int main() {
    int var1 = 10;
    int variable2 = 20;
    int variab = 30;
    char varString[MAXLEN] = "Esto es una prueba";
    char varStr[10] = "Hola";
    char *ptr1 = varString;
    char *ptr2 = varStr;
    float varFloat = 3.14;
    double varDouble = 2.71828;
    struct Person person1 = {"John", 25, 5.9};
    struct Person *personPtr = &person1;
    
    // Pruebas con arreglos y ciclos
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i * var1;
    }

    if (var1 < variable2) {
        printf("var1 es menor que variable2\n");
    }

    // Prueba con una función y más variables
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += array[i];
    }
    printf("La suma del arreglo es: %d\n", sum);

    return 0;
}
