#include <stdio.h>

#define IN 1
#define OUT 0

main(){
    int c, pal, car, lin, state;
    state = OUT;
    pal = car = lin = 0;
    while ((c = getchar()) != EOF){
        ++car;
        if (c == '\n')
            ++lin;
        if (c == ' ' | c == '\t' | c == '\n'){
            state = OUT;
            --car;
        }
        else if (state == OUT){
            state = IN;
            ++pal;
        }
    }
    printf("Palabras: %d. Caracteres: %d. Lineas: %d", pal, car, lin);
}