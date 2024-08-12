#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "..\funciones_utiles\getch_ungetch.c"

// Copia del ejemplo de la seccion 5.12 para mejor entendimiento.

#define MAXTOKEN 100

enum {NAME, PARENS, BRACKETS};

int tokentype; // Tipo del ultimo token trabajado
char token[MAXTOKEN]; // Cadena del ultimo token trabajado

int gettoken () {
    int c;
    char *p = token; // p puntero a char con la misma direccion a la cadena del ultimo token trabajado

    while ((c = getch()) == ' ' || c == '\t') // Ignorar tab y blancos
        ;
    if (c == '(') {
        if ((c = getch()) == ')') { // Si c y c+1 son parentesis abriendo y cerrando, copiar el token de parentesis a la cadena y establecer el tipo
            strcpy(token, "( )");
            return tokentype = PARENS;
        }
        else {
            ungetch(c); // Si solo c es parentesis, guardar el caracter siguiente para no perderlo y establecer el tipo como parentesis unico.
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; ) // Si es un corchete, escribir en la cadena del token todo lo dentro de estos corchetes, incluyendo el de cierre
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); ) // Si es una letra, anotar todo lo que le siga si es letra o numero en la cadena token y establecer el tipo como nombre de variable.
            *p++ = c;
        *p = '\0';
        ungetch(c); // Siempre guardando el caracter de la entrada para no perderlo.
        return tokentype = NAME;
    }
    else
        return tokentype = c; // Si no es ninguno de los anteriores, podría ser un operador puntero. En ese caso, establecer como asterisco.
}

char name[MAXTOKEN]; // Nombre de token
char out[1000]; // Cadena de texto de salida

int main () {
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) { // Mientras haya una linea y no EOF, copiar directamente el primer token y pedir tokens de toda la linea hasta que se acabe en \n
        strcpy(out, token); 
        while ((type = gettoken()) != '\n') 
            if (type == PARENS || type == BRACKETS) // Si es parentesis de funcion o corchete de array (Desde gettoken) concatenarla a lo que se tenga en out
                strcat(out, token); 
            else if (type == '*') { // Si es operador puntero, tomar lo existente, ponerlo con un asterisco antes y en parentesis, en una cadena temporal, y luego copiarla a out
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            }
            else if (type == NAME) { // Si es un nombre, es el tipo de dato, escribir el tipo de dato antes de todo lo existente en cadena temporal y luego copiarla en out
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
                printf("Error. Entrada invalida en %s.\n", token);
        printf("%s\n", out); // Imprimir todo
    }
    return 0;
}