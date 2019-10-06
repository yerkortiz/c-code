#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#define EXIT_PROGRAM return 0
sem_t *mutex;
void *f(void *arg)
{
    sem_wait(mutex);
    sem_post(mutex);
    pthread_exit(NULL);
}
int main()
{
    sem_unlink("mutex");
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    pthread_t fn;
    pthread_create(&fn, NULL, f, NULL);
    pthread_join(fn, NULL);
    sem_unlink("mutex");
    EXIT_PROGRAM;
}