#include "var_groups_header.h"

struct node {
    char *var; // Variable
    struct node *nequal_major; // n-equivalente lexicograficamente mayor
    struct node *nequal_lower; // n-equivalente lexicograficamente menor
    struct node *major; // n-distinto lexicograficamente mayor
    struct node *lower; // n-distinto lexicograficamente menor
};

char *strsave(char *s) {
    // Pedir un espacio en una direccion con malo
    // Si fue posible, copiar s en p.

    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p)
        strcpy(p, s);
    return p;
}

char *all_tolower(char *dest, char *src) {
    // Escribier en el puntero a char destino la cadena en src pero con los caracteres en minuscula

    char *p = src;

    for (; *p; p++)
        *dest++ = tolower(*p);
    *dest = '\0';

    return dest;
}

struct node *sort_node (struct node *to_check, char *s, int n) {
    // Verifica que el nodo a estudiar exista, y si no, lo crea asignandole espacio en memoria con sus funciones.
    // Si existe, compara el string en s con la variable, ambos en minusculas, y ve si s es mayor o menor
    // Si hay resultado en la comparacion, asigna el nodo que le corresponde a s con la direccion que retorna la recursion,
    // que puede ser la misma de antes, o la nueva en caso de que to_check antes fuese NULL.
    // Ignora variables repetidas.

    char temp_s[MAXWORDLEN];
    char temp_v[MAXWORDLEN];
    all_tolower(temp_s, s); // Convertir s y la variable en minusculas para comparar sin darle relevancia a eso.
    if (to_check != NULL)
        all_tolower(temp_v, to_check->var);

    if (to_check == NULL) { // Si no hay nodo, crear espacio para el nodo e inicializarlo
        to_check = (struct node *) malloc (sizeof(struct node));
        to_check->var = strsave(s);
        to_check->nequal_major = to_check->nequal_lower = to_check->major = to_check->lower = NULL;
    }

    else if (strncmp(temp_s, temp_v, n) > 0) // Si la cadena no es n-equivalente y mayor a la var, revisar la mayor que la var
        to_check->major = sort_node(to_check->major, s, n);

    else if (strncmp(temp_s, temp_v, n) < 0) // Si la cadena no es n-equivalente y menor a la var, revisar la menor que la var
        to_check->lower = sort_node(to_check->lower, s, n);

    else if (strncmp(temp_s, temp_v, n) == 0) // Si la cadena es n-equivalente
        if (strcmp(temp_s, temp_v) > 0) // Si es mayor a la variable, estudiar la n-equivalente mayor
            to_check->nequal_major = sort_node(to_check->nequal_major, s, n);
        else if (strcmp(temp_s, temp_v) < 0) // Si es mayor a la variable, estudiar la n-equivalente mayor
            to_check->nequal_lower = sort_node(to_check->nequal_lower, s, n); 
    
    return to_check;
}

void print_group (struct node *base) {
    // Comienza a imprimir la variable del nodo n-equivalente menor de la rama
    // Una vez impreso el nodo, se estudia cada rama de nodo n-equivalente mayor

    if (base->nequal_lower != NULL) // Llegar hasta el menor n-equivalente del grupo
        print_group(base->nequal_lower);
    
    printf("%s\n", base->var); // Imprimirlo

    if (base->nequal_major != NULL) // Si hay, empezar a imprimir grupo de mayor n-equivalente
        print_group(base->nequal_major); 
}

void search_groups(struct node *base, int n) {
    // Comienza en el nodo n-distinto menor y se llama a la funcion para imprimir el nodo n-equivalente menor de ese nodo.
    // Una vez se imprime la rama n-equivalente menor se imprime el nodo n-distinto y se comienza a imprimir la rama del nodo n-equivalente mayor

    int i;

    if (base->lower != NULL) // LLegar al nodo n-distinto menor
        search_groups(base->lower, n);
    
    printf("\nGrupo ");
    for(i = 0; i < n && base->var[i]; ++i)
        printf("%c", base->var[i]);
    printf(":\n");

    if (base->nequal_lower != NULL) // Empezar imprimiendo desde la rama del menor nodo n-equivalente al nodo n-distinto
        print_group(base->nequal_lower);

    printf("%s\n", base->var); // Imprimir el nodo n-distinto

    if (base->nequal_major != NULL) // Empezar a imprimir los nodos n-equivalente mayores que el nodo
        print_group(base->nequal_major);
    
    if (base->major != NULL) // Empezar a imprimir los nodos n-distintos mayores que el nodo
        search_groups(base->major, n);
}