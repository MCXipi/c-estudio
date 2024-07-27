#include <stdio.h>
#include <string.h>

int reverse(char s[]) {
    static int pos;
    int temp;
    int last = (strlen(s) - 1);

    if (pos <= last - pos) {
        temp = s[pos];
        s[pos] = s[last - pos];
        s[last - pos] = temp;
        ++pos;
        reverse(s);
    }
    return 0;
}

void main() {
    char test[] = "abcdefg";

    printf("String original:  %s.\n", test);
    reverse(test);
    printf("String revertido: %s.\n\n", test);
}