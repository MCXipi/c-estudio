#include <stdio.h>

main(){
    double nc;
    for (nc = 0; getchar() != EOF; ++nc)
        printf("Valor de nc: %.0f\n", nc);
        ; /*for debe tener cuerpo. Haciendo una proposición nula se satisface el requisito.*/
    printf("%.0f\n", nc);
}
/*Se verifica la prueba, se ejecuta el cuerpo, y se aplica el incremento para el proximo ciclo.*/