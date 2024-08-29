#include <stdio.h>
#include <string.h>

// Ejercicio 7-6

void filecmp (FILE *f1, FILE *f2) {
    // Funcion que compara dos archivos f1 y f2 letra por letra.
    // Compara letra a letra por linea hasta que se acabe el archivo o haya alguna diferencia entre estos o en su longitud.
    // Se imprime la diferencia con la columna y linea exacta donde está, y el codigo ASCII del caracter diferente.

    int col, fil, c1, c2;

    fil = col = 1;

    while (1) {
        c1 = fgetc(f1); // Asignar dentro de un while infinito y no en la comprobacion permite que se lean caracteres en ambos archivos,
        c2 = fgetc(f2); // por cada ciclo, independientemente si la comprobación es verdadera o no (EOF), en alguna, o las dos.

        if (c1 == EOF && c2 == EOF) {
            fprintf(stdout, "Archivos iguales.\n");
            exit(0);
        }
        else if (c1 == EOF || c2 == EOF) {
            fprintf(stdout, "Archivos de longitudes distintas.\n");
            exit(0);
        }
        else if (c1 != c2) {
            fprintf(stdout, "Encontrada diferencia en linea %d columna %d entre los caracteres ASCII %d = %c y %d = %c.\n", fil, col, c1, c1, c2, c2);
            exit(0);
        }

        if (c1 == '\n' && c2 == '\n') {
            ++fil;
            col = 1;
        }
        else
            ++col;
    }
}

int main (int argc, char *argv[]) {
    // Encargada de obtener los nombres de los archivos para trabajarlos. Debe recibir si o si dos nombres de archivos, para luego abrirlos y compararlos.

    FILE *f1, *f2;

    if (argc != 3) {
        fprintf(stderr, "%s: Debe recibir dos argumentos.\n", argv[0]);
        exit(1);
    }
    else {
        f1 = fopen(argv[1], "r");
        f2 = fopen(argv[2], "r");
        if (f1 == NULL || f2 == NULL) {
            fprintf(stderr, "%s: Error de lectura %s.\n", argv[0], f1 == NULL ? argv[1] : argv[2]);
            exit(1);
        }
        filecmp(f1, f2);
    }
}