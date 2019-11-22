#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define EXIT_PROGRAM return 0
#define BUFFER_SIZE (1U << 10) // 1024

/*
typedef struct {
    int buffer[BUFFER_SIZE];
    int front, tail, size;    
} monitor;
*/

int buffer[BUFFER_SIZE];
int front, tail, size;

void enqueue(int n)
{
    if(size == BUFFER_SIZE - 1) return;
    else buffer[tail++] = n;
    tail %= BUFFER_SIZE;
    ++size;
}
void dequeue()
{   
    if(size == 0) return ;
    else buffer[front++] = 0;
    front %= BUFFER_SIZE;
    --size;
}
pthread_cond_t empty = PTHREAD_COND_INITIALIZER,
    full = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex;
int loops = 10;

static void monEnter()
{
    pthread_mutex_lock(&mutex);
}
static void monProdExit()
{
    pthread_cond_signal(&full); 
    pthread_mutex_unlock(&mutex);
}
static void monConsExit()
{
    pthread_cond_signal(&empty); 
    pthread_mutex_unlock(&mutex);
}
static void monFullBuffer()
{
    while (size == BUFFER_SIZE - 1) 
        pthread_cond_wait(&empty, &mutex);
}
static void monEmptyBuffer()
{
    while (size == 0) 
        pthread_cond_wait(&full, &mutex); 
}
static void *monProducer() 
{
    for (int i = 0; i < loops; i++) {
        monEnter();
        monFullBuffer();
        printf("PRODUCIENDO %d \n", i);
        enqueue(i);
        monProdExit();
    } 
    pthread_exit(0);
}
static void *monConsumer () {
    for (int i = 0; i < loops; i++) {
        monEnter();
        monEmptyBuffer();
        int tmp = buffer[front];
        printf("CONSUMIENDO %d \n", tmp);
        dequeue();
        monConsExit();
    }
    pthread_exit(0);
}
int main(void)
{   
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&prod, NULL, &monProducer, NULL);
    pthread_create(&cons, NULL, &monConsumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    EXIT_PROGRAM;
}