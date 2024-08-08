#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXSPACE 100000
#define MAXLEN 1000
#define MAXCAMP 10
#define MAXOPLEN 5
#define MAXBUFLEN 60
#define MAXCAMPS 50000

enum options {N, R, F, D};

char **lineptr[MAXLINES]; // Lineptr es un arreglo de apuntadores a arreglos de apuntadores a char. La notacion anterior al parecer requeria de la creacion de arrays de 10 elemetnos por NLINES

char *campos[MAXCAMPS]; // Buffer de almacenamiento de todos los campos, cada uno terminando en \0
char **campos_i = campos; // Puntero de guardado de campo.

char **save_campo (char *ptr) { // Revisa si es posible guardar el puntero del campo y lo guarda
    if (MAXCAMPS - (campos_i - campos) > 2) { // 2, para un puntero más y un '\0'
        *campos_i++ = ptr;
        return campos_i - 1;
    }
    else {
        return NULL;
        printf("Error: save_campo. Not enough space.\n");
    }
}

void end_campo() { // Termina el campo poniendo un '\0' en la ultima posicion. De esta manera es independiente del largo o un maximo de campo.
    if (MAXCAMPS - (campos_i - campos) > 1)
        *campos_i++ = NULL;
}

void writelines (char **lineptr[], int nlines) { // Recibe un numero de lineas y un arreglo de punteros
    int i;
    
    printf("\n\n");
    for (i = 0; i < nlines; ++i)
        printf("%s", *lineptr[i]);
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
        return i; // El largo considera TODOS los caracteres, al usarse para solicitar espacio en alloc_line
}

char buff[MAXSPACE];
char *buffp = buff; // buffp inicialmente apuntaba a 0. Debe comenzar como la misma direccion inicial en buff

char *alloc_line (int sp) {
    if (sp < MAXSPACE - (buffp - buff)) { // Si hay espacio disponible
        buffp += sp; // Correccion   
        return (buffp - sp); // Establecer la nueva direccion como la posicion del buffer ---> Incorrecto, retorno un puntero que deja un espacio entre linea y linea.
    }
    else {
        printf("alloc_line: not enough space.\n");
        return NULL;
    }
}

int readlines (char **lineptr[]) {
    int len, nlines, i, cmp;
    char *p, **c, line[MAXLEN];

    nlines = 0;
    
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= MAXLINES || (p = alloc_line(len)) == NULL) { // Es necesario tener algun lugar donde almacenar todas las lineas.
            return -10;
        }
        else {
            strcpy(p, line); // Copiar la linea (temporal) a p (espacio en almacenamiento)
            for (i = cmp = 0; cmp < 10; ++i) {
                if (i == 0) {
                    c = save_campo(p); // El primer campo es el inicio de la linea, que al mismo tiempo guarda toda la linea
                    lineptr[nlines] = c;
                    ++cmp;
                }
                else if (isspace(*(p + i))) { // Si es espacio, ignorar todos los demás espacios y guardar el campo desde el proximo caracter
                    for (i; isspace(*(p + i)); ++i)
                        ;
                    c = save_campo(p + i);
                    ++cmp;
                }
            }
            end_campo(); // Terminar el array de campos con '\0
            ++nlines;
        }
    }
    return nlines; // Retornar la cantidad de lineas
}

