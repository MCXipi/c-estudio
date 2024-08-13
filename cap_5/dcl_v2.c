#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "..\funciones_utiles\getch_ungetch.c"

// Ejercicios de la seccion 5.12

#define MAXTOKEN 100
#define MAXOUTLEN 1000

enum {NAME, PARENS, BRACKETS, TOKEN, OUT, DATATYPE};

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
            write_entry(token, "( )", TOKEN);
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

char name[MAXTOKEN]; // Nombre de token
char out[MAXOUTLEN]; // Cadena de texto de salida
char *out_i = out; // Indice para escritura

void write_entry(char *o, const char *s, int type) { // Escribir el tipo (TOKEN o OUT) en su respectivo array, si hay espacio suficiente, si no, mandar error
    size_t s_len = strlen(s);
    extern char *datatype_i, *datatype;

    if (type == TOKEN) { 
        if (s_len < MAXTOKEN)
            strcpy(o, s);
        else
            printf("Error: Entrada muy larga. (write_entry:token).\n");
    }
    else if (type == OUT) { 
        if (s_len < (MAXOUTLEN - (out_i - out))) {
            strcpy(out_i, s);
            out_i += s_len; // Trabaja usando direccion como indice, por lo que es compatible con strcat y strcpy.
        }
        else
            printf("Error: Entrada muy larga. (write_entry:out).\n");
    }
    else if (type == DATATYPE) {
        if (s_len < (MAXTOKEN - (datatype_i - datatype))) {
            strcpy(datatype_i, s);
            datatype_i += s_len; 
            *datatype_i++ = ' '; // Agregar espacio al final del token de tipo.
        }
        else
            printf("Error: Entrada muy larga. (write_entry:datatype).\n");
    }
}

void dcl () { // Para reconocer lo que en el libro son las declaraciones *s
    int ns; // Cuenta de operadores punteros
    extern char out[];
    void dirdcl(void);

    for (ns = 0; gettoken() == '*'; ) // Cuenta operadores puntero antes de cualquier otro token
        ++ns;
    dirdcl();
    while (ns-- > 0) // Por cada operador puntero escribir apuntador a en una cadena de salida.
        write_entry(out, " apuntador a", OUT);
}

void get_args() { // Obtiene cada argumento de una funcion separada por comas y las escribe en la cadena de salida.
    char argname[MAXTOKEN];
    char argtype[MAXTOKEN];
    char argbody[MAXTOKEN];
    char temp[MAXTOKEN];
    char copy_temp[MAXTOKEN];
    
    int c, i;
    size_t s_len;
    
    char *argtype_i = argtype;
    char *argbody_i = argbody;
    *argbody_i = '\0'; // Cuerpo del argumento cerrado

    while((c = getch()) == ' ' || c == '\t') // Saltar espacios
        ;
    ungetch(c);

    while((c = getch()) != ')' && c != '\n') { // Hasta que se acaben los argumentos o termine la linea en caso de error
        ungetch(c);

        for(i = 0; isalnum(c = getch()) && i < MAXTOKEN; ++i) // Anotar token en cadena temporal y ver su tipo, para asi distribuirlo en cadenas para cada tipo
            temp[i] = c;

        if (i == 0 && !isspace(c)) // Si el primer caracter no es una letra, y tampoco es un espacio, anotarla de todas maneras en temp
            temp[i++] = c;
        else if (!isspace(c)) // Si i != 0 pero no es alfanumerico, devolver a buff.
            ungetch(c);
        temp[i] = '\0';
        
        s_len = strlen(temp);
        if (s_len > 1 && type_verification(temp) && MAXTOKEN - (argtype_i - argtype) > s_len) { // Si es un tipo y hay espacio, anotar en la cadena de tipo
            strcpy(argtype_i, temp);
            argtype_i += s_len;
            *argtype_i++ = ' ';
        }
        else if (s_len >= 1 && isalpha(temp[0]) && MAXTOKEN > s_len) {  // Si es un nombre aunque sea de largo 1
            *argtype_i = '\0'; // Cerrar cadena de tipo
            sprintf(copy_temp, " %s: ", temp);
            strcpy(argname, copy_temp);
        }
        else if (s_len == 1) { // Si la cadena obtenida solo es de un caracter, osea no es un nombre ni tipo
            if (temp[0] == '[') { // Si es corchete, obtener todo lo de dentro del corchete y escribir en el cuerpo del argumento
                for(i; (temp[i] = c = getch()) != ']' && c != '\n'; ++i)
                    ;
                temp[++i] = '\0';
                sprintf(copy_temp, " arreglo %s de %s", temp, argbody);
                strcpy(argbody, copy_temp);
            }
            else if (temp[0] == '*') { // Si es un asterisco, poner apuntador a antes del cuerpo del argumento y copiarlo si hay espacio
                sprintf(copy_temp, " apuntador a %s", argbody);
                if (strlen(copy_temp) < MAXTOKEN)
                    strcpy(argbody, copy_temp);
            }
            else if (temp[0] == ',') { // Si es una coma, escribir el nombre, cuerpo y tipo del argumento, limpiar cadena de cuerpo y tipo, y escribir la coma
                write_entry(out, argname, OUT);
                write_entry(out, argbody, OUT);
                write_entry(out, argtype, OUT);
                *argbody = '\0';
                argtype_i = argtype;
                *argtype_i = '\0';
                write_entry(out, temp, OUT); // Escribir la coma
            }
            else // En cualquier otro caso, es un error.
                printf("Error: Argumento invalido %s.\n", temp);
        }
    }
    if (c == ')') { // Si el while termino como corresponde por parentesis, escribir argumento y la coma
        write_entry(out, argname, OUT);
        write_entry(out, argbody, OUT);
        write_entry(out, argtype, OUT);
        write_entry(out, ",", OUT);
    }
    else
        printf("Error: Falta ).\n");
}

