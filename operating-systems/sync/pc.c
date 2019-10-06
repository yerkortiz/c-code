/*
 * PRODUCTOR CONSUMIDOR
 * SEMAFOROS
*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define EXIT_PROGRAM return 0
#define BUFFER_SIZE 1 << 4

sem_t *empty, *full, *mutex;
int produced, consumed;
int buffer[BUFFER_SIZE];
int front, size, tail;
void *consumer(void *arg)
{
    while(1) {
        sem_wait(full);
        sem_wait(mutex);
        if(size > 0) {
            sleep(1);
            consumed += buffer[front++];
            front %= BUFFER_SIZE;
            --size;
            printf("CONSUMIENDO %d\n", consumed);
        } else {
            printf("BUFFER VACIO\n");
        }
        sem_post(mutex);
        sem_post(empty);
    }
    pthread_exit(NULL);
}
void *producer(void *arg)
{
    while(1) {
        sem_wait(empty);
        sem_wait(mutex);
        if(size < BUFFER_SIZE){
            sleep(1);
            buffer[tail++] = ++produced;
            tail %= BUFFER_SIZE;
            ++size;
            printf("PRODUCIENDO %d \n", produced);
        } else {
            printf("BUFFER LLENO\n");
        }
        sem_post(mutex);
        sem_post(full);
    }
    pthread_exit(NULL);
}
int main(void)
{
    sem_unlink("empty"); sem_unlink("full"); sem_unlink("mutex");
    empty = sem_open("empty", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("full", O_CREAT, 0644, 0);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    pthread_t pid, cid;
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    sleep(1);
    pthread_join(cid, NULL);
    sem_unlink("empty"); sem_unlink("full"); sem_unlink("mutex");
    EXIT_PROGRAM;
}