#include <stdio.h>
#include <ctype.h>

// squeeze2: Borrar de s1 todos los caracteres que hayan en s2.

void squeeze2(char[], char[]);

void squeeze2(char s1[], char s2[]) {
    int i, j, k;

    for (i = 0; s2[i] != '\0'; ++i){
        for(j = k = 0; s1[j] != '\0'; ++j){
            if (tolower(s1[j]) != tolower(s2[i]))
                s1[k++] = s1[j];
        }
        s1[k] = '\0';
    }
}

void main() {
    char test1[] = "testtesttest";
    char test2[] = "es";
    squeeze2(test1, test2);
    printf("%s", test1);
}
