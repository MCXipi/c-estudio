#include <stdio.h>
#include <math.h>
#include <ctype.h>

// Copia en un mismo archivo del ejemplo de la seccion 4.4 en otro orden para mejor entendimiento, agregando hasta el ejercicio 4-4.

#define MAXOP 100
#define BUFSIZE 100
#define MAXVAL 100
#define MAXVAR 27
enum operations {NUMBER = '0', COS = '1', SIN = '2', EXP, POW, CALL, EXCHANGE, CLEAN, DUPLICATE, VARWORK};

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

char var;
double vars[MAXVAR]; // Almacenamiento de variables.
char var_buf[MAXVAR]; // Buffer que almacenará las variables utilizadas desde la 'a' hasta la 'z'
int var_buf_last; // Posicion de la ultima variable almacenada

void save_var() { // Funcion para guardar el pop() en la variable.
    int i;

    if(check_var()) // Si ya existe, imprimela
        printf("\t%c = %.8g\n", var, vars[var - 'a']);
        
    if (sp > 0) { // Si hay al menos un numero en el historial, guardalo
        vars[var - 'a'] = pop();
        for (i = 0; i <= var_buf_last && var_buf[i] != var; ++i)
            ;
        if (i > var_buf_last) {
            var_buf[++var_buf_last] = var;
        }
    }
}

int check_var() {
    int i;
    for (i = 0; i <= var_buf_last && var_buf[i] != var; ++i)
        ;
    return (i > var_buf_last) ? 0 : 1;
}

int buf;
int buf_used = 0; // Tambien es posible asignarle el valor buf = EOF para controlar si está vacio o no.

void ungetch(int c) {
    buf = c;
}

int getch(void) {
    if (buf_used){
        buf_used = 0;
        return buf;
    }
    else
        return getchar();
}

int getop(char s[]) {
    int i, c;

    while ((s[0] = c = tolower(getch())) == ' ' || c == '\t')
        ;

    // Para evitar el uso de getch y ungetch se necesitaria el siguiente codigo:
    //    while ((s[0] = c = tolower(getchar())) == ' ' || c == '\t')
    //      ;
    
    if (c == '\n')
        return c;

    // for (i = 1; c != EOF && !isspace(c = tolower(getchar())); ++i)
    //    s[i] = c;

    // Donde todo lo demás sería igual.

    for (i = 1; c != EOF && !isspace(c = tolower(getch())); ++i)
        s[i] = c; // Escribir la operacion entera, que está separada por espacios a ambos lados.
    s[i] = '\0'; 
    
    if (c != EOF)
        ungetch(c);
    else
        return c;

    if (s[1] == '\0') {
        if (isalpha(s[0])) {
            var = tolower(s[0]);
            return VARWORK;
        }
        else
            return (isdigit(s[0]) ? NUMBER : s[0]); // En el caso de que la operacion sea de un solo caracter. Si funciona o no, depende de main.
    }
    if (s[0] == '-' || s[0] == '+' || isdigit(s[0])) { // Si no era un comando era un numero, y si este numero empieza con algo distinto a -, + o un digito, entonces está mal escrito.
        for (i = 0; s[i] != '\0'; ++i)
            if (s[i] != '.' && s[i] != '-' && !isdigit(s[i])) // Si lo demás del numero está bien escrito
                return 0;
        return NUMBER;
    }
    
    // Si paso todas las pruebas y no se retornó nada, se supone un comando.
    if (streq(s, "cos"))
        return COS;
    else if (streq(s, "sin") || streq(s, "sen"))
        return SIN;
    else if (streq(s, "exp"))
        return EXP;
    else if (streq(s, "pow"))
        return POW;
    else if (streq(s, "call"))
        return CALL;
    else if (streq(s, "exchange"))
        return EXCHANGE;
    else if (streq(s, "clean"))
        return CLEAN;
    else if (streq(s, "duplicate"))
        return DUPLICATE;
    else
        return 0;
    
}

double call(){ // LLama al elemento tope de la pila
    if (sp > 0) {
        printf("tope: %g\n", val[sp - 1]);
        return val[sp - 1];
    }
    else {
        printf("error: pila vacia\n");
        return 0.0;
    }
}

void duplicate() { // Duplica el elemento tope de la pila. Si hay suficientes elementos, de eso se encarga el pop.
    double temp = pop();
    push(temp);
    push(temp);
}

void exchange() { // Intercambia los dos ultimos elementos de la pila
    double temp1, temp2;
    temp2 = pop();
    temp1 = pop();
    push(temp2);
    push(temp1);
}

void clean() { // Limpia la pila, considerando que si sp = 0 no hay elementos.
    if (sp == 0)
        printf("error: pila ya vacia");
    else
        sp = 0;
}

int streq(char s[], char base[]) {
    size_t i, len_base;

    len_base = strlen(base);

    if (strlen(s) == len_base)
        for (i = 0; s[i] == base[i] && s[i] != '\0'; ++i)
            ;
    else
        return 0;
            
    if (i == len_base)
        return 1;
    else
        return 0;
}

void ungets(char s[]) {
    int i;

    for (i = 0; s[i] != '\0'; ++i) // La funcion ungets solamente debe hacer ungetch a la cadena s completa. No necesita saber nada de buf
        ungetch(s[i]); 
}

int main() {
    int type;
    double op1, op2, last;
    char s[MAXOP]; // s funciona como la entrada de un operador u operando, uno a uno, que se escribe con getop.

    while ((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case COS:
                push(cos(pop()));
                break;
            case SIN:
                push(sin(pop()));
                break;
            case EXP:
                push(exp(pop()));
                break;
            case POW:
                op2 = pop();
                op1 = pop();
                if (op1 > 0 && op2 > 0)
                    push(pow(op1, (int) op2));
                else
                    printf("error: dominio\n");
                break;
            case CALL:
                call();
                break;
            case EXCHANGE:
                exchange();
                break;
            case CLEAN:
                clean();
                break;
            case DUPLICATE:
                duplicate();
                break;
            case VARWORK:
                save_var();
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
                if (sp > 0) {
                    last = pop();
                    printf("\t%.8g\n", last); // Mostrar ultimo resultado cuando haya acabado el ingreso.
                }
                break;
            default:
                printf("error: comando desconocido %s\n", s);
                break;
        }
    }
    return 0;
}