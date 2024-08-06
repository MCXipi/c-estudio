#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Ejemplo de la seccion 5.11 para usar de base para los ejercicios.

#define MAXLINES 5000
#define MAXSPACE 100000
#define MAXLEN 1000

char *lineptr[MAXLINES]; // Array de apuntadores a todas las lineas.

void writelines (char **lineptr, int nlines) { // Recibe un numero de lineas y un arreglo de punteros
    printf("\n\n");
    do 
        printf("%s", *lineptr++); 
    while (--nlines > 0); // Imprimir la linea siempre que queden lineas.
}

int getline(char *s, int lim) { // Copiado de funciones utiles
    int i, c;

    for (i = 0; i < lim - 2 && (c = getchar()) != EOF && c != '\n'; ++i, ++s)
        *s = c;
    if (i == lim - 2) {
        printf("Error: Linea muy larga\n");
        return 0;
    }
    if (c == '\n') {
        *s = c;
        ++i;
    }
    *++s = '\0';
    ++i;

    if (c == EOF)
        return c;
    else
        return i; // El largo considera TODOS los caracteres, al usarse para solicitar espacio en alloc
}

char buff[MAXSPACE];
char *buffp = buff; // buffp inicialmente apuntaba a 0. Debe comenzar como la misma direccion inicial en buff

char *alloc (int sp) {
    if (sp < MAXSPACE - (buffp - buff)) { // Si hay espacio disponible
        buffp += sp; // Correccion   
        return (buffp - sp); // Establecer la nueva direccion como la posicion del buffer ---> Incorrecto, retorno un puntero que deja un espacio entre linea y linea.
    }
    else {
        printf("alloc: not enough space.\n");
        return NULL;
    }
}

int readlines (char **lineptr) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= MAXLINES || (p = alloc(len)) == NULL) { // Es necesario tener algun lugar donde almacenar todas las lineas.
            return -10;
        }
        else {
            strcpy(p, line); // Copiar la linea (temporal) a p (espacio en almacenamiento)
            *(lineptr + nlines++) = p; // Guardar la direccion de la linea en el arreglo
        }
    }
    return nlines; // Retornar la cantidad de lineas
}

