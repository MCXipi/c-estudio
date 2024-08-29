#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// Cometí un error. El ejercicio requiere que la cadena de input sea ya un hexadecimal y yo lo convierta a un entero mediante conversion completa.
// Debo considerar una funcion para recibir la cadena, otro para convertirla y en main trabajar con estos datos para mostrarlos.

#define MAX 25

void getline(char[], int);
int transform(char[]);

void getline(char spce[], int l) {
    int i, c;

    for (i = 0; i < l - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        spce[i] = c;
    spce[i] = '\0';
}

int transform(char line[]) {
    int num, i, largo, jump, exponente; // Por enunciado se considerará que el numero es un int de 32 bits por lo que el numero hexadecimal será de largo 8 digitos maximo.
    num = 0;
    char hex;

    // La cadena puede partir por 0x o 0X o directamente en el codigo hexadecimal. Si hex es 'X', i partira como el indice 2, si no, partira como el 0.
    hex = toupper(line[1]);
    if (hex == 'X')
        jump = 2;
    else
        jump = 0;

    largo = strlen(line) - jump; // El largo del hexadecimal define los exponentes a utilizar.
    for (i = 0 + jump; isxdigit(line[i]) && (i - jump) < (largo + 2) && line[i] != '\0'; ++i){
        //Trabajaré normalmente con los digitos. Para los digitos A-F aprovecharé los codigos ASCII.
        exponente = largo - (i - jump) - 1; // El exponente estudiado es el largo del numero menos el indice actual menos el salto que se tuvo que hacer al principio, menos uno.

        if ('0' <= line[i] && line[i] <= '9' && exponente != 0) // Si el caracter es un exponente del 0 al 9 y no se está trabajando el primer exponente (0)
            num = num + (line[i] - '0') * pow(16, exponente);
        else if ('0' <= line[i] && line[i] <= '9' && exponente == 0) // line[i] debe ser mayor a 0 y aparte menor a 9. No existen la relacion '0' < line[i] < '9' como en python.
            num = num + (line[i] - '0');

        else if (exponente != 0) // Si no es un exponente del 0 al 9 y no se está trabajando el primer exponente
            num = num + (toupper(line[i]) - '7') * pow(16, exponente); // restar '7' es lo mismo que restar 55.
        else
            num = num + (toupper(line[i]) - '7');
    }

    if ((!isxdigit(line[i]) && line[i] != '\0') || (i - jump) == (largo + 2)){
        num = -1;
        printf("Invalid hex number.\n"); 
    }

    return num;    
}

void main() {
    char codigo[MAX];
    int num_equiv;

    printf("Ingresa tu codigo hexadecimal:\n");
    getline(codigo, MAX);
    num_equiv = transform(codigo);
    printf("El numero equivalente a %s es %d \n", codigo, num_equiv);
}

//Input de prueba: "0x17A0", "0X17a0", "17A0".