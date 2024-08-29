#include "cf.h"
#include "get_word.c"
#include "words_management.c"

// Ejercicio 6-4.

int main () {
    // Funcion que obtiene palabra con getword y la ordena con study_word. Luego llama para que estas sean ordenadas y finalmente imprime.
    // Inicializa el arreglo de structs de palabras con el primer elemento nulo.

    int i, last_i;
    char word[MAXWORDLEN];
    
    words[0] = NULL;

    while (get_word(word, MAXWORDLEN) != NULL) 
        study_word(word, &last_i);
   
    qsort_structs(words, 0, last_i);

    for (i = 0; words[i]; ++i)
        printf(words[i]->count == 1 ? "%2d ocurrencia de  \"%s\".\n" : "%2d ocurrencias de \"%s\".\n", words[i]->count, words[i]->word);

    return 0;
}