void swap(void *v[], int i, int j) { // swap no retorna nada y ahora recibe un arreglo de punteros genericos y dos indices: Ahora puede intercambiar punteros de cualquier tipo de dato.
    void *temp; // Puntero generico

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

double atof(const char s[]) {
    int i, signo, ctf_sign, ctf;
    double num, exp;

    i = 0;
    num = 0.0;

    while (isspace(s[i])) // Elimina posibles espacios en blanco al principio de la cadena 
        ++i; 

    signo = 1;
    if (s[i] == '-') {
        signo = -1;
        ++i; // Define signo del numero y trabaja con el indice si hay caracter de signo
    }
    else if (s[i] == '+')
        ++i;
    
    for (i; isdigit(s[i]); ++i)
        num = 10 * num + (s[i] - '0'); // Trabajar digitos antes del punto hasta que salga el punto
    
    exp = 1.0;
    if (s[i] == '.' || s[i] == ',') {
        for (i++; isdigit(s[i]); ++i) {
            num = 10 * num + (s[i] - '0');
            exp *= 1.0/10.0; // Trabaja numeros despues del punto
        }  
    } 

    if (tolower(s[i]) == 'e') { // Trabaja con la notacion cientifica
        ++i;
        if (s[i] == '-')
            ctf_sign = -1;
        else
            ctf_sign = 1;  // Trabajo con el signo de la notacion

        if (s[i] == '+' || s[i] == '-')
            ++i; // Trabajo con indice en caso de caracter de signo

        ctf = 0;
        for (i; isdigit(s[i]); ++i)
            ctf = 10 * ctf + (s[i] - '0'); // Obtencion de exponente como entero
        
        for (i = 0; i < ctf; ++i)
            (ctf_sign == -1) ? (exp *= 1.0/10.0) : (exp *= 10.0); // Conversion de notacion cientifica a double aplicandolo al exp obtenido antes
    }

    return signo * num * exp; // Se le pone el signo y se multiplica para dejar el punto donde corresponde
}

int numcmp (char *s1, char *s2) { // Compara s1 y s2 al volverlos double; ve cual es menor y retorna un entero a partir de eso.
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2); // Volver ambas cadenas un double equivalente.

    if (v1 < v2) // Retornar -1 si v1 es menor a v2, 1 si es mayor, 0 si son iguales.
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void all_tolower(char *ptr) {
    while(*ptr)
        *ptr++ = tolower(*ptr);
}

void cleanstr(char ptr[]) {
    int i, j;

    for (i = j = 0; ptr[i]; i++, j++)
        if (isalnum(ptr[i]) || isspace(ptr[i]))
            ptr[j] = ptr[i];
        else
            --j; 
}

void qsort_ascend(void *v[], int left, int right, int (*comp) (void *, void *), int eq, int dir_mode) { // Funcion qsort_ascend, no retorna nada; recibe array de punteros, dos indices, y un apuntador a funcion que retorna entero, y que recibe dos punteros genericos
    int i, last;
    char temp_a[MAXLEN];
    char temp_b[MAXLEN];

    if (left >= right) 
        return; 
    
    swap(v, left, (left + right) / 2); 
    last = left;
    for (i = left + 1; i <= right; i++) {
        strcpy(temp_a, v[i]); // Copiar las lineas estudiadas
        strcpy(temp_b, v[left]);

        if (dir_mode) { // Si están en modo orden de directorio, limpiar de caracteres no alfanumericos.
            cleanstr(temp_a);
            cleanstr(temp_b);
        }
        if (eq) { // Si se igualan mayusculas y minusculas poner en minusculas las dos copias.
            all_tolower(temp_a);
            all_tolower(temp_b);
        }

        if ((*comp)(temp_a, temp_b) < 0) // Hacer la comparacion entre las copias, pasadas a minusculas o no.
            swap(v, ++last, i);
        
    }
    swap(v, left, last);
    qsort_ascend(v, left, last-1, comp, eq, dir_mode); 
    qsort_ascend(v, last + 1, right, comp, eq, dir_mode); 
}

void qsort_descend(void *v[], int left, int right, int (*comp) (void *, void *), int eq, int dir_mode) { // Funcion qsort_descend, no retorna nada; recibe array de punteros, dos indices, y un apuntador a funcion que retorna entero, y que recibe dos punteros genericos
    int i, last;
    char temp_a[MAXLEN];
    char temp_b[MAXLEN];

    if (left >= right) 
        return; 
    
    swap(v, right, (left + right) / 2); 
    last = right; 
    for (i = right - 1; i >= left; i--)  {
        strcpy(temp_a, v[i]); // Copiar las lineas estudiadas
        strcpy(temp_b, v[right]);

        if (dir_mode) { // Si están en modo orden de directorio, limpiar de caracteres no alfanumericos.
            cleanstr(temp_a);
            cleanstr(temp_b);
        }
        if (eq) {
            all_tolower(temp_a);
            all_tolower(temp_b);
        }

        if ((*comp)(temp_a, temp_b) < 0)
            swap(v, --last, i);
    }
    swap(v, right, last); 
    qsort_descend(v, left, last-1, comp, eq, dir_mode);
    qsort_descend(v, last + 1, right, comp, eq, dir_mode);   
}

int main (int argc, char *argv[]) {
    int nlines;
    int numeric, descend, eq, dir_mode; // "Bools" para las distintas opciones entregables

    numeric = descend = eq = dir_mode = 0;

    if (argc > 1) // Si hay más de un argumento y el adicional es la opcion -n, poner verdadero al bool de comparacion numerica.
        for (--argc; argc > 0; --argc) // Para cada uno de los argumentos adicionales
            switch (argv[argc][1]) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    descend = 1;
                    break;
                case 'f':
                    eq = 1;
                    break;
                case 'd':
                    dir_mode = 1;
                    break;
                default:
                    printf("\nError: Opcion invalida.\nUso: [-n] [-r]");
                    return 1;
            }
    
    if ((nlines = readlines(lineptr)) > 0) { // Si hay lineas
        if (!descend)
            qsort_ascend((void **) lineptr, 0, nlines - 1, (int (*) (void *, void *)) (numeric ? numcmp : strcmp), eq, dir_mode);
        else
            qsort_descend((void **) lineptr, 0, nlines - 1, (int (*) (void *, void *)) (numeric ? numcmp : strcmp), eq, dir_mode);

        writelines(lineptr, nlines);
        return 0;
    }
    else if (nlines == -10) {
        printf("Error: Entrada demasiado grande para ordenar.\n");
        return 1;
    }
}
