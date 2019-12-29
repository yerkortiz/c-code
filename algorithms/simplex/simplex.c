/*
    Author: Yerko Ortiz
*/
#include <stdio.h>
#include <stdlib.h>

#define MAIN_PROGRAM main
#define EXIT_PROGRAM return 0

void currentValue(int *c, int *x, int n)
{
    int value, i;
    for(i = 0; i < n; ++i)
        value += (x[i] * c[i]);
    printf("Valor Función Objetivo %d\n", value);
}
void mtrxProd(int *A, int *B, int *product, int n, int m, int p)
{
    int i, j, k, sum = 0;
    for (i = 0; i < n; ++i) 
      for (j = 0; j < m; ++j) {
        for (k = 0; k < p; ++k) sum = sum + A[i * n + k] * B[k * m + j];
        product[j * m + k] = sum;
        sum = 0;
      }
}
int MAIN_PROGRAM(void)
{
    int n, m, o, i, j;
    scanf("%d %d %d", &n, &m, &o);
    int *A = (int *) malloc(n * m * sizeof(int));
    int *b = (int *) malloc(m * sizeof(int));
    int *c = (int *) malloc(n * sizeof(int));
    int *s = (int *) malloc(m * sizeof(int));
    int *x = (int *) malloc(n * sizeof(int));
    for(i = 0; i < n; ++i)
        for(j = 0; j < m; ++j) 
            scanf("%d", &A[i * n + j]);
    for(j = 0; j < m; ++j) scanf("%d", &b[j]);
    for(i = 0; i < n; ++i) scanf("%d", &c[i]);
    for(j = 0; j < m; ++j) scanf("%d", &s[j]);
    EXIT_PROGRAM;
}