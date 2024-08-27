#include "defs.h"
#include "buf.c"
#include "entry.c"
#include <math.h>

// Ejercicio 7-5

void calc (char *entry) {
    // Funcion calculadora postfija.
    // Obtiene operaciones una a una o en una sola linea
    // Identifica el tipo de la operacion y dependiendo de esa realiza calculos o guarda el numero.

    char op[MAXLEN];
    double t, t2;

    while(getop(op, entry) != EOF) {
        if (typeop(op) == NUM) {
            push(atof(op));
            clear_screen();
        }
        else if (typeop(op) == OP)
            switch(*op) {
                case '+':
                    push(pop() + pop());
                    clear_screen();
                    break;
                case '-':
                    t = pop();
                    push(pop() - t);
                    clear_screen();
                    break;
                case '*':
                    push(pop() * pop());
                    clear_screen();
                    break;
                case '/':
                    t = pop();
                    push(pop() / t);
                    clear_screen();
                    break;
                case '%':
                    t = pop();
                    push((int) pop() % (int) t);
                    clear_screen();
                    break;
                case '=':
                    system("cls");
                    printf("\t%g\n", pop());
                    break;
            }
        else if (typeop(op) == STR) {
            if (strcmp(op, "cos") == 0) {
                push(cos(pop()));
                clear_screen();
            }
            else if (strcmp(op, "sin") == 0|| strcmp(op, "sen") == 0) {
                push(sin(pop()));
                clear_screen();
            }
            else if (strcmp(op, "e") == 0) {
                push(exp(pop()));
                clear_screen();
            }
            else if (strcmp(op, "pow") == 0) {
                t2 = pop();
                t = pop();
                if (t > 0 && t2 > 0) {
                    push(pow(t, t2));
                    clear_screen();
                }
                else
                    printf("pow Error.\n");
            }
            else if (strcmp(op, "sqrt") == 0) {
                t = pop();
                if (t >= 0) {
                    push(sqrt(t));
                    clear_screen();
                }
                else
                    printf("sqrt Error.\n");
            }
            else
                printf("\t%d\n", 0);
        }
        else {
            clear_screen();
            printf("Invalid entry %s.\n", op);
        }
    }
}