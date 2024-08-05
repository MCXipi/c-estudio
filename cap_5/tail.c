#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 100
#define MAXLEN 100000
#define MAX 1000

// Necesitaré dos funciones: Una para escribir las lineas y otra para leerlas. Leerlas debe escribir una linea y guardar el puntero a esta en un arreglo más grande. Main lo que hace es simplemente mandarle la indicacion a la funcoin de escribir, de cuantas lineas para "atras" debe escribir.

static char *ln_ptr[MAXLINES]; // Array externo de almacenamiento de punteros de lineas
static char ln_buff[MAXLEN]; // Array externo de almacenamiento de lineas
static char *ln_buff_i = ln_buff; // Indice de ultimo caracter escrito en ln_buff --> Es mas practico trabajar con punteros para buffers
static int ptr_i;

// Tambien necesito de una funcion alloc que me permita estudiar el uso de almacenamiento y disponibilidad.

// ['h', 'o', 'l', 'a', '\n', '\0', 0, 0, 0, 0]
//   0    1    2    3     4     5   6  7  8  9     --> len + 1 indica el nuevo indice para el siguiente espacio libre. Len es el minimo de espacio que debe haber disponible


char *alloc (int len) { // Retorna un puntero a la direccion de ln_buff donde empezar a escribir
    if (len < MAXLEN - (ln_buff_i - ln_buff)) { // Si hay espacio disponible
        ln_buff_i += len; // Actualiza el puntero a espacio libre
        return ln_buff_i - len; // Retorna puntero donde escribir
    }
    else { // Si no hay espacio suficiente
        printf("Alloc: Not enough space.\n"); 
        return NULL; // Imprimir error y retornar nulo
    }
}

int readlines () {
    char ln_temp[MAX]; // Para realizar un buen trabajo con el almacenamiento es necesario obtener la linea primero.
    int len = 0, c, nlines = 0;
    char *ptr;

    while((c = getchar()) != EOF && len < MAX) { // Mientras el caracter pasado no sea EOF y no se haya superado el limite de tamaño
        if (c != '\n')  // Si el caracter no es una nueva linea
            ln_temp[len++] = c;
        else { // Si lo es
            ln_temp[len++] = c;
            ln_temp[len++] = '\0'; // Terminar la linea con '\n' y '\0'
            if ((ptr = alloc(len)) != NULL && ptr_i < MAXLINES) {// Si se pudo otorgar espacio para el puntero y para la linea
                strcpy(ptr, ln_temp); // Escribe la linea en el array de caracteres
                ln_ptr[ptr_i++] = ptr; // Guardar el puntero en el arreglo.
                len = 0; // Reiniciar len para la siguiente linea
                ++nlines; // Aumentar numero de linea
            }
            else if (ptr_i == MAXLINES) { // Si ya no pueden haber más lineas
                printf("Readlines: Too many lines.\n");
                break; // Terminar
            }
            else
                break; // Si es nulo, se uso todo el espacio y no se puede seguir escribiendo
        }
    }
    if (len == MAX) {
        printf("Readlines: Line too long.\n");
        return 0;
    }
    else
        return nlines;
}

void writelines (int n) {
    int i;
    printf("\n\n");
    for (i = 1; i <= n; ++i) // Para un i igual al indice de la ultima linea, y mientras i y sus antecesores sean pertenecientes a los ultimos n indices
        printf("%s", ln_ptr[ptr_i - i]); // Imprimir
}

int main (int argc, char **argv) {
    int r, n = 0;

    r = readlines(); // Pedir entrada
    if (r && argc == 1) { // Si hay lineas y un argummento
        writelines(r); // Escribir todas las lineas
        return 1;
    }
    else if (r && argc == 2 && **++argv == '-') { // Si se pudo leer la linea, hay dos argumentos y el segundo es una opcion
        for (++(*argv); isdigit(**argv); ++(*argv)) // Para cada caracter en la opcion partiendo del caracter despues del '-'
            n = n * 10 + (**argv - '0');
        if (**argv != '\0' && !isdigit(**argv)) { // Si el for termino por un caracter aparte de '\0' y un numero
            printf(".\\tail [-n]\n");
            return 0;
        }
        else {
            writelines(n);
            return 1;
        }
    }
    else {
        printf(".\\tail [-n]\n");
        return 0;
    }
}
