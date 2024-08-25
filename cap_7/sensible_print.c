#include <stdio.h>
#include <ctype.h>

#define MAXCOL 10
#define TMPLEN 100

int main () {
    // Funcion que escribe la entrada recibida volviendo caracteres no graficos en graficos, y restringiendo las columnas a un numero MAXCOL
    // Trabaja las palabras cortadas poniendo un "-" al continuarla en la otra fila
    // Imprime codigo ASCII en forma hexadecimal de los caracteres no graficos.
    
    int c, last, col;
    char temp[TMPLEN];

    col = 1;
    last = NULL;

    while((c = getchar()) != EOF) {
        if (isalpha(last) && isalpha(c) && col == 1) {
            printf("-%c", c);
            col += 2;
        }
        else if (isprint(c) && col < MAXCOL) {
            printf("%c", c);
            ++col;
        }
        else if (iscntrl(c)) {
            sprintf(temp, "\\0x%X", c);
            if (col + strlen(temp) > MAXCOL) {
                col = 1;
                printf("\n%s", temp);
                col += strlen(temp);
            }
            else {
                printf("%s", temp);
                col += strlen(temp);
            }
        }
        else if (col >= MAXCOL) {
            printf("%c\n", c);
            col = 1;
        }
        last = c;
    }
}