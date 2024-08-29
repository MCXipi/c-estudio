#include <stdio.h>
#include <ctype.h>

// Programa expr que calcula una expresion igual que la calculadora polaca inversa, recibiendo la entrada desde main.

// Requiero una pila de memoria para trabajar con los calculos.

#define PILA 500

static double pila[PILA]; // Defino la pila de memoria con 500 elementos
static int pl_i;

void push(double el) { // Funcion para guardar en la pila
    if (pl_i < PILA - 1) // Si hay espacio en la pila
        pila[pl_i++] = el;
    else
        (printf("Error: Demasiados numeros.\n"));
}

double pop() { // Funcion para obtener el ultimo elemento de la pila
    if (pl_i > 0) 
        return pila[--pl_i];
    else
        printf("Error: Pila vacia.\n");
}

double getnum(char *s) {
    double num = 0, exp = 1.0, sign = 1.0;
    
    if (*s == '-')
        sign = -1.0; // Establecer el signo del numero a retornar
    
    if (*s == '-' || *s == '+')
        ++s; // Pasar al primer digito
    
    for (; isdigit(*s); ++s)
        num = 10 * num + (*s - '0'); // Pasar la cadena a double, de la parte entera
    if (*s == '.' || *s == ',')
        for (++s; isdigit(*s); ++s) {
            num = 10 * num + (*s - '0');
            exp *= 0.1; // Pasar la cadena a double de la parte decimal, calculando también el exponente que le corresponde
        }
    
    return num * exp * sign; // Retornar el numero con su decimal correspondiente, y el signo correspondiente
}

int main (int argc, char **argv) {
    double temp;
    int i;

    if (argc == 1) {
        printf("expr [num] [operation]\n");
        return NULL;
    }

    printf("\n\n");
    while (--argc > 0) {
        if (isdigit(*(*++argv)) || (*(*argv) == '-' || *(*argv) == '+') && isdigit(*((*argv) + 1))) // Si el argumento en cuestion es un digito ya sea precedido por un negativo o no
            push(getnum(*argv)); // Guardar en la pila el numero en cuestion
        else
            switch (**argv) { // Revisar la operacion y realizarla, guardando en la pila inmediatamente el resultado
                case '+':
                    push(pop() + pop());
                    break;
                case '-':
                    temp = pop();
                    push(pop() - temp);
                    break;
                case '/':
                    temp = pop();
                    if (temp != 0)
                        push(pop() / temp);
                    else
                        printf("Error: Division por 0.\n");
                    break;
                case '%':
                    temp = pop();
                    if (temp != 0)
                        push((int)pop() % (int)temp);
                    else
                        printf("Error: Division por 0.\n");
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case 'p':
                printf("Pila: ");
                    for(i = 0; i < pl_i; i++)
                        printf((i < pl_i - 1) ? "%0.8g, " : "%0.8g\n", *(pila + i));
                    break;
                default:
                    printf("Error: Operacion invalida.\n");
                    return NULL;
            }        
    }
    printf("\n\t= %0.8g\n\n\n", pop()); // Imprimir el resultado final
}