#include <stdio.h>

// Escriba una función escape(s,t) que convierte caracteres como
// nueva línea y tabulación en secuencias de escape visibles como \n y \ t mientras
// copia la cadena t a s. Utilice un switch. Escriba también una función para la dirección
// inversa, convirtiendo secuencias de escape en caracteres reales.

// Debo copiar t a s y cada vez que haya un '\n', poner un '\\' y luego un 'n, y si es un '\t', un '\\' y un 't'.

#define MAX 100

void escape(char s[], char t[], int lim){ 
    int i, j; // Uno que revisa t y otro que escribe en s.

    for (i = j = 0; j < lim - 1 && t[i] != '\0'; ++i) 
        switch(t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
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

    escape(modificada, palabra, MAX);
    
    printf("Original: %sModificada: %s \n", palabra, modificada);
}
// Palabra de prueba: "palabra tab  tab   palabra"