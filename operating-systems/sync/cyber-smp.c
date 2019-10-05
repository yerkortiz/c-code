#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

#define EXIT_PROGRAM return 0
#define MAX_COMPUTER 5
#define NOT !
#define AND &&
#define LEFT(i, j) (i + MAX_COMPUTER - j) % MAX_COMPUTER
#define RIGHT(i, j) (i + j) % MAX_COMPUTER
/* 
 * ESTADO DE UN COMPUTADOR,
 * WAITING = 0 MANOS, BORED = 1 MANO, 
 * PLAYING = 2 MANOS 
*/
enum {WAITING, BORED, PLAYING} state[MAX_COMPUTER]; 
int hand_state[MAX_COMPUTER] = {0};
//int play_ready[MAX_COMPUTER];
//int current_ready;
/* 
 * ESTA FUNCION(play) SOLUCIONA EL PROBLEMA DE FORMA 
 * NO CONCURRENTE 
*/
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
    /* Iterar pares y luego impares */
    for(i = 0, j = 0; j < 2 * MAX_COMPUTER; i = RIGHT(i, 2), ++j) {
        /* printf("COMPUTADOR %d NECESITA MANO %d Y MANO %d\n", i, RIGHT(i, 1), LEFT(i, 1)); */
        if(NOT hand_state[i] AND NOT hand_state[LEFT(i, 1)]){
            printf("COMPUTADOR %d RECIBE SEÑAL DE MANO %d\n", i, LEFT(i, 1));
            ++hand_state[LEFT(i, 1)];
            printArray();
        } else if(hand_state[LEFT(i, 1)] AND NOT hand_state[i]) {
            printf("COMPUTADOR %d RECIBE SEÑAL DE MANO %d\n", i, i);
            printArray();
            ++hand_state[i];
            printf("______________\n");
            printf("COMPUTADOR %d JUEGA CON COMPUTADOR %d\n")
        }
    }
}
int main(void)
{
    play();
    EXIT_PROGRAM;
}