/*
 * FILOSOFOS COMENSALES
 * SOLUCION CONCURRENTE
*/
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_PROGRAM return 0
#define N 5 /* NUMERO DE FILOSOFOS */
#define LEFT(i) (i - 1 + N) % N
#define RIGHT(i) (i + N) % N
#define AND &&
enum {THINKING, HUNGRY, EATING} state[N];

sem_t *phil[N];
sem_t *mutex;

void test(int i)
{
    if(state[i] == HUNGRY AND state[LEFT(i)] != EATING AND state[RIGHT(i)] != EATING) {
        state[i] = EATING;
        sem_post(phil[i]);
    }
}
void takeForks(int i)
{
    sem_wait(mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(mutex);
    sem_wait(phil[i]);
}
void putForks(int i)
{
    sem_wait(mutex);
    state[i] = THINKING;
    test(LEFT(i));
    test(RIGHT(i));
    sem_post(mutex);
}
void *philosopher(void *arg)
{
    int i = *((int *) arg);
    while(1) {
        printf("FILOSOFO %d PIENSA Y LUEGO EXISTE\n", i);
        sleep(2);
        takeForks(i);
        sleep(2);
        printf("FILOSOFO %d COME Y LUEGO PIENSA\n", i);
        putForks(i);
    }
    pthread_exit(NULL);
}
void cat(char str[], int i)
{
    int end = strlen(str);
    str[end++] = (char) i + '0';
    str[end] = '\0';
}
int main(void)
{
    int i;
    pthread_t ph[N];
    char str[8] = "phil";
    cat(str, 1);
    for(i = 0; i < N; ++ i)
        sem_unlink(str);
    for(i = 0; i < N; ++ i)
        sem_open(str, O_CREAT, 0644, 0);
    sem_unlink("mutex");
    sem_open("mutex", O_CREAT, 0644, 1);
    for(i = 0; i < N; ++i) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&ph[i], NULL, philosopher, arg);
    }
    printf("\n ______ \n");
    sleep(1);
    for(i = 0; i < N; ++i)
        pthread_join(ph[i], NULL);
    EXIT_PROGRAM;
}