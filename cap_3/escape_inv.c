#include <stdio.h>

// Escriba una función escape(s,t) que convierte caracteres como
// nueva línea y tabulación en secuencias de escape visibles como \n y \ t mientras
// copia la cadena t a s. Utilice un switch. Escriba también una función para la dirección
// inversa, convirtiendo secuencias de escape en caracteres reales.

// Con un concepto similar al original, debo ir copiando uno a uno los caracteres. Si el caracter es \ y el siguiente es t, o n, entonces pongo su respectiva sec. de
// escape

#define MAX 100

void escape_inv(char s[], char t[], int lim){ 
    int i, j; // i revisa, j escribe.
    
    for (i = j = 0; j < lim - 1 && t[i] != '\0'; ++i) // Un switch anidado necesita estar dentro de llaves?
        switch(t[i]) {
            case '\\':
                if (t[i + 1] == 'n')
                    s[j++] = '\n';
                else if (t[i + 1] == 't')
                    s[j++] = '\t';
                ++i; // Se ajusta el indice para que el proximo sea una letra nada que ver con \n y \t
                break;
            default:
                s[j++] = t[i];
                break;
        }
    
    s[j++] = '\n';
    s[j] = '\0';
}

void getline(char t[], int lim){
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        t[i] = c;
    if (c == '\n')
        t[i++] = '\n';
    t[i] = '\0';
}

void main() {
    char palabra[MAX];
    char modificada[MAX];

    getline(palabra, MAX);

    escape_inv(modificada, palabra, MAX);
    
    printf("Original: %sModificada: %s \n", palabra, modificada);
}
// Palabra de prueba: "palabra tab\ttab\tpalabra\n"