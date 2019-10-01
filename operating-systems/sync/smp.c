/*
  Compilar:
    gcc -o semaforo semaforo.c -lpthread
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
 
sem_t mutex;
 
void* thread(void* arg)
{
    //wait
    sem_wait(&mutex);
    printf("\n ENTER\n");
 
    printf("\n SECCIÓN CRÍTICA\n");
    sleep(1);
    printf("\n WAKE UP \n");
     
    printf("\n EXIT\n");
    sem_post(&mutex);
}
int main()
{
    sem_init(&mutex, 0, 1);
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread,NULL);
    sleep(1);
    pthread_create(&t2,NULL,thread,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return 0;
}