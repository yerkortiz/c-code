#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define EXIT_PROGRAM return 0
#define N 8
#define M 16

sem_t *oxy_s, *hyd_s;
pthread_mutex_t mutex;
int oxy, hyd;

void *oxygen(void *arg)
{
    pthread_mutex_lock(&mutex);
    ++oxy;
    if (hyd >= 2){
        sem_post(hyd_s);
        sem_post(hyd_s);
        hyd -= 2;
        sem_post(oxy_s);
        --oxy;
        printf("MOLECULA CRAFTEADA\n");
    } else {
        //printf("FALTAN ATOMOS\n");
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    sem_wait(oxy_s);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
void *hydrogen(void *arg)
{
    pthread_mutex_lock(&mutex);
    ++hyd;
    if (hyd >= 2 && oxy>= 1) {
        sem_post(hyd_s);
        sem_post(hyd_s);
        hyd -= 2;
        sem_post(oxy_s);
        --oxy;
        printf("MOLECULA CRAFTEADA\n");
    } else {
        //printf("FALTAN ATOMOS\n");
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    sem_wait(hyd_s);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
int main(void)
{
    int i;
    pthread_mutex_init(&mutex, NULL);
    pthread_t ox[N], hy[M];
    for(i = 0; i < N; ++i)
        pthread_create(&ox[i], NULL, oxygen, NULL);
    for(i = 0; i < M; ++i)
        pthread_create(&hy[i], NULL, hydrogen, NULL);
    for(i = 0; i < N; ++i)
        pthread_join(ox[i], NULL);
    for(i = 0; i < M;++ i)
        pthread_join(hy[i], NULL);
    return 0;
}