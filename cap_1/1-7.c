#include <stdio.h>

/*Caracter debe ser un int porque en realidad asegura la funcionalidad del código.*/
int caracter; 
/*Hipotesis: caracter como char funciona de todas formas por el cambio de tipo automatico*/

main(){
    /*Estudio: Si el if se imprime, tengo la razón y el int establecido como char se vuelve un int nuevamente al comparar (O algo asi)*/
    if ("1" == 1){
        printf("Funciona");
    }
    /*No pasa. Mi hipotesis era falsa*/
    /*Quiero saber el valor de eof*/
    printf("El valor de EOF es: %d\n", EOF); /*EOF es simbolicamente -1, pero no es igual a un entero -1 ni tampoco a un char -1*/
    caracter = getchar();
    while(caracter != EOF){
        putchar(caracter);
        caracter = getchar();
    }
    printf("Hecho!");
}

/*Conclusión: Funciona porque char tiene dos tipos. Unsigned y signed char. Podría ser que se esté tratando char como un signed char. Es decir, un solo char puede tomar valores numericos entre -127 a 128. Como getchar va pasando caracter por caracter como entero, este podría nunca sobrepasar el "limite", y además, coincidir con EOF que puede que sea un numero negativo. Es por esto que si se define caracter como un unsigned char, ahi si que el código se rompe.*/

/*¿Hay que tener fe para comprender el -1 EOF?*/