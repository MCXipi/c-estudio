#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../funciones_utiles/getch_ungetch.c"

// Copia del ejemplo de la seccion 6.3 para trabajo de ejercicio 6-1.

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0]) // Tamaño del arreglo keytab, inmune a cambios de tipo por dividir por keytab[0]

enum type {OTHER, COMMENT, PREPROCCESOR, STRING};

enum bool {FALSE, TRUE};

struct key {
    char *word;
    int count;
} 
keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "double", 0,
    "float", 0,
    "int", 0,
    "long", 0,
    "null", 0,
    "register", 0,
    "static", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

int getword_old (char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch())) // Ignorar espacios
        ;
    
    if (c != EOF) // Si c no es EOF, anotarlo en la palabra
        *w++ = c;
    if (!isalpha(c)) { // Como c no es EOF, si no es alfanumerico, es un simbolo. Se cierra la palabra y se retorna el simbolo.
        *w = '\0';
        return c;
    }

    for ( ; --lim > 0; w++) // Mientras haya espacio (El limite disminuye conforme se usan espacios en word)
        if (!isalnum(*w = getch())) { // Si el caracter recibido y escrito en word no es alfanumerico, guardar caracter en buffer y salir del for sin aumentar w
            ungetch(*w);
            break;
        }
    *w = '\0'; // Cerrar la palabra, reemplazando cualquier caracter no alfanumerico que haya detenido el for y que se haya escrito
    return word[0];
}

int getword_new (char *word, int lim) {
    int c, type = OTHER, next;
    char *w = word;

    while (isspace(c = getch())) // Ignorar espacios
        ;
    
    if (c != EOF) // Si c no es EOF, anotarlo en la palabra
        *w++ = c;
    else
        return c;
    
    if (!isalpha(c)) {// Si c no es alfanumerico
        if (!isgraph(c = getch()) && !isspace(c)) { // Si el caracter siguiente no es grafico y tampoco un espacio, es un simbolo unico. Cerrar word y retornar
            *w = '\0';
            return c;
        }
        else if (isspace(c)) { // Pero si el caracter siguiente es espacio, anotar todos los espacios hasta que quede un caracter grafico, el cual se devuelve a buffer
            *w++ = c;
            for( ; --lim > 0 && (*w = getch()) == ' ' || *w == '\t'; w++)
                ;
            ungetch(*w);
        }
        else  // Y si el caracter siguiente es grafico, retornarlo al buffer
            ungetch(c);
        
        switch(*(w - 1)) { // Determinar el tipo de palabra a partir del primer caracter, osea el simbolo
                case '/':
                    type = COMMENT;
                    break;
                case '#':
                    type = PREPROCCESOR;
                    break;
                case '"':
                    type = STRING;
                    break;
            }
    }
    
    for (next = TRUE ; next && --lim > 0; w++) {// Mientras haya espacio (El limite disminuye conforme se usan espacios en word)
        switch(type) {
            case PREPROCCESOR: // Si es orden para preprocesador, escribir palabra hasta que haya un ; o se acabe la linea
                if ((*w = getch()) == ';' || *w == '\n') {
                    if (*w == '\n')
                        *w = '\0';
                    next = FALSE;
                }
                break;
            case STRING: // Si es un string, escribir hastas comilla doble o se acabe la linea
                if ((*w = getch()) == '"' || *w == '\n') {
                    if (*w == '\n')
                        *w = '\0';
                    next = FALSE;
                }
                break;
            case COMMENT: // Si es comentario, escribir hasta que haya un punto o se acabe la linea
                if ((*w = getch()) == '.' || *w == '\n') {
                    if (*w == '\n')
                        *w = '\0';
                    next = FALSE;
                }
                break;
            case OTHER: // Si es una palabra cualquiera o no identificada, anotar hasta que haya un espacio
                if (!isgraph(*w = getch())) { // Si el caracter recibido y escrito en word no es alfanumerico, guardar caracter en buffer y salir del for sin aumentar w
                    *w = '\0';
                    next = FALSE;
                }
                break;
        }
    }
    *w = '\0'; // Cerrar la palabra, reemplazando cualquier caracter no alfanumerico que haya detenido el for y que se haya escrito
    return word[0];
}

int binsearch (char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) // Si la palabra a comparar es lexicograficamente menor a la de la mitad del intervalo estudiado, bajar el intervalo por debajo de la mitad
            high = mid - 1;
        else if (cond > 0) // Si la palabra es lexicograficamente mayor, subir el intervalo de estudio partiendo despues de la mitad
            low = mid + 1;
        else
            return mid; // Si es 0, son iguales, y se retorna el indice
    }
    return -1; // Si no hubo retorno de mid, devolver indice inexistente
}

int main () {
    int n;
    char word[MAXWORD];

    while(getword_new(word, MAXWORD) != EOF) { // Mientras la palabra obtenida no sea EOF
        if (isalpha(word[0])) // Si la palabra empieza por caracter alfanumerico
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) // Y si la palabra esta en keytab, en un indice n mayor o igual a 0, subir su cuenta en 1 en su indice n.
                keytab[n].count++;
        printf("Word: %s .\n", word);
    }

    for (n = 0; n < NKEYS; n++) // Imprimir todas las palabras que estén al menos una vez, con su cantidad.
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);

    return 0;
}