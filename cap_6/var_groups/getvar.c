#include <string.h>
#include <ctype.h>
#include "..\..\funciones_utiles\getch_ungetch.c"
#include "..\..\funciones_utiles\verify.c"

#define MAXWORDLEN 100

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

int nextword(int *c) {
    // LLega hasta la siguiente palabra o caracter importante
    // Retorna el caracter
    
    while (!isalpha(*c = getch()) && *c != '"' && *c != '\'' && *c != EOF && *c != '/' && *c != '#')
        ;

    return *c;
}

char *getvar (char *s, int max) { 
    // Lee la entrada y distigue entre palabras reservadas, nombres de funciones,
    // y variables, ya sea "comunes" o arreglos, y escribe los nombres de variables en *s.
    // Retorna s si hubo exito, nulo si no hay variables o hubo error.

    char tempword[MAXWORDLEN]; // Arreglo para guardar temporalmente la palabra, y puntero para escribirla.
    char *wrt_tempword = tempword;
    int c;
    
    *wrt_tempword = '\0';

    for (nextword(&c); c != EOF; ) { // Pedir letras hasta que getch se quede sin palabras...
        if(isalnum(c) && (wrt_tempword - tempword) < MAXWORDLEN) {
            if (wrt_tempword == tempword && isalpha(c)) { // Si el primer caracter es alfabetico, anotar
                *wrt_tempword++ = c;
                c = getch();
            }
            else if (wrt_tempword > tempword) { // Para cualquier otro caracter anotar libremente
                *wrt_tempword++ = c;
                c = getch();
            }
            else // Si el primer caracter es numerico, no es variable.
                nextword(&c);
        }

        else if ((wrt_tempword - tempword) >= MAXWORDLEN) { // Si no hay espacio mandar error.
            printf("Error: Palabra demasiado larga.\n");
            return NULL;
        }

        else if (isspace(c) || c == ';') { // Si es espacio o punto coma, cerrar la cadena temporal, y verificar si es palabra reservada.
            *wrt_tempword = '\0';
            
            if (!verify_token(tempword)) // Si no es cadena reservada, y la palabra tiene tamaño aceptable, dejar getch en la sig. palabra, escribir en s y retornar s. 
                return writeword(s, tempword, max);
            else { // Si es cadena reservada, limpiar cadena temporal y llegar hasta la siguiente palabra.
                wrt_tempword = tempword;
                nextword(&c);
            }
        }

        else if (c == '[') { // Si es un arreglo, dejar getch en la siguiente palabra, copiar en s y retornar s si hay espacio suficiente. 
            while ((c = getch()) != ']' && c != EOF) // Llegar hasta el fin de la declaracion o EOF si hay syntax error
                ;
            if (c == EOF) { // Si hubo EOF retornar error, si no, continuar
                printf("EOF Syntax Error.\n");
                return NULL;
            }
            *wrt_tempword = '\0';
            return writeword(s, tempword, max);
        }

        else if (c == '(') { // Si es una funcion, limpiar palabra temporal y llegar hasta la siguiente palabra
            wrt_tempword = tempword;
            while ((c = getch()) != ')' && c != EOF) // Llegar hasta el fin de la declaracion o EOF en syntax error
                    ;
            if (c == EOF) { // Si hay EOF retornar error
                printf("EOF Syntax Error.\n");
                return NULL;
            }
            nextword(&c);
        }

        else if (c == '"') { // Si es comilla doble, llegar hasta el fin del string o EOF, y luego a la siguiente palabra o comilla
            while ((c = getch()) != '"' && c != EOF) // Llegar hasta el fin de la declaracion o EOF en syntax error
                    ;
            if (c == EOF) { // Si hay EOF retornar error
                printf("EOF Syntax Error.\n");
                return NULL;
            }
            nextword(&c);
        }

        else if (c == '\'') { // Si es comilla simple, llegar al fin de la comilla simple e ir a la siguiente palabra.
            while ((c = getch()) != '\'' && c != EOF) // Llegar hasta el fin de la declaracion o EOF en syntax error
                    ;
            if (c == EOF) { // Si hay EOF retornar error
                printf("EOF Syntax Error.\n");
                return NULL;
            }
            nextword(&c);
        }

        else if (c == '/') { // Si es una diagonal o orden de preprocesador
            if ((c = getch()) == '/') { // Si es orden de prep, o el sig. c es diagonal, entonces llegar hasta la siguiente linea.
                while ((c = getch()) != '\n' && c != EOF) // Llegar hasta el fin de la declaracion o EOF en syntax error
                        ;
                if (c == EOF) { // Si hay EOF retornar error
                    printf("EOF Syntax Error.\n");
                    return NULL;
                }
                nextword(&c);
            }
            else // Si no es comentario, seguir hasta la siguiente palabra
                nextword(&c);
        }

        else if (c == '#') {
            while ((c = getch()) != '\n' && c != EOF) // Llegar hasta el fin de la declaracion o EOF en syntax error
                ;
            if (c == EOF) { // Si hay EOF retornar error
                printf("EOF Syntax Error.\n");
                return NULL;
            }
            nextword(&c);
        }

        else { // En cualquier otro caso, llegar hasta la siguiente palabra
            nextword(&c);
            if (c == EOF) { // Si hay EOF retornar error
                printf("EOF Syntax Error.\n");
                return NULL;
            }
        }
    }
    return NULL; // Retorno si no hay más variables.
}