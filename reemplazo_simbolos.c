#include <stdio.h>

/*Reemplazar '\t' por "\t", '\b' por "\b", y '\' por '\\'*/
main(){
    char c;
    while ((c = getchar()) != EOF){
        if (c == '\t'){
            putchar('\\');
            putchar('t');
        }
        if (c == '\b'){
            putchar('\\');
            putchar('b');
        }
        if (c == '\\'){
            putchar('\\');
            putchar('\\');
        }
        if (c == ' ')
            putchar('b');
        else
            putchar(c);
    }
}
/*Putchar no recibe strings, pero "\b" es lo mismo que concatenar '\\' y 'b'*/
/* '\' no existe*/