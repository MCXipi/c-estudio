#include <stdio.h>
#include <ctype.h>

#define MAX 150

// Convertir un string numerico con punto flotante a un numero double.

double atof(char s[]) {
    int i, signo, ctf_sign, ctf;
    double num, exp;

    i = 0;
    num = 0.0;

    while (isspace(s[i])) // Elimina posibles espacios en blanco al principio de la cadena 
        ++i; 

    signo = 1;
    if (s[i] == '-') {
        signo = -1;
        ++i; // Define signo del numero y trabaja con el indice si hay caracter de signo
    }
    else if (s[i] == '+')
        ++i;
    
    for (i; isdigit(s[i]); ++i)
        num = 10 * num + (s[i] - '0'); // Trabajar digitos antes del punto hasta que salga el punto
    
    exp = 1.0;
    if (s[i] == '.' || s[i] == ',') {
        for (i++; isdigit(s[i]); ++i) {
            num = 10 * num + (s[i] - '0');
            exp *= 1.0/10.0; // Trabaja numeros despues del punto
        }  
    } 

    if (tolower(s[i]) == 'e') { // Trabaja con la notacion cientifica
        ++i;
        if (s[i] == '-')
            ctf_sign = -1;
        else
            ctf_sign = 1;  // Trabajo con el signo de la notacion

        if (s[i] == '+' || s[i] == '-')
            ++i; // Trabajo con indice en caso de caracter de signo

        ctf = 0;
        for (i; isdigit(s[i]); ++i)
            ctf = 10 * ctf + (s[i] - '0'); // Obtencion de exponente como entero
        
        for (i = 0; i < ctf; ++i)
            (ctf_sign == -1) ? (exp *= 1.0/10.0) : (exp *= 10.0); // Conversion de notacion cientifica a double aplicandolo al exp obtenido antes
    }

    return signo * num * exp; // Se le pone el signo y se multiplica para dejar el punto donde corresponde
}

void main() {
    char numero[] = "-6.2e5"; // 0.00012345
    double convertido = atof(numero);

    printf("El numero original es %s, y el convertido es %0.12lf\n", numero, convertido);
}

