#include "var_groups_header.h"
#include "getvar.c"
#include "tree_management.c"

// Ejercicio 6-2.

int main (int argc, char *argv[]) {
    int n, i;
    char var[MAXWORDLEN];
    struct node *root;

    n = 6; // Valor por defecto.
    root = NULL; // Para inicializar el ordenamiento

    if (argc > 2) { // Si hay mas argumentos que los esperados, enviar modo de uso
        printf(".\\vargroups [-n] (0 <= n <= 6)\n");
        return -1;
    }
    else if (argc == 2) { // Si hay dos argumentos
        for (i = 1; *(argv[1] + i); ++i) // Para cada caracter en la opcion, pasado el caracter -, si hay mas de un digito, o no es digito, enviar uso.
            if (!isdigit(*(argv[1] + i)) || i > 1) {
                printf(".\\vargroups [-n] (0 <= n <= 6)\n");
                return -1;
            }
        else
            n = atoi(argv[1] + 1); // Si esta bien el argumento, escribir n.
    }

    if (getvar(var, MAXWORDLEN) != NULL) // Inicializar el nodo raiz.
        root = sort_node(root, var, n);

    while (getvar(var, MAXWORDLEN) != NULL) { // Mientras hayan variables ordenarlos en el arbol
        sort_node(root, var, n);
    }
    search_groups(root, n); // Imprimir nodos.

    return 0;
}
