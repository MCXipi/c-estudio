#include <stdio.h>
#include <ctype.h>

// Funcion que quita el \n y \t del final de una cadena.
void trim(char *s) {

    for (; *s; ++s)  // Dejar a *s hasta que sea \0
        ;
    for (--s; isspace(*s); --s) // Empezar a retroceder s mientras sean espacios en blanco, tabuladores, nuevalinea, etc.
        ;
    
    if (!isspace(*s)) // Si a la letra a la que se llego no es un espacio
        *++s = '\0'; // Colocar el fin de linea.
}