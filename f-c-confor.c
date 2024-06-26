#include <stdio.h>

int fahr;

main() {
    printf("%6s %12s\n", "Fahrenheit", "Celcius");
    for(fahr = 0; fahr <= 300; fahr = fahr + 20){
        printf("%3d %17.2f\n", fahr, (5.0/9.0)*(fahr-32.0));
    }
    printf("Hecho!\n");
}