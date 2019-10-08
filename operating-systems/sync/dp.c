/*
 * SOLUCION A LOS FILOSOFOS COMENSALES
 * SOLUCION IMPLEMENTADA EN BASE
 * A LO PROPUESTO EN EL LIBRO DE TANENBAUM
*/
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define EXIT_PROGRAM return 0
#define N 5
#define LEFT (phnum - 1  + N) % N 
#define RIGHT (phnum + 1) % N 
#define AND &&

enum {THINKING, HUNGRY, EATING} state[N];
sem_t *phil[N];
sem_t *mutex;

void cat(char str[], int i)
{
    int end = strlen(str);
    str[end++] = (char) i + '0';
    str[end] = '\0';
}
void test(int phnum) 
{ 
    if (state[phnum] == HUNGRY  && state[LEFT] != EATING && state[RIGHT] != EATING) { 
        state[phnum] = EATING; 
        sleep(2); 
        printf("FILOSOFO %d TOMA TENEDOR %d Y TENEDOR %d\n", phnum + 1, LEFT + 1, phnum + 1); 
        printf("FILOSOFO %d COME Y LUEGO EXISTE\n", phnum + 1);
        sem_post(phil[phnum]); 
    } 
}
void takeFork(int phnum) 
{ 
    sem_wait(mutex); 
    state[phnum] = HUNGRY; 
    printf("FILOSOFO %d TIENE HAMBRE\n", phnum + 1); 
    test(phnum); 
    sem_post(mutex); 
    sem_wait(phil[phnum]); 
    sleep(1); 
} 
void putFork(int phnum) 
{ 
    sem_wait(mutex); 
    state[phnum] = THINKING; 
    printf("FILOSOFO %d DEJA TENEDOR %d Y TENEDOR %d EN LA MESA\n", 
           phnum + 1, LEFT + 1, phnum + 1); 
    printf("FILOSOFO %d PIENSA Y LUEGO EXISTE\n", phnum + 1); 
    test(LEFT); 
    test(RIGHT); 
    sem_post(mutex); 
} 
  
void *philospher(void *num) 
{ 
    while (1) { 
        int i = *((int *) num);
        sleep(1); 
        takeFork(i); 
        sleep(0); 
        putFork(i); 
    } 
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
    for(i = 0; i < N; ++ i)
        sem_unlink(str);
    for(i = 0; i < N; ++ i)
        sem_open(str, O_CREAT, 0644, 0);
    sem_unlink("mutex");
    for (i = 0; i < N; i++) { 
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&ph[i], NULL, philospher, arg); 
    } 
    for (i = 0; i < N; i++) 
        pthread_join(ph[i], NULL); 
    EXIT_PROGRAM;
}