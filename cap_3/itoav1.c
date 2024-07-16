#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
    int i, temp; // Indice que parte al principio
    size_t j; // Indice que viene del final

    for (i = 0, j = strlen(s) - 2; i < j; ++i, --j) { // strlen - 2 pues strlen - 1 lo vuelve indice, y strlen - 2 no cuenta '\n'
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    } 
}

// 

void itoa(int n, char s[]) {
    int i, sign;

    // En un sistema complemento a dos de n bits, o el tamaño de la palabra n, el minimo valor negativo es de -2^(n - 1) pero el maximo es 2^(n - 1) - 1 
    // puesto que se incluye el 0. Es por esto que dentro del codigo original:
    // if ((sign = n) < 0)
    //    n = -n; <-- Si n = -2^(n - 1), el nuevo n = 2^(n - 1) el cual está 1 numero por sobre el limite maximo positivo produce overflow.
    // Además, dato curioso, los numeros negativos en binario son el complemento del valor absoluto más uno, y el bit más significativo, el más grande o a la izquierda
    // del sistema de n bits, indica si tiene signo (1) o no (0).


    // En la nueva version:
    if ((sign = n) < 0)
        n = -(n + 1); // En cualquier caso le quito uno al numero negativo (Aunque en realidad le sumo)
    
    i = 0;
    do
        s[i++] = n % 10 + '0';
    while ((n /= 10) > 0);

    if (sign < 0) {
        s[i++] = '-';
        ++s[0]; // Y en esta parte lo devuelvo. 
    }
    s[i++] = '\n';
    s[i] = '\0';
    reverse(s);

    // La forma de ChatGPT es muy inteligente también. En vez de usar un tipo signed como puede ser un int (Aunque depende del compilador), simplemente crea una
    // variable temporal unsigned la cual si o si almacenará el numero, al tener un numero maximo positivo de 2^(n - 1) + 2^(n - 1) - 1 = 2^n - 1
}

void main() {
    int test = 1023456789;
    char s[12];

    itoa(test, s);
    printf("Numero: %d. String: %s", test, s);
}