/*
 * FILOSOFOS COMENSALES
 * SOLUCION CONCURRENTE
*/
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

#define EXIT_PROGRAM return 0
#define N 5 /* NUMERO DE FILOSOFOS */
#define LEFT (phnum + 4) % N /* filosofo a la izquierda */
#define RIGHT (phnum + 1) % N /* filosofo a la derecha */
#define MAX_IT 1 /* NUMERO DE ITERACIONES */ 
enum {THINKING, HUNGRY, EATING} state[5];
int phil[N] = { 0, 1, 2, 3, 4 }; /* aqui se guardan los pid de los thread */
sem_t mutex; /* para cuando comen */
sem_t S[N]; /* para agarrar tenedores */
void eat(int phnum) 
{ 
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) { 
        state[phnum] = EATING; 
        printf("FILOSOFO %d TOMA TENEDOR %d Y %d\n", phnum + 1, LEFT + 1, phnum + 1);   
        printf("FILOSOFO %d ESTA LISTO PARA COMER\n", phnum + 1); 
        sem_post(&S[phnum]); 
    } 
} 
void pickup(int phnum) 
{ 
    sem_wait(&mutex); 
    state[phnum] = HUNGRY; 
    printf("FILOSOFO %d TIENE HAMBRE\n", phnum + 1); 
    eat(phnum);   
    sem_post(&mutex); 
    sem_wait(&S[phnum]); 
} 
void putdown(int phnum) 
{ 
    sem_wait(&mutex); 
    state[phnum] = THINKING; 
    printf("FILOSOFO %d DEJA TENEDOR %d Y %d EN LA MESA\n", phnum + 1, LEFT + 1, phnum + 1); 
    printf("FILOSOFO %d ESTA PENSANDO\n", phnum + 1); 
    eat(LEFT); 
    eat(RIGHT);
    sem_post(&mutex); 
} 
void* philospher(void* num) 
{ 
    int j;
    for(j = 0; j < MAX_IT; ++j) { 
        printf("\n ITERACION %d \n", j);
        int* i = num; 
        pickup(*i); 
        putdown(*i); 
    } 
} 
int main(void)
{
    int i; pthread_t thread_id[N]; 
    sem_init(&mutex, 0, 1);   
    for (i = 0; i < N; i++) 
        sem_init(&S[i], 0, 0); 
    for (i = 0; i < N; i++) { 
        pthread_create(&thread_id[i], NULL, philospher, &phil[i]); 
        printf("FILOSOFO %d PENSANDO\n", i + 1); 
    } 
    for (i = 0; i < N; i++) 
        pthread_join(thread_id[i], NULL); 
    EXIT_PROGRAM;
}