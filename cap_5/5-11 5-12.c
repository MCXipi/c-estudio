#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Modifique el programa entab y detab (escritos como ejercicios en
// el capítulo 1) para que acepten una lista de puntos de tabulación como argumentos.
// Utilice los tabuladores habituales si no hay argumentos

// Extienda entab y detab de modo que acepten la abreviatura
// entab —m + n que indica puntos de tabulación cada n columnas, iniciando en la columna m. Seleccione
// el comportamiento por omisión más conveniente (para el usuario).

// Ejercicio 1-20. Escriba un programa detab que reemplace tabuladores de la entrada
// con el número apropiado de blancos para espaciar hasta el siguiente paro
// de tabulación. Considere un conjunto fijo de paros de tabulación, digamos cada
// n columnas. ¿Debe ser n una variable o un parámetro simbólico? □

// Ejercicio 1-21. Escriba un programa entab que reemplace cadenas de blancos
// por el mínimo número de tabuladores y blancos para obtener el mismo espaciado.
// Considere los paros de tabulación de igual manera que para detab. Cuando un
// tabulador o un simple espacio en blanco fuese suficiente para alcanzar un paro
// de tabulación, ¿a cuál se le debe dar preferencia?

// Pasar como argumento el numero de espacios que corresponden a un tabulador. Entab reemplaza los espacios en blanco por el minimo de tabs y espacios para verse igual. Detab reemplaza los tabs por espacios.

// Entab y detab piden individualmente una linea y a medida que la van escribiendo van trabajando con los espacios. El trabajo mientras se escribe es facilitado por un buffer

#define MAXCHARS 150
enum bool {FALSE, TRUE};

static char savedchar[MAXCHARS];
static int i_saved;

char getch () {
    return (i_saved > 0) ? savedchar[--i_saved] : getchar();
}

char savechar (char c) {
    if (i_saved < MAXCHARS) {
        savedchar[i_saved++] = c;
        return c;
    }
    else {
        printf("Error. Too many saved characters.\n");
        return 0;
    }
}

static char spacebuf[MAXCHARS];
static int i_spacebuf; // Al final solo entab necesitó este buffer, por lo que podrían haber sido variables automaticas, de menos espacio e importancia.

void entab (int m, int n) {
    int c, i, cols = 1;
    printf("entab: Type your line.\n");
    while((c = getch()) != '\n') { // Mientras el caracter de entrada no sea \0, es decir, ya no hay más entrada
        if (c == ' ' && i_spacebuf < n && cols >= m) // Si es un espacio, pasada la columna de estudio inicial m, guardarlo en el buffer e ir sumando al indice
            spacebuf[i_spacebuf++] = ' ';
        else if (i_spacebuf == n) { // Si el indice indica suficientes espacios para un tabulador, escribe un tabulador y guarda el caracter ignorado
            savechar(c);
            putchar('t');
            i_spacebuf = 0; // Reinicia indice del buffer.
        }
        else if (i_spacebuf > 0) { // Si c no es espacio y hay caracteres en el buffer de espacios
            for (i = 0; i < i_spacebuf; ++i)
                putchar(spacebuf[i]); // Escribir todos los caracteres en blanco
            i_spacebuf = 0;
            putchar(c); // Escribir el caracter siguiente
        }
        else // En cualquier otro caso, osea si no es espacio y el i_spacebuf es 0
            putchar(c); // Escribir la letra.
        ++cols; // Aumentar el numero de columna estudiada.
    }
    putchar('\n');
}

void detab (int m, int n) {
    int cols = 1, sp, c, i;

    printf("detab: Type your line.\n");
    while((c = getch()) != '\n') { // Mientras el caracter pedido no sea nueva linea
        if (c == '\t' && cols >= m) { // Si el caracter es un tab y la columna es igual o mayor a la inicial
            for (i = 0, sp = 0; (sp = n * i - cols) <= 0; ++i) // Para un i, aumentarlo hasta que multiplicado por n, la resta con la columna actual sea positiva, es decir, que falten espacios a la derecha para alcanzarlo
                ;
            for (; sp; --sp)
                putchar(' '); // Poner los espacios en blanco faltantes
        }
        else
            putchar(c);
        ++cols; // Aumentar el numero de columna
    }
    putchar('\n');
}

// La sintaxis permitirá entonces .\programa {-d | -e | -d -e} < -<m> + n | <n> > donde si no se especifica n, este será 8.
int main (int argc, char **argv) {
    int det = FALSE, ent = FALSE, m = 0, n = 8; // Inicializo las variables relacionadas a opciones y a las columnas y espacios predeterminados.

    if (argc <= 2) { // Si no hay suficientes argumentos
        printf("Syntax: {-detab | -entab | -detab -entab} {-<m> + n | n >}\n");
        return NULL;
    }

    while (--argc > 0) { // Mientras hayan argumentos;
        if (**++argv == '-' && isdigit(*(*argv + 1))) {// Si se envio una opcion y es un numero, osea es -<m>+n
            for (++(*argv); isdigit(**argv); ++(*argv)) // Mientras sea un numero
                m = 10 * m + (**argv - '0'); // Agregarlo a m
            if (**argv == '+') { // Si ademas se establecio n
                n = 0; // Reinicio n para que no haya conflictos con la lectura
                for (++(*argv); isdigit(**argv); ++(*argv))
                    n = 10 * n + (**argv - '0'); // Establecerlo como n
            }
        }    

        else if (**argv == '-') // Si lo enviado al menos es una funcion
            switch(*(*argv + 1)) { // Determinar cual de las dos fue, y activar su bool, o de lo contrario retornar error.
                case 'd':
                    det = TRUE;
                    break;
                case 'e':
                    ent = TRUE;
                    break;
                default:
                    printf("Syntax: {-detab | -entab | -detab -entab} {-<m> + n | n >}\n");
                    return NULL;
            }

        else if (isdigit(**argv) && n == 8) { // Si lo enviado es un numero y n no ha sido cambiado, entonces el argumento es para n,
            n = 0; // Reinicio n para que no haya conflictos con la lectura
            for (; isdigit(**argv); ++(*argv))
                    n = 10 * n + (**argv - '0'); // Establecerlo como n
        }
        else { // En cualquier otro caso no es un numero, ya se cambio n, etc etc, retorar error.
            printf("Syntax: {-detab | -entab | -detab -entab} {-<m> + n | n >}\n");
            return NULL;
        }
    }

    if (ent) // Si se pidió entab o detab o ambos en las opciones, llamar a la funcion.
        entab(m, n);
    if (det)
        detab(m, n);
    return 1;
    
}