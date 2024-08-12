#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "..\funciones_utiles\getch_ungetch.c"

// Ejercicios de la seccion 5.12

#define MAXTOKEN 100
#define MAXOUTLEN 1000

enum {NAME, PARENS, BRACKETS, TOKEN, OUT};

int tokentype; // Tipo del ultimo token trabajado
char token[MAXTOKEN]; // Cadena del ultimo token trabajado

int gettoken () {
    int c;
    char *p = token; // p puntero a char con la misma direccion a la cadena del ultimo token trabajado
    void write_entry(char *, const char *, int);

    while ((c = getch()) == ' ' || c == '\t') // Ignorar tab y blancos
        ;
    if (c == '(') {
        if ((c = getch()) == ')') { // Si c y c+1 son parentesis abriendo y cerrando, copiar el token de parentesis a la cadena y establecer el tipo
            write_entry(token, "( )", token);
            return tokentype = PARENS;
        }
        else {
            ungetch(c); // Si solo c es parentesis, guardar el caracter siguiente para no perderlo y establecer el tipo como parentesis unico.
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']' && (*(p - 1)) != '\n' && (p - token) < MAXTOKEN; ) // Si no hay corchete final, esperar a nueva linea para enviar error
            ;
        if (*(p - 1) == '\n') {
            printf("Error: Falta ].\n");
            return '\n';
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()) || c == '_' && (p - token) < MAXTOKEN; ) // Si es una letra, anotar (si hay espacio) todo lo que le siga si es letra o numero o _ y - en la cadena token y establecer el tipo como nombre de variable.
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
    void dirdcl(void), write_entry(char *, const char *, int);

    for (ns = 0; gettoken() == '*'; ) // Cuenta operadores puntero antes de cualquier otro token
        ++ns;
    dirdcl();
    while (ns-- > 0) // Por cada operador puntero escribir apuntador a en una cadena de salida.
        write_entry(out, " apuntador a", OUT);
}

char name[MAXTOKEN]; // Nombre de token
char out[MAXOUTLEN]; // Cadena de texto de salida
char *out_i = out; // Indice para escritura

void write_entry(char *o, const char *s, int type) { // Escribir el tipo (TOKEN o OUT) en su respectivo array, si hay espacio suficiente, si no, mandar error
    if (type == TOKEN) { 
        if (strlen(s) < MAXTOKEN)
            strcpy(o, s);
        else
            printf("Error: Entrada muy larga. (write_entry:token).\n");
    }
    else if (type == OUT) { 
        if (strlen(s) < (MAXOUTLEN - (out_i - out))) {
            strcpy(out_i, s);
            out_i += strlen(s); // Trabaja usando direccion como indice, por lo que es compatible con strcat y strcpy.
        }
        else
            printf("Error: Entrada muy larga. (write_entry:out).\n");
    }
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
        write_entry(name, token, TOKEN);
    else
        printf("Error: Nombre o (dcl) esperado y se recibio tokentype = %c = %d.\n", tokentype, tokentype);

    while ((type = gettoken()) == PARENS || type == BRACKETS) // Ver si el siguiente token son parentesis de funcion o corchetes de arreglo, y copiar en la cadena de salida lo que corresponda.
        if (type == PARENS)
            write_entry(out, " funcion que regresa", OUT);
        else {
            write_entry(out, " arreglo ", OUT);
            write_entry(out, token, OUT);
            write_entry(out, " de", OUT);
        }
}

char datatype[MAXTOKEN]; // Tipo de dato

int main () {
    while (gettoken() != EOF) { // Si el primer token no es EOF, es el tipo de dato. Se copia en su cadena y se cierra la cadena de salida.
        write_entry(datatype, token, TOKEN);
        out[0] = '\0';
        dcl(); // Se inicia la recursión de busqueda de tokens entre dcl y dirdcl. Si el ultimo token no es un '\n', hubo un error. Imprimir la salida.
        if (tokentype != '\n')
            printf("Error: Sintaxis tokentype = %c = %d.\n", tokentype, tokentype);
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}
