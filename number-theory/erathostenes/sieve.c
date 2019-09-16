/*
* CON EXTENDED ERATHOSTENES
* SE PUEDE CALCULAR LOS FACTORES PRIMOS DE
* UN ENTERO N CUALQUIERA EN COMPLEJIDAD
* O(LOG(N)).
*/
#include <stdio.h>
#define MAX_SIZE (1 << 8)
int primes[MAX_SIZE];
int *end = primes;
void printPrimes(void)
{
    for(int *it = (primes + 2), i = 2; it < end; ++it, ++i)
        printf("NÚMERO %d: %s\n", i, (*it) ? "COMPUESTO" : "PRIMO");
}
void printMinFactor(void)
{
    for(int *it = (primes + 2), i = 2; it < end; ++it, ++i)
        printf("NÚMERO %d TIENE MÍNIMO FACTOR %d \n", i, *it);
}
void erathostenes(int n)
{
    end += (n + 1);
    for(int i = 2; i <= n; ++i) {
        if (primes[i]) continue;
        for(int j = i << 1; j <= n; j += i)
            primes[j] = 1;
    }
}
void extendedErathostenes(int n)
{
    end += (n + 1);
    for(int i = 2; i <= n; ++i) {
        if (primes[i]) continue;
        for(int j = i << 1; j <= n; j += i)
            primes[j] = i;
    }
}
int main()
{
    //erathostenes((1 << 8) - 1);
    //printPrimes();
    extendedErathostenes((1 << 5) - 1);
    printMinFactor();
    return 0;
}