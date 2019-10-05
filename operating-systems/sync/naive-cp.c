/*
 * VARIACION DEL PROBLEMA DE FILOSOFOS
 * SOLUCION NO CONCURRENTE(POR ESO NAIVE)
*/
#include <stdio.h> 
#include <stdlib.h>

#define EXIT_PROGRAM return 0
#define MAX_COMPUTER 5
#define NOT !
#define AND &&
#define LEFT(i, j) (i + MAX_COMPUTER - j) % MAX_COMPUTER
#define RIGHT(i, j) (i + j) % MAX_COMPUTER

int hand_state[MAX_COMPUTER];
int cnt;
int last_comp;
void printArray(void)
{
    int i;
    for(i = 0; i < MAX_COMPUTER; ++i)
        printf("%d, ", hand_state[i]);
    printf("\n");
}
void play(void)
{
    int i, j;
    /* SOLUCION PROPUESTA EN AYUDANTIA */
    for(i = 0, j = 0; j < 4 * MAX_COMPUTER; i = RIGHT(i, 2), ++j) {
        /* printf("COMPUTADOR %d NECESITA MANO %d Y MANO %d\n", i, RIGHT(i, 1), LEFT(i, 1)); */
        if(NOT hand_state[i] AND NOT hand_state[LEFT(i, 1)]){
            printf("COMPUTADOR %d RECIBE SEÑAL DE MANO %d\n", i + 1, LEFT(i, 1));
            hand_state[LEFT(i, 1)] = i + 1;
            printArray();
        } else if(hand_state[LEFT(i, 1)] == i + 1 AND NOT hand_state[i]) {
            printf("COMPUTADOR %d RECIBE SEÑAL DE MANO %d\n", i + 1, i);
            hand_state[i] = i + 1;
            printArray();
            if(NOT cnt) 
                last_comp = i;
            ++cnt;
        } 
        if(cnt == 2) {
            printf("______________\n");
            printf("COMPUTADOR %d JUEGA CON COMPUTADOR %d\n", i + 1, last_comp + 1);
            hand_state[i] = 0;
            hand_state[LEFT(i, 1)] = 0; 
            hand_state[last_comp] = 0;
            hand_state[LEFT(last_comp, 1)] = 0;
            printArray();
            printf("______________\n");
            cnt = 0;
            last_comp = 0;
        }
    }
}
int main(void)
{
    play();
    EXIT_PROGRAM;
}