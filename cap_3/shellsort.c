#include <stdio.h>

// Aplicacion de Shellsort para una lista distribuida en orden ascendente.

void shellsort(int v[], int n) { // Recibe como argumentos el array y el numero de elementos en este.
    int gap, i, j, k, temp;

    for (gap = n/2; gap > 0; gap /= 2){ // Gap comienza con una separacion entre elementos igual a la mitad del numero de elementos, y se va reduciendo a la mitad.
        for (i = gap; i < n; i++){ // El indice i comienza como el elemento alejado gap elementos del primero de la lista.

            for (k = 0; k < n; ++k)                     // Impresion
                printf("%2d ", v[k]);                   // para la
            printf("| i = %2d, gap = %2d\n", i, gap);   // tabla

            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) { // Se establece j como el indice que tiene alejado a i en gap elementos, y se comprueba si el elemento j es mayor. Si lo es, se cambian lugares y con j-=gap se realizan más cambios a partir del primero, hacia el inicio de la lista.
                temp = v[j];
                v[j] = v[j + gap]; // j + gap tiene la utilidad de hacer los posibles cambios después de un primer cambio en este mismo for, luego de que j -= gap.
                v[j + gap] = temp;
            }
        }
    }
}

// Main hace una tabla con los pasos que realiza el shellsort entre un indice i y el siguiente, con su respectivo gap.
void main() {
    int i, n;
    n = 10;
    int list[10] = {2, 10, 6, 4, 9, 7, 3, 8, 1, 5};
    
    printf("            Indice              Indice lejano / gap\n");
    for (i = 0; i < n; ++i)
        printf("%2d ", i);
    printf("\n");
    for (i = 0; i < n; ++i)
        printf("_____");
    printf("\n");

    shellsort(list, n);
}