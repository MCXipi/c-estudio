#include <stdio.h>
#include <ctype.h>

#define MAXCOL 10

int main () {
    int c, last, col;
    char temp[MAXCOL];

    col = 1;

    while((c = getchar()) != EOF) {
        if (isprint(c) && col <= MAXCOL) {
            printf("%c", c);
            ++col;
        }
        else if (iscntrl(c) && col <= MAXCOL) {
            sprintf(temp, "\\0x%X", c);
            printf("%s", temp);
            col += strlen(temp);
        }
        else if (isgraph(c)) {
            col = 1;
            isgraph(last) ? printf("-\n-%c", c) : printf("\n%c", c);
        }
        else if (iscntrl(c)) {
            sprintf(temp, "\n0x%X", c);
            printf("%s", temp);
            col += strlen(temp);
        }
        last = c;
    }
}