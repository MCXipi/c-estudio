#include <stdio.h>
#define MAXLINE 1000 /*Longitud maxima de la palabra*/

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/*Leer la linea y regresar longitud*/
int getline(char stg[], int lim){
    int c, i; /*Para cada caracter y el indice*/

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        stg[i] = c; /*Asigna al arreglo cada caracter de la palabra*/
    
    if (c == '\n'){ /*Agrega '\n' al final del arreglo como normalmente habría pasado (?) -> Permite el salir del getchar cuando se termina la palabra de manera natural, sin concatenar palabaras ni necesitar EOF para salir del ciclo.*/
        stg[i] = c;
        ++i; /*Aumenta en uno el indice para agregar el fin del arreglo*/
    }
    stg[i] = '\0'; /*Agrega el fin de linea al arreglo de caracteres*/
    return i; /*Devolver el valor de la longitud absoluta de la palabra*/
}

/*Poner todos los caracteres de un arreglo a otro arreglo*/
void copy(char to[], char from[]){
    int i;
    
    for (i = 0; (to[i] = from[i]) != '\0'; ++i)
        ;
}

/*Haciendo la comparacion de la sandia imprime la linea que es más larga*/
int main(){
    int len, max; /*Longitud de la linea y longitud maxima vista*/
    char line[MAXLINE], longest[MAXLINE]; /*Se inicializan los arreglos de caracteres*/

    max = 0;
    while((len = getline(line, MAXLINE)) > 0){ /*Si existe una linea*/
        if (len > max){
            max = len;
            copy(longest, line); /*Hacer del largo maximo el largo obtenido y la palabra mas larga como la nueva.*/
        }
    }
    
    if (max > 0 ) /*Si hubo alguna linea ganadora*/
        printf("%s", longest);
    return 0;
}