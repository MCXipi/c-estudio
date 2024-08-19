#include <string.h>
#include <ctype.h>
#include "..\..\funciones_utiles\getch_ungetch.c"
#include "..\..\funciones_utiles\verify.c"

#define MAXWORDLEN 100
enum bool {FALSE, TRUE};

char *writeword(char *dest, char *src, int max) {
    // Revisa si la palabra en src tiene un tamaño aceptable y la escribe en dest.
    // Si se escribe, retorna la direccion destino, si no, retorna nulo.

    if (strlen(src) < max) {
        strcpy(dest, src);
        return dest;
    }
    else {
        printf("getvar: Nombre muy largo.\n");
        return NULL;
    }
}

void skip_string() {
    int c;

    while ((c = getch()) != '"' && c != '\'') // Pedir caracteres hasta que se cierre el comentario. Si es secuencia de escape ignorarlo.
        if (c == '\\')
            c = getch();
}

void skip_args() {
    int c;

    while((c = getch()) != ')') // Mientras no terminen los argumentos, llamarse a si misma si dentro hay otra funcion, y si hay string llamar a su funcion
        if (c == '(')
            skip_args();
        else if (c == '"')
            skip_string();
}

char *getvar (char *s, int max) { 
    int c, i;
    char tmp_word[MAXWORDLEN];

    while((c = getch()) != EOF) {
        ungetch(c);

        while (isspace(c = getch())) // Ignorar espacios.
            ;

        if (c == '#' || c == '/') // Si es preprocesador o comentario cambiar de linea.
            while((c = getch()) != '\n')
                ;
        else if (c == '"' || c == '\'') // Si es una cadena llamar a funcion para saltarla
            skip_string();

        else if (c == '[') // Si es arreglo, saltarse todo lo que haya dentro.
            while((c = getch()) != ']')
                ;

        else if (isalpha(c)) { // Si es un token que parte por letra
            ungetch(c);

            for (i = 0; isalnum(c = getch()) || c == '_'; ++i) // Escribir token en palabra temporal
                tmp_word[i] = c;
            tmp_word[i] = '\0';
            ungetch(c);

            while (isspace(c = getch())) // Quitar espacios despues del token
                ;
            
            if (c == '(') // Si el caracter es un parentesis, es una funcion. Saltar argumentos y continuar.
                skip_args();
            else if (!verify_token(tmp_word)) { // Si el token no es reservado, escribir en arreglo y retornar. Si es reservado, seguir.
                ungetch(c);
                writeword(s, tmp_word, max);
                return s;
            }
            else
                ungetch(c);
        }
    }
    return NULL;
}