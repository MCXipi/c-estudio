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

void dcl () { // Para reconocer lo que en el libro son las declaraciones *s
    int ns; // Cuenta de operadores punteros
    extern char out[];
    void dirdcl(void);

    for (ns = 0; gettoken() == '*'; ) // Cuenta operadores puntero antes de cualquier otro token
        ++ns;
    dirdcl();
    while (ns-- > 0) // Por cada operador puntero escribir apuntador a en una cadena de salida.
        strcat(out, " apuntador a");
}

void dirdcl () { // Para reconocer en el libro lo que son las declaraciones directas nombre, (dcl), dcl-directa(), dcl-directa[tamaño-opcional]
    int type;
    extern char name[], out[];

    if (tokentype == '(') { // Si el token ignorado por dcl es parentesis, ejecutar dcl recursivamente para todo lo interno. Si el ultimo token no es parentesis, imprimir error
        dcl();
        if (tokentype != ')')
            printf("Error: Falta ).\n");
    }
    else if (tokentype == NAME) // Si el token ignorado en dcl es un nombre, copiar el nombre en la cadena para nombres, o enviar error.
        strcpy(name, token);
    else
        printf("Error: Nombre o (dcl) esperado.\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS) // Ver si el siguiente token son parentesis de funcion o corchetes de arreglo, y copiar en la cadena de salida lo que corresponda.
        if (type == PARENS)
            strcat(out, "funcion que regresa");
        else {
            strcat(out, " arreglo ");
            strcat(out, token);
            strcat(out, " de");
        }
}

char name[MAXTOKEN]; // Nombre de token
char datatype[MAXTOKEN]; // Tipo de dato
char out[1000]; // Cadena de texto de salida

int main () {

    while (gettoken() != EOF) { // Si el primer token no es EOF, es el tipo de dato. Se copia en su cadena y se cierra la cadena de salida.
        strcpy(datatype, token);
        out[0] = '\0';
        dcl(); // Se inicia la recursión de busqueda de tokens entre dcl y dirdcl. Si el ultimo token no es un '\n', hubo un error. Imprimir la salida.
        if (tokentype != '\n')
            printf("Error: Sintaxis.\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}