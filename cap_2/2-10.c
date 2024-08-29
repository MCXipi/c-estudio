#include <stdio.h>

int lower(int);

lower(c) {
    return 65 <= c && c <= 90 ? c + 32 : c; // Si c es un codigo ASCII perteneciente a las mayusculas, entonces sumale 32 para el codigo de su minuscula equivalente. Si no, retorna la misma.
}

main() {
    int c;
    printf("\n");
    for (c = 'A'; c <= 'Z'; ++c)
        printf("La antigua letra es %c. La nueva es %c\n", c, lower(c));
}