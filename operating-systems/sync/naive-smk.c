#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

#define EXIT_PROGRAM return 0
char *elementos[3] = {"MERCA", "PAPEL", "FUEGO"};
void fumadorMerca(void)
{
    printf("FUMADOR MERCA FUMA\n");
}
void fumadorPapel(void)
{
    printf("FUMADOR PAPEL FUMA\n");
}
void fumadorFuego(void)
{
    printf("FUMADOR FUEGO FUMA\n");
}
void agente(void)
{
    int i, j, k;
    int sum = 6;
    for(k = 0; k < 5; ++k) {
        i = rand() % 3;
        j = rand() % 3;
        if(i == j) j = (j ^ 1) % 3;
        ++i; ++j;
        printf("AGENTE SE SACA %s y %s\n", elementos[i - 1], elementos[j - 1]);
        sum -= (i + j);
        printf("FALTA %s\n", elementos[sum - 1]);
        switch(sum) {
            case 1: 
            fumadorMerca();
            break;
            case 2: 
            fumadorPapel();
            break;
            case 3: 
            fumadorFuego();
            break;
        }
        sum = 6;
    }
}
int main(void)
{
    agente();
    EXIT_PROGRAM;
}