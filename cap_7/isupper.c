// Ejercicio 7-9

int itisuper (unsigned *c) {
    // Revisa si c es MAYUS considerando A = 65, Z = 90.
    // Retorna algo si es, retorna 0 si no.

    // if (c >= 65 && c <= 90) Claramente funciona, pero se puede
    //    return c;            comprimir aun más para usar menos
    //else                     espacio y ser más veloz.
    //    return 0;

    return (c >= 65 && c <= 90); // O es 1, o es 0.
}