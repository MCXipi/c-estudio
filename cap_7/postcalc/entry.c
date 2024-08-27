#include "defs.h"

// Funciones de entrada y obtención de operando/operador de la calculadora.

void safentry (char *writeto, int max) {
    // Funcion que obtiene una entrada de manera literal, y la escribe en writeto, sin pasarse del limite establecido por max

    char *p, c;

    for (p = writeto; --max >= 0 && (c = getchar()) != '\n' && c != EOF; ++p)
        *p = tolower(c);
    *p = '\0';
}

void clear_entry(char *entry) {
    *entry = '\0';
}

int getop (char *opstr, char *entry) {
    // Funcion que obtiene un operando u operador mediante sscanf y una entrada obtenida de forma segura, y lo escribe en opstr.
    // Limpia la entrada una vez leida, para evitar bucles sin fin.
    // Se asegura la lectura de solo un elemento separado por espacios. Que sirva o no depende de calc.
    // Retorna puntero de opstr si escribió con exito, o NULL si hubo error.
    
    int result;
    
    result = sscanf(entry, "%s", opstr);
    clear_entry(entry);

    if (result == EOF || result == 0) {
        safentry(entry, MAXLEN);
        result = getop(opstr, entry);
    }

    return result;
}

int typeop (char *opstr) {
    // Funcion que obtiene el tipo de entrada dado a la calculadora.
    // Considera un numero a una cadena de solo digitos y una coma o punto.
    // Considera una operacion a un simbolo unico.
    // Considera una cadena a cualquier sucesión de caracteres alfabéticos.
    // Retorna el tipo NUM, OP, STR o INV al ser invalido.

    char *p;
    int point;

    point = 1;
    p = opstr;

    if (isdigit(*p)) {
        for (p; *p != '\0' && (isdigit(*p) || *p == '.' || *p == ','); ++p)
            if (*p == '.' || *p == ',')
                --point;
        if (*p == '\0' && point >= 0)
            return NUM;
        else
            return INV;
    }
    else if (isalpha(*p)) {
        for (p; *p != '\0' && isalpha(*p); ++p)
            ;
        if (*p == '\0')
            return STR;
        else
            return INV;
    }
    else if (ispunct(*p) && strlen(p) == 1)
        return OP;
    else
        return INV;
}

void clear_screen() {
    // Limpiar terminal y mostrar ultimo numero guardado.
    // Creada para limpiar el codigo de repeticiones.

    system("cls");
    printf("\t%g\n", getlast());
}