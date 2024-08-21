#include "cf.h"

#define MAXWORDS 500

struct word {
    char *word;
    int count;
} ;

struct word *words[MAXWORDS];

char *copy_word (char *s) {
    // Asigna espacio para la cadena s, y si fue exitoso copia la cadena.
    // En cualquier caso retorna el apuntador retornado por malloc.

    char *sp;
    sp = (char *) malloc(strlen(s) + 1);

    if (sp)
        strcpy(sp, s);
    return sp;
}

struct word *struct_save(char *word) {
    // Funcion que asigna espacio para una palabra y inicializa sus variables.
    // Retorna el espacio donde se asignó.
    
    struct word *p;

    p = (struct word *) malloc(sizeof(struct word));
    
    p->word = copy_word(word);
    p->count = 1;

    return p;
}

int lower_cmp (const char *cs, const char *ct) {
    // Funcion que hace comparacoin entre dos cadenas, sin distinguir mayusculas o minusculas, al hacerlas todas minusculas.
    // Copia la cadena cs en una temporal con los caracteres en minuscula, y repite con ct.
    // Retorna la evaluacion de strcmp.

    char temp_cs[MAXWORDLEN], temp_ct[MAXWORDLEN];
    int i;

    for (i = 0; cs[i]; ++i)
        temp_cs[i] = tolower(cs[i]);
    temp_cs[i] = '\0';
    
    for (i = 0; ct[i]; ++i)
        temp_ct[i] = tolower(ct[i]);
    temp_ct[i] = '\0';
    
    return strcmp(temp_cs, temp_ct);
}

int study_word (char *word, int *last) {
    // Funcion que para cada palabra que reciba buscará en el arreglo de palabras si existe. Si es así, aumenta la cuenta. Si no, crea su estructura.
    // Si se excede el numero de palabras imprime error.
    // Se decidió el uso de un arreglo debido al hecho de que no necesitamos ordenar alfabeticamente las palabras.

    int i;

    for (i = 0; words[i] && i < MAXWORDS - 1; ++i)
        if (lower_cmp(word, words[i]->word) == 0) {
            ++words[i]->count;
            return 0;
        }

    if (words[i] == NULL) {
        *last = i;
        words[i++] = struct_save(word);
        words[i] = NULL;
    }
    else if (i == MAXWORDS - 1)
        printf("Error: Too many words.\n");
    
    return 0;
}

void switch_structs(struct word *structs[], int a, int b) {
    // Funcion para intercambiar dos estructuras dentro del algoritmo qsort.

    struct word *temp;

    temp = structs[a];
    structs[a] = structs[b];
    structs[b] = temp;
}

void qsort_structs (struct word *structs[], int left, int right) {
    // Funcion que utiliza el algoritmo de ordenamiento qsort para ordenar las cuentas de las palabras en orden descendente.
    
    int i, mid, last;

    mid = (left + right) / 2;
    last = right;
    switch(structs, mid, right);

    if (left >= right)
        return;
    
    for (i = right; i >= left; --i) 
        if (structs[right]->count > structs[i]->count)
            switch_structs(structs, i, --last);
    
    switch_structs(structs, last, right);
    qsort_structs(structs, left, last - 1);
    qsort_structs(structs, last + 1, right);
}