#include <stdio.h>

// Codigo para testear lo establecido sobre las "variables en bloques" de la seccion 4.8

void main() {
    int x = 100;
    int i = 0;
    
    while(i < 3) {
        // static int x = 0; Si se deja como static efectivamente se ira sumando +1 a x por cada ciclo, mientras que si no es static, se inicializará como 0 cada vez.
        int x = 0;
        ++x;
        printf("%d\n", x);
        ++i;
    }

    //if (1) {
    //    int x = 4;
    //    printf("%d\n", x);
    //}
    
    printf("%d\n", x);
}