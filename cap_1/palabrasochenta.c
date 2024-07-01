#include <stdio.h>

/*Una función para recibir palabras, una para contar caracteres, y luego imprimir con main las palabras con longitud mayor a 80*/

#define MAX 100 /*Constantes simbolicas como buena costumbre*/

void getline(char[], int); /*Getline debe recibir un arreglo para poner la palabra, y un int que limite el tamaño de la palabra a ingresar*/
int count(char[]); /*count debe recibir un arreglo de caracteres para contar*/

void getline(char espacio[], int limite){
    int i, c;
    for (i = 0; i < limite - 1 && (c = getchar()) != EOF && c != '\n'; ++i) /*Puede que limite - 1 implique un uso del ultimo espacio limpio y no un reemplazo, y nuncah habra overflow*/
        espacio[i] = c;
    if (espacio[i] == '\n'){
        espacio[i] = '\n';
        ++i;
    }
    espacio[i] = '\0';
}

int count(char palabra[]){
    int i, cuenta;
    cuenta = i = 0;

    while (palabra[i] != '\0'){
        ++cuenta;
        ++i;
    }

    return cuenta;
}

void main(){
    char palabra[MAX];
    int largo, i;

    getline(palabra, MAX);
    largo = count(palabra);

    if (largo > 80)
        printf("%s", palabra);
    else
        printf("Tu palabra es muy corta.");

}
