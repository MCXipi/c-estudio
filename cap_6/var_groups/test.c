#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estructura para representar un punto en 2D
struct Point {
    int x;
    int y;
};

// Prototipos de funciones
void printVariables(int a, float b, char c, struct Point p);
int sum(int a, int b);

int main() {
    // Variables de diferentes tipos
    int a = 10;
    float b = 20.5;
    char c = 'C';

    // Arreglo de enteros
    int arr[5] = {1, 2, 3, 4, 5};

    // Punteros
    int *ptrA = &a;
    float *ptrB = &b;

    // Estructura
    struct Point p1 = {10, 20};
    struct Point p2 = {30, 40};

    // Llamada a funciones
    int result = sum(a, arr[2]);
    printVariables(a, b, c, p1);

    // Operaciones con punteros
    *ptrA = 15;
    *ptrB = 25.5;

    // Modificando estructura
    p2.x = *ptrA;
    p2.y = *ptrB;
    
    // Imprimiendo resultados
    printf("Resultado de la suma: %d\n", result);
    printf("Nuevo valor de a: %d\n", *ptrA);
    printf("Nuevo valor de b: %.2f\n", *ptrB);
    printf("Punto 2 actualizado: (%d, %d)\n", p2.x, p2.y);
    return 0;
}

// Función que imprime variables
void printVariables(int a, float b, char c, struct Point p) {
    printf("Valores:\n");
    printf("a = %d\n", a);
    printf("b = %.2f\n", b);
    printf("c = %c\n", c);
    printf("Punto: (%d, %d)\n", p.x, p.y);
}

// Función que suma dos enteros
int sum(int a, int b) {
    return a + b;
}
