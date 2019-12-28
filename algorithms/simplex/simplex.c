#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int n, m, o, i, j;
    scanf("%d %d %d", &n, &m, &o);
    int *A = (int *) malloc(n * m * sizeof(int));
    int *b = (int *) malloc(m * sizeof(int));
    int *c = (int *) malloc(n * sizeof(int));
    int *s = (int *) malloc(m * sizeof(int));
    for(i = 0; i < n; ++i)
        for(j = 0; j < m; ++j) 
            scanf("%d", &A[i * n + j]);
    for(j = 0; j < m; ++j) scanf("%d", &b[j]);
    for(i = 0; i < n; ++i) scanf("%d", &c[i]);
    for(j = 0; j < m; ++j) scanf("%d", &s[j]);
    
    return 0;
}