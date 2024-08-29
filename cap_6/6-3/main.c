#include "cf.h"
#include "get_word.c"
#include "words_management.c"

// Ejercicio 6-3.

int main () {
    // Obtiene palabra en get_word y la ordena con sort_word. LLama a imprimir al final.
    // Inicializa una primera palabra con direccion nula.

    char word[MAXWORDLEN];
    int nline;
    struct word *root;

    nline = 1;
    root = NULL;
    
    while (get_word(word, MAXWORDLEN, &nline) != NULL)
        root = sort_word(root, word, nline);
   
    if (root != NULL)
        get_branch_toprint(root);
    
    return 0;
}