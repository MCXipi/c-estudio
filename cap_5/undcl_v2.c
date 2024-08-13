#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "..\funciones_utiles\getch_ungetch.c"

// Ejercicio 5-19

#define MAXTOKEN 100
#define MAXOUTLEN 1000

enum {NAME, PARENS, BRACKETS, CAT, WRITE};

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
        for (*p++ = c; MAXTOKEN - (p - token) >= 1 && (*p++ = getch()) != ']'; ) // Si es un corchete, escribir en la cadena del token todo lo dentro de estos corchetes, incluyendo el de cierre
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; MAXTOKEN - (p - token) >= 1 && isalnum(c = getch()); ) // Si es una letra, anotar todo lo que le siga si es letra o numero en la cadena token y establecer el tipo como nombre de variable.
            *p++ = c;
        *p = '\0';
        ungetch(c); // Siempre guardando el caracter de la entrada para no perderlo.
        return tokentype = NAME;
    }
    else
        return tokentype = c; // Si no es ninguno de los anteriores, podría ser un operador puntero. En ese caso, establecer como asterisco.
}

char name[MAXTOKEN]; // Nombre de token
char out[MAXOUTLEN]; // Cadena de texto de salida
char *out_i = out; // Indice de texto de salida.
int type; // Registro de tipo
int last_type; // Registro de ultimo tipo

void write_entry (const char *s, int cat) { // Escribir en out la cadena s, concatenando si CAT es 1.
    size_t s_len = strlen(s);
    last_type = type;

    if (cat == WRITE) {
        if (s_len < MAXOUTLEN) {
            out_i = out;
            strcpy(out_i, s);
            out_i += s_len;
        }
        else
            printf("Error. Not enough space (write_entry:WRITE).\n");
    }
    else if (cat == CAT) {
        if (MAXOUTLEN - (out_i - out) > s_len) {
            strcpy(out_i, s);
            out_i += s_len;
        }
        else
            printf("Error. Not enough space (write_entry:CAT).\n");
    }
}

void clean_all() {
    last_type = 0;
    out_i = out;
}

int main () {
    char temp[MAXTOKEN];

    // Son innecesarios los parentesis de los punteros si viene despues de un nombre, dos parentesis, otro puntero, o corchetes

    while ((type = gettoken()) != EOF) { // Mientras haya una linea y no EOF, copiar directamente el primer token y pedir tokens de toda la linea hasta que se acabe en \n
        write_entry(token, WRITE); 
        while ((type = gettoken()) != '\n') 
            if (type == PARENS || type == BRACKETS) // Si es parentesis de funcion o corchete de array (Desde gettoken) concatenarla a lo que se tenga en out
                if (last_type == '*') { // Si el ultimo tipo escrito es puntero, agregar parentesis a lo anterior, si no, concatenar normalmente
                    sprintf(temp, "(*%s)%s", out, token);
                    write_entry(temp, WRITE);
                }
                else
                    write_entry(token, CAT); 
            else if (type == '*') { // Si es puntero, y antes habia un puntero, poner los punteros juntos sin parentesis. Si no, establecer ultimo tipo como puntero
                if (last_type == '*') { 
                    sprintf(temp, "*%s", out, token);
                    write_entry(temp, WRITE);
                }
                else 
                    last_type = type;
            }
            else if (type == NAME) { // Si es el tipo de dato, y el tipo anterior era un puntero, anotar todo en temp y luego en out poniendo el puntero antes. Si no, anotar normalmente
                if (last_type == '*')
                    sprintf(temp, "%s *%s", token, out);
                else
                    sprintf(temp, "%s %s", token, out);
                write_entry(temp, WRITE);
            }
            else
                printf("Error. Entrada invalida en %s.\n", token);
        printf("%s\n", out); // Imprimir todo
        clean_all();
    }
    return 0;
}