#include <stdio.h>

/*Contar los espacios en blanco '\b', las tabulaciones '\t', y las nuevas lineas '\n'*/
main(){
    int c;
    int bco = 0;
    int tab = 0;
    int nl = 0;
    printf("Ingresa texto:");
    while((c = getchar()) != EOF){
        if (c == '\n')
            ++nl;
        if (c == '\t')
            ++tab;
        if (c == ' ')
            ++bco;
    }
    printf("Hay %d espacios en blanco, %d tabulacion(es) y %d linea(s)", bco, tab, nl);
}