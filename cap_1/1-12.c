#include <stdio.h>

/*Debo imprimir cada input hasta su \n. Cada espacio debo reemplazarlo por una nueva linea*/
main(){
    int c, car;
    car = 0;
    while(((c = getchar()) != EOF)){
        ++car;
        if (c == ' ' | c == '\t') /*Pendiente: ¿Como declarar para que un '\t' inicial solo se ignore, ESTE MISMO IF? -->> Limpiando espacios en blanco antes de comenzar */
            putchar('\n');
        else
            putchar(c);
    }
}