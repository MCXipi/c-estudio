#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 150

//Escriba un programa para imprimir un conjunto de archivos, iniciando
//cada nuevo archivo en una página nueva, con un título y un contador de
//página por cada archivo.


void prtfile (FILE *f, char *fname, int page, int nf) {
    // Funcion que imprime el archivo f.
    // Imprime colocando el nombre de archivo, y el numero de archivo respecto al total, además de todas sus lineas, claramente.
    
    char line[MAXLEN];
    char temp[MAXLEN];
    int i, e;

    for (i = 0; i < (MAXLEN / 2) - (strlen(fname) / 2); ++i)
        fprintf(stdout, "=");
    printf(" %s ", fname);
    for (i = 0; i < (MAXLEN / 2) - (strlen(fname) / 2); ++i)
        fprintf(stdout, "=");
    fprintf(stdout, "\n");

    while(fgets(line, MAXLEN, f) != NULL)
        fprintf(stdout, "%s", line);

    sprintf(temp, " Archivo %d de %d ", page, nf);
    for (i = 0; i < (MAXLEN / 2) - (strlen(temp) / 2); ++i)
        fprintf(stdout, "=");
    fprintf(stdout, " %s ", temp);
    for (i = 0; i < (MAXLEN / 2) - (strlen(temp) / 2); ++i)
        fprintf(stdout, "=");

    fprintf(stdout, "\nPresiona ENTER para continuar.\n");
    while ((e = fgetc(stdin)) != '\n') 
        ;
    system("cls");
    return;
}

int main (int argc, char *argv[]) {
    // Considera la existencia de al menos un argumento adicional: El patron a buscar.
    // Llama a la funcion de busqueda de patron hasta que se terminen los archivos, llamados en orden, o finalice la entrada si no hay archivos.
    
    int f_i, ct; // Indice para argumento de cada nombre de archivo.
    FILE *fp;

    ct = 1;

    if (argc == 1) {
        fprintf(stderr, "%s: Requiere al menos 1 argumento.\n", argv[0]);
        exit(1);
    }
    else {
        system("cls");
        for (f_i = 1; f_i < argc; ++f_i) {
            if ((fp = fopen(argv[f_i], "r")) == NULL) {
                fprintf(stderr, "%s: Error al abrir archivo %s.\n", argv[0], argv[f_i]);
                exit(1);
            }
            else 
                prtfile(fp, argv[f_i], ct, argc - 1);
            fclose(fp);
            ++ct;   
        }        
    }
    exit(0);
}