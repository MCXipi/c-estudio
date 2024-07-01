#include <stdio.h>

/*Reemplazar los espacios en blancos por la minima cantidad de t y rellenar con blancos*/

#define MAX 1000
#define N 8

void getline(char[], int);

void getline(char espacio[], int limite) {
    int indice, caracter, blancos, tabs, i, esp_blancos;

    blancos = 0;
    
    for (indice = 0; indice < limite - 1 && (caracter = getchar()) != EOF && caracter != '\n'; ++indice){
        espacio[indice] = caracter;
        if (espacio[indice] == ' ')
            ++blancos; /*Si es un espacio en blanco aumentar el contador*/
        else if (blancos >= N){
            tabs = blancos / N;
            esp_blancos = blancos % N; /*Sacar cuentas de cuantos tab hay que poner y cuandos espacios blancos hay que dejar*/
            for (i = 0; i < tabs; ++i)
                espacio[(indice - blancos + i)] = 't';
            indice = indice - blancos + tabs + esp_blancos; /*Recalcular nuevo indice donde continuar*/
            espacio[indice] = caracter; /*Volver a colocar la letra que faltaba*/
            blancos = 0; /*Reiniciar contador de blancos*/
        }
        else
            blancos = 0;
    }

    if (caracter == '\n'){
        espacio[indice] = caracter;
        ++indice;
    }
    espacio[indice] = '\0';
}

void main() {
    char palabra[MAX];

    getline(palabra, MAX);

    printf("%s", palabra);
}
/*Texto de prueba: "              hola    hola " 14 espacios, luego el hola, 4 espacios, hola, y un espacio*/
/*2. "   hola    hola    hola        hola"*/
/*3. "             hola"*/