#include <stdio.h>

main(){
    int c, i, nwhite, nother; /*Caracter, indice, numero de espacios blancos, numero de otros caracteres.*/
    int ndigit[10];

    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0; /*Se inicializa cada indice del arreglo*/
    
    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c - '0']; /*¿Para que -'0'? --> Posiblemente para hacer la conversión a entero y asi volverlo un indice válido.*/
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    /*El while no requiere llaves para una secuencia de if-else if- else*/

    printf("Digitos = ");
    for (i = 0; i < 10; ++i)
        printf("%d ", ndigit[i]);
    printf(". Espacios en blanco: %d. Otros caracteres: %d", nwhite, nother);
}
/*Texto de prueba: '   hola 1234 56789 0        ' que tiene 2 tabs, 6 espacios en blanco.*/