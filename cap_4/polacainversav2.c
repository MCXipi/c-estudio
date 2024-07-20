#include <stdio.h>
#include <math.h>
#include <ctype.h>

// Ejemplo de la seccion 4.4 con la inclusion de los ejercicios 4-3 y 4-4, y siguientes. Asi no pierdo el objetivo de polacainversa.c de entender el ejemplo.

#define MAXOP 100
#define BUFSIZE 100
#define MAXVAL 100
enum operations {NUMBER = '0', COS = '1', SIN = '2', EXP, POW, DUPLICATE, CALL, EXCHANGE};

char buf[BUFSIZE];
int bufp = 0;

void writebuf() {
    int i, c;

    printf("Ingresa operacion:\n");
    for (i = 0; i < BUFSIZE - 1 && (c = getchar()) != EOF && c != '\n'; ++i) // Ahora ungetch escribe en el bufer la operacion completa
        buf[i] = c;
    if (c == '\n') {
        buf[i++] = '\n';
    }
    buf[i] = '\0';
    bufp = 0;
}

int getch(void) {
    printf("getchar\n");
    if (buf[bufp] != '\0') // No estoy leyendo bien los caracteres.
        return buf[bufp++];
    writebuf();
    return ' ';  
}

int getop(char s[]) { // Ahora getop debe procesar la operacion ingresada para mandar la señal a main
    int i, c, streq(char[], char[]);

    while ((c = getch()) == '\t' || c == ' ') // Le quito espacios en blanco que preceden la operacion
        ;
    printf("%s\n", s);
    
    i = 0;
    if (isalpha(c)) {
        s[i++] = tolower(c);
        while (isalpha((c = getch())) && i < MAXOP) // Obtiene la operacion que corresponde a un comando o trigonometria.
            s[i++] = tolower(c);

        if (i < MAXOP - 1)
            s[i] = '\0';
        else {
            printf("error: limite de operacion alcanzado.\n");
            return 0;
        }

        if (streq(s, "cos"))
            return COS;
        else if (streq(s, "sin") || streq(s, "sen"))
            return SIN;
        else if (streq(s, "exchange"))
            return EXCHANGE;
        else if (streq(s, "call"))
            return CALL;
        else if (streq(s, "exp"))
            return EXP;
        else if (streq(s, "pow"))
            return POW;
        else if (streq(s, "duplicate"))
            return DUPLICATE;
        else 
            return 0;
    }

    else if (isdigit(c) || c == '-') {
        s[i] = c;
        while (i < MAXOP && (isdigit(c = getch())) || c == '-')
            s[i++] = c;
        if (c == '.') {
            s[i++] = c;
            while (i < MAXOP && (isdigit(c = getch())))
                s[i++] = c;
        }
        if (i < MAXOP)
            return NUMBER;
        else {
            printf("error: limite de operacion alcanzado\n");
            return 0;
        }
    }

    else if (!isalnum(c))
        return c;
    
    return 0;
}

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: pila llena, no puede efectar push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp]; // Porque push deja el indice sp en un espacio en blanco
    else {
        printf("error: pila vacia\n");
        return 0.0;
    }
}

double call(void){ // Imprime elemento tope de la pila y lo retorna.
    if (sp > 0) {
        printf("%g\n", val[sp - 1]);
        return val[sp - 1];
    }
    else
        printf("error: pila vacia\n");
    return 0.0;
}

void duplicate(void) { // Duplica el elemento tope de la pila
    if (sp < MAXVAL && sp > 0) {
        val[sp] = val[sp - 1];
        printf("tope duplicado.\n");
    }
    else if (sp >= MAXVAL)
        printf("error: pila llena, no se puede duplicar tope %g\n", call());
    else if (sp <= 0)
        printf("error: pila vacia\n");
}

void exchange(void) { // Intercambia los dos ultimos elementos de la pila
    double temp;

    if (sp > 1) {
        temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
        printf("elementos intercambiados.\n");
    }
    else
        printf("error: pila vacia, no hay datos para intercambiar.\n");
}

void clean(void) { // Limpia la pila, considerando que si sp = 0 no hay elementos.
    sp = 0;
}

int main(void) {
    int type;
    double op2, op1;
    char s[MAXOP]; // s funciona como la entrada de un operador u operando, uno a uno, que se escribe con getop.

    while ((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case POW:
                op2 = pop();
                op1 = pop();
                if (op2 > 0 && op1 > 0)
                    push(pow(op1, op2));
                else
                    printf("error: dominio\n");
                break;
            case EXP:
                push(exp(pop()));
                break;
            case SIN:
                push(sin(pop()));
                break;
            case COS:
                push(cos(pop()));
                break;
            case DUPLICATE:
                duplicate();
            case CALL:
                call();
            case EXCHANGE:
                exchange();
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: divisor 0\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push((int) pop() % (int) op2);
                else
                    printf("error: divisor 0\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop()); // Mostrar ultimo resultado cuando haya acabado el ingreso.
                break;
            default:
                printf("error: comando desconocido %s \n", s);
                break;
        }
    }
    return 0;
}