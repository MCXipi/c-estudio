#include <stdio.h>

/*Hacer una cuenta de cuantas palabras tienen X caracteres y representarlos con '-'
para un maximo de 9 caracteres de longitud*/
main(){
    int rep_longitud[10], ncar, c, i, n; /*¡Hay que declarar hasta los indices!*/

    ncar = 0;
    for (i = 1; i < 10; ++i)
        rep_longitud[i] = 0;

    while ((c = getchar()) != EOF){
        if (c != ' ' && c != '\n' && c != '\t')
            ++ncar;
        else{
            ++rep_longitud[ncar];
            ncar = 0;
        }
        /*Recordar que si hay más de una proposicion hay que usar llaves!*/
    }

    printf("Debug: Cantidades de palabras de X largo = "); /*Comprobar si se están contando bien las cantidades de palabras*/
    for (i = 1; i < 10; ++i){
        printf("%d ", rep_longitud[i]);
        printf("\n");
    }
    
    printf("Histograma de cantidad de palabras de longitudes entre 1 a 9 caracteres\n");
    for (i = 1; i < 10; ++i){
        printf("%d ", i);
        for (n = 1; n <= rep_longitud[i]; ++n)
            printf("-");
        printf("\n");
    }
}
/*Texto de prueba: "estas palabras tienen que ser contadas sin ningun error"*/