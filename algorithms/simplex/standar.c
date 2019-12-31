#include <stdio.h>
#include <stdlib.h>

#define MAIN_PROGRAM main
#define EXIT_PROGRAM return 0

/* De momento se asume que la naturaleza de todas las variables es >= 0 */

int MAIN_PROGRAM(void)
{
    int n, m, o, i, j, cnt;
    scanf("%d %d %d", &n, &m, &o);
    int *A = (int *) malloc(n * m * sizeof(int));
    int *b = (int *) malloc(m * sizeof(int));
    int *c = (int *) malloc(n * sizeof(int));
    int *s = (int *) malloc(m * sizeof(int));
    for(i = 0; i < n; ++i)
        for(j = 0; j < m; ++j) 
            scanf("%d", &A[j * m + i]);
    for(j = 0; j < m; ++j) scanf("%d", &b[j]);
    for(i = 0; i < n; ++i) scanf("%d", &c[i]);
    for(j = 0; j < m; ++j) scanf("%d", &s[j]);

    /* Contar el numero de variable extra para asignar suficiente*/
    for(j = 0, cnt = 0; j < m; ++j) 
        if(s[j] != 1) ++cnt;

    /* Nuevos parametros del sistema */
    printf("%d %d %d\n", n + cnt, m, o);
    /* Nuevo vector de costos */
    for(i = 0; i < n + cnt; ++i) 
        printf("%d ", (i < n)? c[i] : 0);
    putchar('\n');
    
    /* Vector b se mantiene igual */
    for(j = 0; j < m; ++j)
        printf("%d\n", b[j]);

    /* Nueva matriz a */
    /* Este codigo se puede reducir si se usa alguna struct que almacene pares */
    int cnt2 = 0, stc = 0;
    for(j = 0; j < m; ++j) {
        for(i = 0; i < n + cnt ; ++i) {
            if(s[j] == 0 && i == n + cnt2 && stc == 0){
                printf("%d ", (i < n)? A[i * n + j]: 1);
                ++cnt2;
                stc = 1;
            } else if(s[j] == 2 && i == n + cnt2 && stc == 0) {
                printf("%d ", (i < n)? A[i * n + j]: -1);
                ++cnt2;
                stc = 1;
            } else {
                printf("%d ", (i < n)? A[i * n + j]: 0);
            }
        }
        putchar('\n');
        stc = 0;
    }
    EXIT_PROGRAM;
}