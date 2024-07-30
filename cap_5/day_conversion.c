#include <stdio.h>

static char daytab[2][13] = { 
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} // Se inicia cada array en 0 para ajustar el indice al numero de mes
};

// Una funcion necesita saber cuantas columnas tiene el array bidimensional para asi poder hacer la aritmética de direcciones correctamente. dir = inicial + n_fila * columnas + m_columna

int day_of_year (int year, int month, int day) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0; // leap = 1 si el año es bisiesto (divisible por 4 Y no divisible por 100 O divisible por 400), si no, leap = 0

    if (year < 0 || month < 1 || month > 12 || day < 1 || day > daytab[leap][month]) { // Si es una fecha invalida
        printf("error: fecha invalida\n");
        return -1;
    }
    
    for (i = 1; i < month; i++) // Para cada mes, hasta el anterior del mes entregado
        day += daytab[leap][i]; // Sumar los días de cada mes correspondiente al año bisiesto o normal
    return day; // Retornar numero de dias
}

void month_day (int year, int yearday, int *pmonth, int *pday) { // Como debe entregar mes y año la unica alternativa es modificar algo en una direccion. De lo contrario solo se pasará un retorno
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0; // leap = 1 si el año es bisiesto (divisible por 4 Y no divisible por 100 O divisible por 400), si no, leap = 0

    for (i = 1; yearday > daytab[leap][i]; i++) // Mientras queden días en la cuenta de día del año, correspondientes a más de un solo mes
        yearday -= daytab[leap][i]; // Quitar a la cuenta la cantidad de días del mes ya pasado

    if (year < 0 || yearday > 365 || yearday < 1) // Si el año es menor a 0 y los dias del año superan un año mismo
        printf("error: fecha invalida\n");
    else {
        *pmonth = i; // Cuando for pare significa que los días que quedan en la cuenta son del ultimo mes i estudiado.
        *pday = yearday;  
    }
}

void main () {
    int dias, dia_mes, mes, anio = 2004;
    
    dias = day_of_year (anio, 9, 22);
    month_day (anio, dias, &mes, &dia_mes);

    if (dias > 0)
        printf("El %d/%d es el dia %d del %d\n", dia_mes, mes, dias, anio);
}