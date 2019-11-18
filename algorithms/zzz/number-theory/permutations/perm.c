/*
* ALGORITMO RECURSIVO PARA SACAR LAS PERMUTACIONES
* DE UN CONJUNTO
*/
#include <stdio.h>
#define SIZE_MAX  (1ul << 32) - 1
#define TRUE 1
#define FALSE 0
#define EXIT_PROGRAM return 0
typedef unsigned long long ull_t;
ull_t vector[SIZE_MAX] = {0};
ull_t *current = vector;
ull_t chosen[4] = {0};
void printPermutation(void)
{
    for(ull_t *it = vector; it < current; ++it)
        printf("%llu ", *it);
    putchar('\n');
}
void permutations(ull_t n)
{
    if(current - vector == n)
        printPermutation();
    else {
        for(ull_t i = 1; i <= n; ++i) {
            if (chosen[i]) continue;
            chosen[i] = TRUE;
            *(current++) = i;
            permutations(n);
            chosen[i] = FALSE;
            --current;
        }
    }
}
int main()
{
    permutations(3);
    EXIT_PROGRAM;
}