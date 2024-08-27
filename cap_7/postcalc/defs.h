#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLEN 100

#ifndef TIPO_OP
    #define TIPO_OP
    enum tipo {INV = -1, NUM, OP, STR};
#endif