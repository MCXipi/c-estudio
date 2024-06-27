#include <stdio.h>

/*Detectar si es una secuencia de varios espacios en blanco para reemplazarlo por un retroceso*/
main(){
    int c;
    int c_anterior;
    while ((c = getchar()) != EOF){
        if (c != ' '){
            putchar(c);
        }
        else
            if (c_anterior != ' ')
                putchar(c);
        c_anterior = c;
    }
}