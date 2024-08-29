#include <stdio.h>

// Ejemplo del quicksort mostrado en la sección 4.11

void swap(int v[], int i, int j) { // Funcion usada para intercambiar dos elementos en los indices i e j del array v
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(int v[], int left, int right) { // Distribuye en orden ascendente.
    int i, last;
    void swap(int v[], int i, int j);

    if (left >= right) // Left es el elemento al extremo izquierdo, y right, el del extremo derecho. Si el extremo izquierdo es igual o mayor al derecho, entonces ya no hay más que ordenar. Es el tope de la recursividad.
        return;
    
    swap(v, left, (left + right)/2); // Se toma como referencia el elemento medio del grupo estudiado para comenzar el ordenamiento, el que se pone a la izquierda
    last = left; // Se inicializa el ultimo elemento intercambiado, partiendo con la izquierda.

    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);  // En el intervalo que se está ordenando, distribuir los que son menores teniendo a left como referencia y los que son mayores se quedan al final, sin mayor detalle. El ultimo menor que left queda con el nombre last
    
    swap(v, left, last); // Mover el elemento de "referencia" de left hacia el lugar donde estaba el ultimo menor comparado, dejando los menores a el a la izquierda, y los mayores a la derecha

    qsort(v, left, last - 1); // Inicializar recursividad para ordenar entre ellos todos los elementos que están a la izquierda del elemento de referencia, osea los menores

    qsort(v, last + 1, right); // Inicializar recursividad para ordenar entre ellos todos los elementos que están a la derecha del elemento de referencia, osea los mayores.
}

void main() {
    ;
}