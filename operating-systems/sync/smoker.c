#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#define EXIT_PROGRAM return 0
char *elementos[3] = {"MALICIA", "PAPEL", "FUEGO"};
int recurso_mesa[3] = {0, 0, 0};
pthread_mutex_t mutex;
pthread_cond_t cond_var1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_var2 = PTHREAD_COND_INITIALIZER;
void *agente(void *arg)
{
    int i, j, k, sum;
    while(1) {
        sum = 6;
        i = rand() % 3;
        j = rand() % 3;
        if(i == j) j = (j ^ 1) % 3;
        ++i; ++j;
        sum -= (i + j);
        pthread_mutex_lock(&mutex);
        if(recurso_mesa[0] || recurso_mesa[1] || recurso_mesa[2]) {
            pthread_cond_wait(&cond_var2, &mutex);
        }
        recurso_mesa[i - 1] = 1;
        recurso_mesa[j - 1] = 1;
        pthread_cond_signal(&cond_var1);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
void *fumeta1(void *arg)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        if (!(recurso_mesa[1] && recurso_mesa[2])) {
            pthread_cond_wait(&cond_var1, &mutex);
        } else {
            pthread_cond_signal(&cond_var2);
            pthread_mutex_unlock(&mutex);

            pthread_exit(NULL);
        }
        printf("AGENTE SE SACA %s y %s\n", elementos[1], elementos[2]);
        printf("FALTA %s\n", elementos[0]);
        printf("FUMETA DE LA MALICIA FUMA\n");
        sleep(2);
        recurso_mesa[1] = 0;
        recurso_mesa[2] = 0;
        pthread_cond_signal(&cond_var2);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
void *fumeta2(void *arg) 
{
    while (1) {
        pthread_mutex_lock(&mutex);
        if (!(recurso_mesa[0] && recurso_mesa[2])) {
            pthread_cond_wait(&cond_var1, &mutex);
        } else {
            pthread_cond_signal(&cond_var2);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        printf("AGENTE SE SACA %s y %s\n", elementos[0], elementos[2]);
        printf("FALTA %s\n", elementos[1]);
        printf("FUMETA DEL PAPEL FUMA\n");
        sleep(2);
        recurso_mesa[0] = 0;
        recurso_mesa[2] = 0;
        pthread_cond_signal(&cond_var2);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
void *fumeta3(void *arg)
{
    while (1) {
        pthread_mutex_lock(&mutex);
        if (!(recurso_mesa[1] && recurso_mesa[0])) {
            pthread_cond_wait(&cond_var1, &mutex);
        } else {
            pthread_cond_signal(&cond_var2);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        printf("AGENTE SE SACA %s y %s\n", elementos[1], elementos[0]);
        printf("FALTA %s\n", elementos[2]);
        printf("FUMETA DEL FUEGO FUMA\n");
        sleep(2);
        recurso_mesa[1] = 0;
        recurso_mesa[0] = 0;
        pthread_cond_signal(&cond_var2);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
int main(void)
{
    pthread_t agent, f1, f2, f3;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&agent, NULL, agente, NULL);
    pthread_create(&f1, NULL, fumeta1, NULL);
    pthread_create(&f2, NULL, fumeta2, NULL);
    pthread_create(&f3, NULL, fumeta3, NULL);
    pthread_join(agent, NULL);
    pthread_join(f1, NULL);
    pthread_join(f2, NULL);
    pthread_join(f3, NULL);
    EXIT_PROGRAM;
}