void dirdcl () { // Para reconocer en el libro lo que son las declaraciones directas nombre, (dcl), dcl-directa(), dcl-directa[tamaño-opcional]
    int type;
    extern char name[], out[];

    if (tokentype == '(') { // Si el token ignorado por dcl es parentesis, ejecutar dcl recursivamente para todo lo interno. Si el ultimo token no es parentesis, imprimir error
        dcl();
        if (tokentype != ')')
            printf("Error: Falta ).\n");
    }
    else if (tokentype == NAME) { // Si el token ignorado en dcl es un nombre, copiar el nombre en la cadena para nombres, o enviar error.
        write_entry(name, token, TOKEN);
    }
    else
        printf("Error: Nombre o (dcl) esperado y se recibio tokentype = %c = %d.\n", tokentype, tokentype);

    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') { // Ver si el siguiente token son parentesis de funcion o corchetes de arreglo, y copiar en la cadena de salida lo que corresponda.
        if (type == '(') {
            write_entry(out, " funcion de argumentos", OUT);
            get_args();
            write_entry(out, " que regresa", OUT);
        }
        else if (type == PARENS)
            write_entry(out, " funcion que regresa", OUT);
        else {
            write_entry(out, " arreglo ", OUT);
            write_entry(out, token, OUT);
            write_entry(out, " de", OUT);
        }
    }
}

char datatype[MAXTOKEN]; // Tipo de dato
char *datatype_i = datatype;

int type_verification (const char *t) { // Verificar que el token entregado es un token de tipo valido en C. Si no, se dará por terminada la escritura de datatype-
    const char *type_tokens[] = {"int", "char", "float", "long", "double", "register", "const", "void", "signed", "unsigned", "static", '\0'};
    char **type_tokens_i;
    int result = 0;
    
    for (type_tokens_i = type_tokens; *type_tokens_i; type_tokens_i++) { // Para cada elemento en la lista de tokens validos, comparar con la cadena. Si es valida, el resultado sera 1 o "verdadero"
        if (strcmp(t, *type_tokens_i) == 0)
            result = 1;
    }
    return result;
}

void ungetch_line (char *s) { // Ingresar toda una linea al buffer para que quede escrita bien y limpiar la linea vaciada
    size_t l_pos = strlen(s) - 1;

    for (l_pos; *(s + l_pos); --l_pos)
        ungetch(*(s + l_pos));
    *s = '\0';
}

int get_datatype () { // Funcion para obtener el tipo de dato al principio de cada linea. Cuando termine con un token no verificado, envia todo el token al buffer.
    int type;
    
    for (; (type = gettoken()) == NAME && type_verification(token); ) // Mientras el token obtenido sea valido, y sea un nombre, escribirlo en datatype y pedir el siguiente
        write_entry(datatype, token, DATATYPE);
    *datatype_i = '\0';

    if (type == NAME || type == PARENS || type == BRACKETS) // Si el token no valido como tipo es nombre, parentesis o corchetes, mandar a buffer el token. Si no, mandar a buffer el caracter regresado por gettoken.
        ungetch_line(token);
    else
        ungetch(type);
    return type;
}

void clean_all () {
    datatype_i = datatype;
    out_i = out;
}

int main () {
    while (get_datatype() != EOF) { // Si el primer token no es EOF, es el tipo de dato.
        out[0] = '\0';
        dcl(); // Se inicia la recursión de busqueda de tokens entre dcl y dirdcl. Si el ultimo token no es un '\n', hubo un error. Imprimir la salida.
        if (tokentype != '\n')
            printf("Error: Sintaxis tokentype = %c = %d.\n", tokentype, tokentype);
        printf("%s: %s %s\n", name, out, datatype);
        clean_all();
    }
    return 0;
}
