#include <stdio.h>
#include <string.h>

// Transcripcion del ejemplo para mejor entendimiento.

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSPACE 10000

char *lineptr[MAXLINES]; // La notacoin **lineptr no reserva espacio.

void writelines (char **lineptr, int nlines) { // Recibe un numero de lineas y un arreglo de punteros
    printf("\n\n");
    do 
        printf("%s\n", *lineptr++); 
    while (--nlines > 0); // Imprimir la linea siempre que queden lineas.
}

int getline(char *s, int lim) { // Copiado de funciones utiles
    int i, c;

    for (i = 0; i < --lim && (c = getchar()) != EOF && c != '\n'; ++i, ++s)
        *s = c;
    if (c == '\n')
        *s = c;
    *++s = '\0';

    if (c == EOF)
        return c;
    else
        return i;
}

char buff[MAXSPACE];
char *buffp = buff; // buffp inicialmente apuntaba a 0. Debe comenzar como la misma direccion inicial en buff

char *alloc (int sp) {
    if (sp < MAXSPACE - (buffp - buff)) // Si hay espacio disponible
        return (buffp += sp); // Establecer la nueva direccion como la posicion del buffer
    else {
        printf("alloc: not enough space.\n");
        return NULL;
    }
}

int readlines (char **lineptr, int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= MAXLINES || (p = alloc(len + 1)) == NULL) { // Es necesario tener algun lugar donde almacenar todas las lineas.
            return -1;
        }
        else {
            line[len] = '\0'; // Mi version de getline devuelve la cantidad de caracteres distintos a \n y \0 escritos. Por ende, basta con que sea len.
            strcpy(p, line); // Copiar la linea (temporal) a p (espacio en almacenamiento)
            *(lineptr + nlines++) = p; // Guardar la direccion de la linea en el arreglo
            
        }
    }
    return nlines; // Retornar la cantidad de lineas
}

void swap (char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort (char *v[], int left, int right) { // En este caso puedo inferir que la notacion de solo apuntadores será una complicacion más que una facilidad.
    int i, last;
    
    if (left >= right)
        return; // Control de recursion.

    swap(v, left, (left + right) / 2);
    last = left; // Comenzar el ordenamiento tomando el elemento medio, inicializando el ultimo estudiado como el de la izquierda
    for (i = left + 1; i <= right; ++i)
        if (strcmp(v[i], v[left]) < 0) // Si el i-esimo elemento es lexicograficamente menor que el de la derecha
            swap(v, ++last, i); // Poner el i-esimo elemento lo más pegado del elemento left estudiado.
    swap(v, left, last); // Poner el elemento estudiado left en el medio separando los menores de los mayores
    qsort(v, left, last - 1); // Iniciar recursion en el lado izquierdo de la division inicial
    qsort(v, last + 1, right); // Iniciar recursion en el lado derecho de la division inicial
}

int main () {
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) { // Si hay lineas validas o una cantidad valida
        qsort(lineptr, 0, nlines - 1); // Ordenar considerando left como 0 y right como el indice de la ultima direccion guardada
        writelines(lineptr, nlines); // Escribir todas las lineas
        return 0;
    }
    else { // Si hay error
        printf("error: entrada demasiado grande para ordenarla\n");
        return 1;
    }
}

