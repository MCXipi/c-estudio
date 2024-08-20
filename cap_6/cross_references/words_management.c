#include "cf.h"

enum {WORD, EQ};

struct word {
    char *word;
    int line;
    struct word *another_lower;
    struct word *another_major;
    struct equal_word *equal_branch;
};

struct equal_word {
    int line;
    struct equal_word *next;
};

char *copy_word (char *s) {
    // Asigna espacio para la cadena s, y si fue exitoso copia la cadena.
    // En cualquier caso retorna el apuntador retornado por malloc.

    char *sp;
    sp = (char *) malloc(strlen(s) + 1);

    if (sp)
        strcpy(sp, s);
    return sp;
}

void *struct_alloc(int type) {
    // Funcion que le asigna espacio a alguno de los structs, indicados por type como WORD o EQ.
    // Dependiendo del tipo, cambia el tamaño a pedir a malloc. Retorna direccion libre o NULL.
   
    if (type == WORD) 
        return malloc(sizeof(struct word));
    else if (type == EQ) 
        return malloc(sizeof(struct equal_word));

    return NULL;
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

struct equal_word *eqword_sort (struct equal_word *to_study, int nline) {
    // Funcion que trabaja en la rama de palabras iguales con la linea en la que aparecen.
    // Si el nodo ya está utilizado, trabaja con el siguiente nodo
    // Si el nodo está libre (NULL) lo crea.

    if (to_study == NULL) {
        to_study = (struct equal_word *) struct_alloc(EQ);
        to_study->line = nline;
        to_study->next = NULL;
    }
    else
        to_study->next = eqword_sort(to_study->next, nline);
    
    return to_study;
}

struct word *sort_word (struct word *to_study, char *word, int nline) {
    // Funcion que revisa si la palabra en el struct to study es la misma que word, comparando en minusculas.
    // Si no existe siguiente palabra, la crea.
    // Si no es, busca en la siguiente palabra.
    // Si es, comienza el trabajo en la rama de aparicion de palabra
    // Deja palabras en orden de llegada y aparicion.

    if (to_study == NULL) {
        to_study = (struct word *) struct_alloc(WORD);
        to_study->word = copy_word(word);
        to_study->line = nline;
        to_study->another_lower = NULL;
        to_study->another_major = NULL;
        to_study->equal_branch = NULL;
    }

    else if (lower_cmp(word, to_study->word) < 0) 
        to_study->another_lower = sort_word(to_study->another_lower, word, nline);
    
    else if (lower_cmp(word, to_study->word) > 0) 
        to_study->another_major = sort_word(to_study->another_major, word, nline);
    
    else
        to_study->equal_branch = eqword_sort(to_study->equal_branch, nline);
    
    return to_study;    
}

void print_branch(struct equal_word *str) {
    // Funcion para imprimir toda una branch de una misma palabra con distintas apariciones.
    // Imprime el n° de linea y se llama recursivamente con la siguiente palabra, si hay.
    // Que el nodo mismo exista en el primer llamado depende de get_branch_toprint()

    printf(", %d", str->line);
    
    if (str->next != NULL)
        print_branch(str->next);
}

void get_branch_toprint(struct word *str) {
    // Funcion para imprimir cada palabra y sus lineas
    // Imprime la palabra y su linea de aparicion, luego las demás apariciones si existen, y continua hacia la siguiente palabra, si existe.
    // Que exista al menos un nodo depende de main.
    if (str->another_lower != NULL)
        get_branch_toprint(str->another_lower);

    printf(str->equal_branch != NULL ? "%s, en las lineas %d" : "%s, en la linea %d" , str->word, str->line); // Verifica si hay mas apariciones para poner "linea" o "lineas"

    if (str->equal_branch != NULL)
        print_branch(str->equal_branch);
    printf(".\n");

    if (str->another_major != NULL)
        get_branch_toprint(str->another_major);
}