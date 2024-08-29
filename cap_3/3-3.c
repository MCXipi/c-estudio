#include <stdio.h>

// Una vez que se detecte un guion, se debe ver ambos "lados" para saber de donde hasta donde rellenar, usando un for. 
// Hay que tener cuidado con no escribir dos veces la letra del inicio y del final
// Si hay un guion al inicio o al final de la abreviatura, no hay que considerarlo como otra abreviatura.

#define LARGO 500

void expand(char s1[], char s2[]) {
    int i, j, k; // Minimo dos indices: Uno para leer y otro para escribir. K servirá para el segundo for.

    for (i = 0, j = 0; s1[i] != '\0'; ++i, ++j){
        if (s1[i] == '-' && s1[i - 1] != ' ' && s1[i + 1] != ' ') { // Si el caracter a copiar es un guion que no está solo por uno de los dos lados
            for (k = s1[i - 1] + 1; k < s1[i + 1]; ++k)
                s2[j++] = (char) k; // Escribir en s2 cada caracter entre los que están en ambos lados del guion, haciendo la conversion explicita a char del int k equivalente, evitando re escribir la primera
            --j; // Al final del for también le suma uno a j, lo que es innecesario por el for externo.
        }
        else
            s2[j] = s1[i];
    }
    s2[j] = '\0';
}

void getline(char t[]){
    int i, c;

    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        t[i] = c;
    if (c == '\n')
        t[i++] = '\n';
    t[i] = '\0';
}

void main() {
    char original[LARGO];
    char cambiado[LARGO];

    getline(original);

    expand(original, cambiado);
    printf("\nEl string original es: %s\nEl string expandido es: %s\n", original, cambiado);
}

// Texto de prueba: "Las letras de la a-z deberia cambiarlas por el alfabeto entero, aunque sea A-Z. Un a-b o x-y no deberia cambiar, y un 0-9 o un 3-5 tambien deberia funcionar. Guiones vacios en algun lado, como -a-z o a-z- o - no afectan y son ignorados."