#include <stdio.h>
#include <math.h>
#include <ctype.h>

// Copia en un mismo archivo del ejemplo de la seccion 4.4 en otro orden para mejor entendimiento.
#define MAXOP 100
#define NUMBER '0'
#define BUFSIZE 100
#define MAXVAL 100

char buf[BUFSIZE];
int bufp = 0;

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: demasiados caracteres\n");
    else
        buf[bufp++] = c; // Si no se utilizara esta funcion, un caracter despues del final de un numero si o si se perdería al solicitar un nuevo c 
}

int getch(void) {
    return (bufp > 0 ) ? buf[--bufp] : getchar();
}

int getop(char s[]) {
    int i, c;
    // static int saved; Para el ejercicio 4-11, si desearamos dejar de utilizar ungetch y suponemos que solo se guardará un caracter, podemos usar una variable estatica.

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; // Osea si es un operador, EOF, o \n.
    
    i = 0; // Como la funcion no termino antes, ahora comienza el trabajo con operandos.
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
        ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch())) // Escribe el numero en s[], y la separacion por el punto es para si o si escribir numeros. Si no, escribiria cualquier caracter
        ; 

    s[i] = '\0';
    if (c != EOF)
        // saved = c; de esta manera se almacena y no se pierde, al ser variable estatica.
        ungetch(c); // Guarda el caracter que viene. Getchar lo obtendrá denuevo, y si es operando va a seguir llamando los demas numeros de la entrada, y si es operador, lo retorna.
    return NUMBER;
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

int main() {
    int type;
    double op2;
    char s[MAXOP]; // s funciona como la entrada de un operador u operando, uno a uno, que se escribe con getop.

    while ((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
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
                printf("error: comando desconocido %s\n", s);
                break;
        }
    }
    return 0;
}