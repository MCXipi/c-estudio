#include <stdio.h>
#include <string.h>

// Realizacion del ejercicio 5-7

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

int readlines (char **lineptr, int maxlines, char *buf, char *bufpos) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= MAXLINES || len >= MAXSPACE - (bufpos - buf)) // Si ya hay demasiadas lineas o no cabe en el buffer entregado por main, retornar -1
            return -1;
        else {
            line[len] = '\0'; // Mi version de getline devuelve la cantidad de caracteres distintos a \n y \0 escritos. Por ende, basta con que sea len.
            strcpy(bufpos, line); // Copiar la linea (temporal) a p (espacio en almacenamiento)
            bufpos += len + 1; // Se coloca la ultima direccion en buffer para el proximo espacio vacio
            *(lineptr + nlines++) = bufpos - len - 1; // Guardar la direccion de la linea en el arreglo
        }
    }
    // Podría hasta hacer que se escriba directamente en el buffer y no en un arreglo line temporal, pero no me incumbe por el ejercicio. Quiza ni ahorre tiempo con los computadores de ahora.
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
    char buff[MAXSPACE];
    char *buffp = buff; // Inicializo localmente el buffer y su ultima direccion

    if ((nlines = readlines(lineptr, MAXLINES, buff, buffp)) >= 0) { // Si hay lineas validas o una cantidad valida
        qsort(lineptr, 0, nlines - 1); // Ordenar considerando left como 0 y right como el indice de la ultima direccion guardada
        writelines(lineptr, nlines); // Escribir todas las lineas
        return 0;
    }
    else { // Si hay error
        printf("error: entrada demasiado grande para ordenarla\n");
        return 1;
    }
}

