#include <stdio.h>
#include <time.h>

// Binsearch original limita la amplitud de la busqueda de un numero dentro de una
// lista, dividiendola por la mitad cada vez que se encuentre la mitad en la que 
// está. hasta que eventualmente encuentre al numero (o no).

// Newbinsearch elimina la segunda comprobacion y deja solamente si es menor al 
// valor medio del arreglo. Por ende, si esto es falso, o es el valor medio mismo
// o es mayor, por lo que se aumenta el limite inferior. Si es el valor medio, 
// aumentar el limite inferior hará que la primera comprobacion se haga verdadera
// y que por ende el limite superior baje indefinidamente hasta que sean iguales.

int binsearch(int x, int v[], int n) {
    int low, high, mid;
    
    low = 0;
    high = n - 1; // n = numero de elementos

    while (low < high){ // Si low == high, el unico elemento es o no es x.
        mid = (low + high)/2;
        printf("High: %d, mid: %d, low: %d\n", high, mid, low);
        if (x < v[mid])
            high = mid - 1; // -1 porque ya sabemos que v[mid] no es.
        else
            low = mid + 1; // Si no es menor a v[mid], o es mayor o es igual.
                           // si es mayor, puede que no sea, y se detendrá cuando low > high.
    }

    mid = low = high; // El bucle siempre terminará cuando low == high. Por legibilidad se deja como mid. Si mid es 
    if (x == v[mid])
        return mid;
    else
        return -1; 

}

void main() {
    int x, n, posicion;
    clock_t tiempo_inicio, tiempo_fin;
    double tiempo_tot;

    tiempo_inicio = clock();

    n = 50;
    int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
    x = 65;
    posicion = binsearch(x, v, n);

    tiempo_fin = clock();
    tiempo_tot = ((double)(tiempo_fin - tiempo_inicio)) / CLOCKS_PER_SEC; // Al parecer en ese tiempo el proceso demoraba.

    printf("La posicion es %d. Encontrada en %.12f segundos.\n", posicion, tiempo_tot);
}