void swap(void **v[], int i, int j) { // swap no retorna nada y ahora recibe un arreglo de punteros genericos y dos indices: Ahora puede intercambiar punteros de cualquier tipo de dato.
    void *temp; // Puntero generico
    int k;

    for (k = 0; v[i][k] != NULL && v[j][k] != NULL; ++k) { // Intercambiar todos los campos
        temp = v[i][k];
        v[i][k] = v[j][k];
        v[j][k] = temp;
    }
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

void qsort_ascend(void **v[], int left, int right, int (*comp) (void *, void *), int eq, int dir_mode) { // Funcion qsort_ascend, no retorna nada; recibe array de punteros, dos indices, y un apuntador a funcion que retorna entero, y que recibe dos punteros genericos
    int i, last;
    char temp_a[MAXLEN];
    char temp_b[MAXLEN];

    if (left >= right) 
        return; 
    
    swap(v, left, (left + right) / 2); 
    last = left;
    for (i = left + 1; i <= right; i++) {
        strcpy(temp_a, (const char *) *v[i]); // Copiar las lineas estudiadas
        strcpy(temp_b, (const char *) *v[left]);

        if (dir_mode) { // Si están en modo orden de directorio, limpiar de caracteres no alfanumericos.
            cleanstr(temp_a);
            cleanstr(temp_b);
        }
        if (eq) { // Si se igualan mayusculas y minusculas poner en minusculas las dos copias.
            all_tolower(temp_a);
            all_tolower(temp_b);
        }

        if ((*comp)(temp_a, temp_b) < 0)  // Hacer la comparacion entre las copias, pasadas a minusculas o no.
            swap(v, ++last, i);

    }
    swap(v, left, last);
    qsort_ascend(v, left, last-1, comp, eq, dir_mode); 
    qsort_ascend(v, last + 1, right, comp, eq, dir_mode); 
}

void qsort_descend(void **v[], int left, int right, int (*comp) (void *, void *), int eq, int dir_mode) { // Funcion qsort_descend, no retorna nada; recibe array de punteros, dos indices, y un apuntador a funcion que retorna entero, y que recibe dos punteros genericos
    int i, last;
    char temp_a[MAXLEN];
    char temp_b[MAXLEN];

    if (left >= right) 
        return; 
    
    swap(v, right, (left + right) / 2); 
    last = right; 
    for (i = right - 1; i >= left; i--)  {
        strcpy(temp_a, (const char *) *v[i]); // Copiar las lineas estudiadas
        strcpy(temp_b, (const char *) *v[right]);

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

static char *camp_options[MAXCAMP]; // Array de punteros a opciones de campo en forma "(0/1)(0/1)(0/1)(0/1)" en orden n, r, f, d. Almacenados en un indice equivalente al campo. Maximo 9 campos.
static char options_buff[MAXBUFLEN]; // Buffer para guardar opciones
static char *options_buff_i = options_buff; // Direccion de espacio libre para escribir opciones

int saveopt (int n_cmp, char *str_op) {
    if (MAXBUFLEN - (options_buff_i - options_buff) > MAXOPLEN && n_cmp < MAXCAMP) { // Si hay espacio disponible
        camp_options[n_cmp] = options_buff_i; // Guardar el puntero a las opciones del numero de campo
        strcpy(options_buff_i, str_op); // Escribir las opciones del campo en su buffer
        options_buff_i += MAXOPLEN; // Actualizar indice del buffer de opciones.
        return 0;
    }
    else {
        printf("Error: Espacio insuficiente\n");
        return 1;
    }
}

int main (int argc, char *argv[]) {
    int nlines, i, n_campo, campos, mayor_cmp;
    char opstr[MAXOPLEN];

    mayor_cmp = n_campo = campos = 0;
    
    for (i = 0; i < MAXCAMP; ++i)
        saveopt(i, "0000"); // Inicializar todas las opciones en 0.

    if (argc > 1) 
        for (--argc, ++argv; argc > 0; --argc, ++argv) { // Para cada uno de los argumentos adicionales
            strcpy(opstr, "0000"); // Inicializar la opcion del campo como 0000
            i = 0;

            if ((*argv)[i] == '-') { // Si es una opcion
                ++campos;
                ++i;

                if (isdigit((*argv)[i])) {
                        n_campo = (*argv)[i] - '0'; // Establecer n° de campo
                        ++i;
                }

                if (n_campo > mayor_cmp)
                    mayor_cmp = n_campo; // Establecer el mayor campo

                for (i; (*argv)[i]; ++i) { // Para cada caracter de la opcion
                    switch((*argv)[i]) { // Construir opciones para el campo.
                        case 'n':
                            opstr[N] = '1';
                            break;
                        case 'r':
                            opstr[R] = '1';
                            break;
                        case 'f':
                            opstr[F] = '1';
                            break;
                        case 'd':
                            opstr[D] = '1';
                            break;
                        default:
                            printf("Error: Opcion invalida.\nUso: [-[num][n][r][f][d] ... | -[n][r][f][d]]");
                            return 1;
                    }
                }
            }
            else { // Si no es
                printf("Error: Opcion invalida.\nUso: [-[num][n][r][f][d] ... | -[n][r][f][d]]");
                return 1;
            }
            saveopt(n_campo, opstr);
        }   
    else { // Si no hay argumentos, guarda las opciones para el campo 1 predeterminado y establece 1 a la cantidad de campos.
        saveopt(n_campo, "0000");
        ++campos;
    }
    
    if ((nlines = readlines(lineptr)) > 0) { // Si hay lineas
        if (campos == 1) // Si solo hay un campo
            if (!(camp_options[0][R] - '0'))
                qsort_ascend((void ***) lineptr, 0, nlines - 1, (int (*) (void *, void *)) (camp_options[0][N] - '0' ? numcmp : strcmp), camp_options[0][F] - '0', camp_options[0][D] - '0');
            else
                qsort_descend((void ***) lineptr, 0, nlines - 1, (int (*) (void *, void *)) (camp_options[0][N] - '0' ? numcmp : strcmp), camp_options[0][F] - '0', camp_options[0][D] - '0');
        
        

        writelines(lineptr, nlines);
        return 0;
    }
    else if (nlines == -10) {
        printf("Error: Entrada demasiado grande para ordenar.\n");
        return 1;
    }
}
