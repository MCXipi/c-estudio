
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "..\funciones_utiles\getch_ungetch.c"

#define HASHSIZE 101

// ====================== Ejercicio 6-5 ======================

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned int hash (char *s) {
    // Funcion que asigna un indice entre 0 y hashsize - 1 a partir de una cadena s, para asignarle una posicion a s y su definicion en hasthab.
    // Unsigned int asegura que el reusltado sea positivo, es decir, un indice.

    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval; // 31 -> constante arbitraria
    
    return hashval % HASHSIZE; // Asegura valor entre 0 y hashsize - 1
}

struct nlist *lookup (char *s) {
    // Funcion que busca la cadena s en la tabla hashtab.
    // Busca si, en el indice entregado por el hash equivalente a la cadena s, hay un nombre y definicion, y si es el mismo nombre, retorna un puntero.
    // Avanza hasta que se acaben las cadenas que tengan el mismo hash. Si no se encuentra s, retorna nulo. 

    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

char *copy_word (char *s) {
    // Asigna espacio para la cadena s, y si fue exitoso copia la cadena.
    // En cualquier caso retorna el apuntador retornado por malloc.

    char *sp;
    sp = (char *) malloc(strlen(s) + 1);

    if (sp)
        strcpy(sp, s);
    return sp;
}

void reasign (char *name) {
    // Funcion que reordena los bloques con el hash de name.
    // Si el primer bloque no es el que tiene el nombre name, estudia cada uno para ver si el siguiente es el de name.
    // Si el next del bloque es name, hace que el next ahora sea el next de name.
    // Si el primer bloque es el de nombre name, hace que el primer bloque ahora sea su next.

    struct nlist *np;
    unsigned int hashval;

    hashval = hash(name);
    np = hashtab[hashval];

    if (np != NULL && (strcmp(np->name, name) != 0))
        for (np; np != NULL; np = np->next){
            if (np->next != NULL && strcmp(np->next->name, name) == 0)  // Si name del bloque siguiente efectivamente es name.
                np->next = np->next->next; // Hacer el next del bloque actual, el next del bloque siguiente.
        }
    else if (np != NULL && strcmp(np->name, name) == 0)
        hashtab[hashval] = np->next;
    
}

int undef (char *name) {
    // Funcion que limpia la estructura que tenga el nombre name. Retorna int != 0 si hubo exito, 0 si hubo error.
    // Busca con lookup si existe direccion de estructura con ese nombre, y si hay, limpia la definicion, el nombre, reordena los bloques ligados, y limpia las direcciones.

    struct nlist *np;
    unsigned int hashval;

    hashval = hash(name);

    if ((np = lookup(name)) != NULL) {
        reasign(name);
        free((void *) np->defn);
        free((void *) np->name);
        free((void *) np->next);
        free((void *) np);
        return hashval;
    }
    else
        return 0;
}

struct nlist *install (char *name, char *defn) {
    // Funcion que instala un nombre con su definicion en hashtab, y retorna un puntero segun los resultados
    // Si el nombre no está en la tabla, crea una volviendola el primer elemento en la fila, desplazando cualquier otra que haya en la posicion siguiente.
    // Si ya existe, libera la definicion.
    // En ambos casos se estudia si la definicion se pudo copiar correctamente. Si es asi, se retorna el puntero a la struct. Si no, se retorna nulo.

    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = copy_word(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval]; // Pone el elemento en hashtab[hashval] como su siguiente, y se pone en la primera posicion.
        hashtab[hashval] = np;
    }
    else
        free((void *) np->defn);

    if ((np->defn = copy_word(defn)) == NULL)
        return NULL;
    return np;
}
