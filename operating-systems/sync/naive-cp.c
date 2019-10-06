/*
 * SOLUCION NO CONCURRENTE DEL PROBLEMA DE LOS FILOSOFOS
*/
#include <stdio.h> 
#include <stdlib.h>

#define EXIT_PROGRAM return 0
#define MAX_PHILOSOPHERS 5
#define NOT !
#define AND &&
#define LEFT(i, j) (i + MAX_PHILOSOPHERS - j) % MAX_PHILOSOPHERS
#define RIGHT(i, j) (i + j) % MAX_PHILOSOPHERS

int fork_state[MAX_PHILOSOPHERS];

void printArray(void)
{
    int i;
    for(i = 0; i < MAX_PHILOSOPHERS; ++i)
        printf("%d, ", fork_state[i]);
    printf("\n");
}
void play(void)
{
    int i, j;
    /* SOLUCION PROPUESTA EN AYUDANTIA */
    for(i = 0, j = 0; j < 5 * MAX_PHILOSOPHERS; i = RIGHT(i, 2), ++j) {
        /* printf("COMPUTADOR %d NECESITA MANO %d Y MANO %d\n", i, RIGHT(i, 1), LEFT(i, 1)); */
        if(NOT fork_state[i] AND NOT fork_state[LEFT(i, 1)]){
            printf("FILOSOFO %d AGARRA TENEDOR %d\n", i + 1, LEFT(i, 1));
            fork_state[LEFT(i, 1)] = i + 1;
            printArray();
        } else if(fork_state[LEFT(i, 1)] == i + 1 AND NOT fork_state[i]) {
            printf("FILOSOFO %d AGARRA TENEDOR %d\n", i + 1, i);
            fork_state[i] = i + 1;
            printArray();
            printf("FILOSOFO %d COME\n", i + 1);
            printf("FILOSOFO %d SUELTA LOS TENEDORES, %d, %d\n", i + 1, i, LEFT(i, 1));
            fork_state[i] = 0;
            fork_state[LEFT(i, 1)] = 0;
            printArray();
        } 
    }
}
int main(void)
{
    play();
    EXIT_PROGRAM;
}