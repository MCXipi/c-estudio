#include <stdio.h>
#include <string.h>

#define MAXLEN 150

void find (FILE *f, char pat[], char *fname) {
    // Funcion que busca el patron de caracteres pat en cada linea del archivo f, de nombre fname.
    // Si la inicial de pat concuerda con la letra de la linea, se comprueba si es el patrón. Si es, se imprime la linea y el archivo.
    // LLeva seguimiento de la linea actual.

    char line[MAXLEN];
    int ln, i, j, fnd;
    
    ln = 1;
    fnd = 0;

    while(fgets(line, MAXLEN, f) != NULL) {
        for (i = 0; line[i] != '\n'; ++i) {
            if (line[i] == pat[0]) {
                for (j = 0; pat[j] != '\0' && i + j < MAXLEN && line[i + j] == pat[j]; ++j)
                    ;
                if (pat[j] == '\0') {
                    fprintf(stdout, "\"%s\" encontrado en linea %d de %s.\n", pat, ln, fname);
                    ++fnd;
                }
            }
        }
        ++ln;
    }
    if (fnd == 0)
        printf("0 ocurrencias en %s.\n", fname);
}

int main (int argc, char *argv[]) {
    // Considera la existencia de al menos un argumento adicional: El patron a buscar.
    // Llama a la funcion de busqueda de patron hasta que se terminen los archivos, llamados en orden, o finalice la entrada si no hay archivos.
    
    int f_i; // Indice para argumento de cada nombre de archivo.
    FILE *fp;

    if (argc == 1) {
        fprintf(stderr, "%s: Requiere al menos 1 argumento.\n", argv[0]);
        exit(1);
    }
    else if (argc == 2) {
        find(stdin, argv[1], "stdin");
    }
    else {
        for (f_i = 2; f_i < argc; ++f_i) {
            if ((fp = fopen(argv[f_i], "r")) == NULL) {
                fprintf(stderr, "%s: Error al abrir archivo %s.\n", argv[0], argv[f_i]);
                exit(1);
            }
            else 
                find(fp, argv[1], argv[f_i]);
            fclose(fp);   
        }        
    }
    exit(0);
}