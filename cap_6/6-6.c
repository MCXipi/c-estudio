#include "hashtab.c"

#define MAXLEN 100

// ====================== Ejercicio 6-6 ======================

char *getcon (char *fname, char *fdefn, int max) {
    // Funcion que obtiene las variables name y defn desde una declaracion de preprocesador 
    // Considerando la declaracion en formato #define "nombre" "defn"\n
    // Se obtiene la palabra que está directamente despues de #, y comprueba que sea "define". Si no es, no hace nada
    // Si es define, obtiene el texto hasta el siguiente espacio que correspondría a name, y el texto hasta '\n' que corresponde a defn, si es que hay.
    // Retorna el puntero de fname si escribió con exito. NULL si no pudo escribir nada o terminó la entrada.
    // Imprime a medida que llega entrada

    int c, i;
    char temp[MAXLEN];

    while ((c = getch()) != EOF) {
        ungetch(c);
        
        for (i = 0; !isspace(c = getch()); ++i)
            temp[i] = c;
        temp[i] = '\0';

        printf("%s ", temp);

        if (strcmp(temp, "define") == 0) {
            for (i = 0; i < max && !isspace(c = getch()); ++i)
                *(fname + i) = c;
            *(fname + i) = '\0';

            printf("%s ", fname);

            while(c != '\n' && isspace(c = getch()))
                printf("%c", c);
            ungetch(c);
            
            if (c != '\n') {
                for (i = 0; i < max && (c = getch()) != '\n'; ++i)
                    *(fdefn + i) = c;
                *(fdefn + i) = '\0';
                printf("%s", fdefn);
                if (c == '\n')
                    printf("%c", '\n');
            }
            else
                *(fdefn) = '\0';
            
            return fname;
        }
        else {
            while((c = getch()) != '\n')
                printf("%c", c);   
            if (c == '\n')
                printf("%c", '\n');
            return NULL;   
        }
    }
    return NULL;
}

void print_string(int *c) {
    // Programa que se encarga de imprimir una cadena, sin hacer distinciones, para lo que salta los escapes \algo.

    printf("%c", *c);
    while((*c = getch()) != '"') {
        printf("%c", *c);
        if (*c == '\\')
            printf("%c", *c = getch());
    }
    printf("%c", '"');
}

void print_comment(int *c) {
    // Programa que se encarga de imprimir comentarios, considerando que terminan en '\n'.

    printf("//");
    while((*c = getch()) != '\n')
        printf("%c", *c);
    if (*c == '\n')
        printf("%c", '\n');
}

int main () {
    // Programa que lee la entrada, identifica ordenes #define para guardar y reemplazar macros.
    // Identifica si la linea es orden de preprocesador y llama a la funcion getcon(), para que distinga si "sirve" o no. Deja siempre en la sgte linea.
    // Identifica tambien cuando el caracter es alfabetico, obtiene su palabra, revisa si corresponde a un macro e imprime su definicion, o la palabra como tal si no es.
    // Identifica si se abre una cadena, para lo que se llama a su funcion print_string() para su impresion. Idem con los comentarios y print_comment().
    // Para cualquier otro caracter imprime.

    char name[MAXLEN], defn[MAXLEN], temptoken[MAXLEN];
    int i, c;
    struct nlist *np; 

    while((c = getch()) != EOF) {
        if (c == '#') {
            printf("%c", c);
            if (getcon(name, defn, MAXLEN) != NULL ) 
                install(name, defn);
        }

        else if (isalpha(c)) {
            ungetch(c);

            for (i = 0; isalpha(c = getch()) || c == '_'; ++i)
                temptoken[i] = c;
            temptoken[i] = '\0';
            ungetch(c);
    
            if ((np = lookup(temptoken)) != NULL)
                printf("%s", np->defn);
            else
                printf("%s", temptoken);
        }

        else if (c == '"') {
            print_string(&c);
        }

        else if (c == '/')
            if ((c = getch()) == '/') 
                print_comment(&c);
            else {
                printf("%c", c);
                ungetch(c);
            }
        else
            printf("%c", c);
    }
}

// cl defineproc.c; Get-Content hashtab_test.c | .\defineproc > hashtab_testr.c