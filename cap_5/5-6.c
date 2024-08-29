#include <stdio.h>
#include <string.h>

#define MAX 100
// Reversiones de ejercicios de capitulos anteriores, utilizando apuntadores.

int saveline(char *s, int lim) {
    int i, c;

    for (i = 0; i < --lim && (c = getchar()) != EOF && c != '\n'; ++i, ++s)
        *s = c;

    if (c == '\n')
        *s++ = c;
    *s = '\0';

    return i;
}

double atof(const char *s) {
    int i, signo, ctf_sign, ctf;
    double num, exp;

    num = 0.0;

    while (isspace(*s)) // Elimina posibles espacios en blanco al principio de la cadena 
        ++s;
    
    signo = 1;
    
    if (*s == '-') {
        signo = -1;
        ++s; // Define signo del numero y trabaja con el indice si hay caracter de signo
    }
    else if (*s == '+')
        ++s;
    
    for (; isdigit(*s); ++s)
        num = 10.0 * num + (*s - '0'); // Trabajar digitos antes del punto hasta que salga el punto
    
    exp = 1.0;
    if (*s == '.' || *s == ',')
        for (++s; isdigit(*s); ++s) {
            num = 10.0 * num + (*s - '0');
            exp *= 1.0/10.0; // Trabaja numeros despues del punto
        }  
    
    if (tolower(*s) == 'e') { // Trabaja con la notacion cientifica
        ++s;
        if (*s == '-')
            ctf_sign = -1;
        else
            ctf_sign = 1;  // Trabajo con el signo de la notacion

        if (*s == '+' || *s == '-')
            ++s; // Trabajo con indice en caso de caracter de signo

        ctf = 0;
        for (; isdigit(*s); ++s)
            ctf = 10 * ctf + (*s - '0'); // Obtencion de exponente como entero
        
        for (i = 0; i < ctf; ++i)
            (ctf_sign == -1) ? (exp *= 1.0/10.0) : (exp *= 10.0); // Conversion de notacion cientifica a double aplicandolo al exp obtenido antes
    }

    return signo * num * exp; // Se le pone el signo y se multiplica para dejar el punto donde corresponde
}

int reverse(char *s) {
    static int pos; // Static pues así comienza en 0, se mantiene tras llamados, y no se inicializa por cada uno de estos.
    int temp;
    int last = (strlen(s) - 1); // Indice del ultimo caracter

    if (pos <= last - pos) { // Si la posicion estudiada desde la izquierda es menor o igual a la estudiada desde el final de la cadena
        temp = *(s + pos);
        *(s + pos) = *(s + last - pos);
        *(s + last - pos) = temp;
        ++pos;
        reverse(s);
    }
    return 0;
}

int strindex(char *s, char *t) {
    int largo_s, largo_t, i, j, k;

    printf("Ingresa linea a estudiar:\n");
    largo_s = saveline(s, MAX);
    printf("Ingresa patron a buscar:\n");
    largo_t = saveline(t, MAX);

    for (i = largo_s; i >= 0; --i) {
        for (j = i, k = largo_t; k >= 0 && *(t + k) == *(s + j); --j, --k)
           ;
        if (k < 0)
            return j + 1;
    }
    return -1; 
}

void main() {
    char text[MAX];
    const char *numero = "-6.2e-5"; 
    char test[] = "abcdefg";
    char linea[MAX];
    char patron[MAX];
    int resultado;
    
    //saveline(text, MAX);
    //printf("La entrada fue %s\n", text);

    //double convertido = atof(numero);
    //printf("El numero original es %s, y el convertido es %0.12lf\n", numero, convertido);

    //printf("String original:  %s.\n", test);
    //reverse(test);
    //printf("String revertido: %s.\n\n", test);

    //resultado = strindex(linea, patron);
    //printf("El patron %s se encuentra en la posicion %d\n", patron, resultado);
}