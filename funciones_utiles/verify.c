#include <string.h>

// Funcion para comprobar que una palabra en particular es (o no) una palabra reservada de C, 
// considerando las que aparecen en el manual de usuario.

static char *reserved[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
    NULL
};

int verify_token (char *s) { // Compara con cada una de las palabras. Si es identica, retorna 1. Si termina sin retornar 1, retorna 0.
    int result, i;

    result = 0;
    for (i = 0; reserved[i]; ++i)
        if (strcmp(reserved[i], s) == 0)
            return result = 1;
    
    return result;
}