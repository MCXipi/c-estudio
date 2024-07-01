#include <stdio.h>

/*Reemplazar los espacios en blancos por la minima cantidad de t y rellenar con blancos*/

#define MAX 1000
#define TRUE 1
#define FALSE 0

void getline(char[], int);
void revision(char[]);

void getline(char espacio[], int limite) {
    int indice, caracter;
    
    for (indice = 0; indice < limite - 1 && (caracter = getchar()) != EOF && caracter != '\n'; ++indice)
        espacio[indice] = caracter;

    if (caracter == '\n'){
        espacio[indice] = caracter; /*Como es una revisión primero escribiré toda la linea y luego la revisaré*/
        ++indice;
    }
    espacio[indice] = '\0';
}

void revision(char linea[]) {
    int c_apertura, c_cierre, ll_apertura, ll_cierre, ult_caracter, i, pass;
    
    c_apertura = c_cierre = ll_apertura = ll_cierre = 0;

    for (i = 0; linea[i] != '\0'; ++i) {
        if (linea[i] != '{' && linea[i] != '}' && linea[i] != '[' && linea[i] != ']' && linea[i] != ' ' && linea[i] != ';' && linea[i] != '(' && linea[i] != ')' && linea[i] != '\n'){
            ult_caracter = i;
        }
        else if (linea[i] == '{')
            ++ll_apertura;
        else if (linea[i] == '}')
            ++ll_cierre;
        else if (linea[i] == '[')
            ++c_apertura;
        else if (linea[i] == ']') /*Cualquier otra revisión iría incluida aqui y en el if posterior*/
            ++c_cierre;
    }

    pass = FALSE;
    for (i = 0; linea[ult_caracter + i] != '\0'; ++i)
        if (linea[ult_caracter + i] == ';')
            pass = TRUE;
    if (pass == FALSE)
        printf("Falta ';'.\n");    
    else
        printf("No hace falta ';' :)\n");
    if (ll_apertura != ll_cierre)
        printf("Hace falta una llave.\n");
    else
        printf("No hace falta ninguna llave :)\n");
    if (c_apertura != c_cierre)
        printf("Hace falta un corchete.\n");
    else
        printf("No hace falta ningun corchete :)\n");

}

void main() {
    char palabra[MAX];

    getline(palabra, MAX);

    revision(palabra);
}