#include "cf.h"
#include "..\..\funciones_utiles\getch_ungetch.c"

#define MINLEN 3

char *write_word(char *dest, char *src, int lim) {
    // Funcion que comprueba si la cadena en src tiene tiene un largo aceptable menor al limite lim.
    if (strlen(src) < lim) {
        strcpy(dest, src);
        return src;
    }
    else {
        printf("Error: Word too long. (write_word).\n");
        return NULL;
    }
}

char *get_word(char *s, int max, int *nline) {
    // Funcion que busca una palabra de longitud mayor a 2 caracteres desde la entrada
    // Encuentra la palabra, la escribe en una cadena temporal y si es aceptable, la escribe en s.
    // Ayuda al control del numero de linea sumando a la variable de main cuando encuentra un '\n'
    // Retorna puntero NULL si hay error o EOF, s si se escribió.

    int c, i;
    char tmp_word[MAXWORDLEN];

    while((c = getch()) != EOF) {
        ungetch(c);

        while (!isalpha(c = getch())) // LLegar hasta un caracter alfabético. Si es nueva linea aumentar el numero de linea actual. Si es EOF salir de while.
            if (c == '\n') 
                ++*nline;
            else if (c == EOF)
                break;
        ungetch(c);

        for (i = 0; i < max - 1 && isalpha(c = getch()); ++i) // Escribir la palabra que se haya encontrado.
            tmp_word[i] = c;
        tmp_word[i] = '\0';
        ungetch(c);

        if (i >= max - 1)
            printf("\"%s\" cortada por exceso de longitud.\n", tmp_word);

        if (strlen(tmp_word) > MINLEN) // Si la palabra tiene más de 3 letras, escribir y retornar direccion s.
            return write_word(s, tmp_word, max);
    }
    return NULL;
}