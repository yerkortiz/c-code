/*
    AUTHOR: YERKO ORTIZ
    Code referenced from CLRS book
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EXIT_PROGRAM return 0
#define INF (1 << 30)

int max(int a, int b) { return (a > b) ? a: b; }

int naiveCutRod(int *p, int n) // EXPONENCIAL
{
    if(n == 0) return 0;
    int q, i;
    for(q = -INF, i = 0; i <= n; ++i)
        q = max(q, p[i]);
    return q;
}
int dpCutRod(int *p, int n) // CUADRATICO
{
    int i, q, j;
    int *r = malloc((n + 1) * sizeof(int));
    for(r[0] = 0, i = 1; i <= n; ++i) {
        for(q = -INF, j = 1; j <= i; ++j)
            q = max(q, p[j] + r[i - j]);
        r[j] = q;
    }
    return r[n];
}
int main(void)
{
    int n, i;
    int *p = malloc(n * sizeof(int));
    for(n = 10, i = 0; i < n; ++i)
        scanf("%d", &p[i]);
    printf("%d", dpCutRod(p, 8));
    free(p);
    EXIT_PROGRAM;
}