/*
 * LECTOR ESCRITOR USANDO SEMAFOROS
 * PD: sem_open LO USO SOLAMENTE PORQUE sem_init 
 * ESTA DEPRECADO EN OSX Y YA NO ESTA FUNCIONAL,
 * SI USAN LINUX PREFIERAN sem_init, TODO LES SALDRA
 * DE MANERA MAS SENCILLA.
*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define EXIT_PROGRAM return 0
#define STR_SIZE (1 << 8)
#define TRUE 1

char PERGAMINO[STR_SIZE];
sem_t *mutex, *acc;
int rc, i;

void *reader(void *arg)
{
    while(TRUE)
    {
        sem_wait(mutex);
        ++rc;
        if(rc) sem_wait(acc);
        sem_post(mutex);
        printf("LEYENDO EL PERGAMINO: %s\n", PERGAMINO);
        sleep(1);
        sem_wait(mutex);
        --rc;
        if(!rc) sem_post(acc);
        sem_post(mutex);
    }
}
void *writer(void *arg)
{
    while(TRUE)
    {
        sem_wait(acc);
        printf("ESCRIBIENDO EL PERGAMINO %d\n", i);
        sleep(1);
        PERGAMINO[i++] = 'A';
        PERGAMINO[i] = '\0';
        sem_post(acc);
    }
}
int main(void)
{
    pthread_t rd, wt;
    sem_unlink("mutex"); sem_unlink("acc");
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    acc = sem_open("acc", O_CREAT, 0644, 1);
    pthread_create(&rd, NULL, reader, NULL);
    sleep(2);
    pthread_create(&wt, NULL, writer, NULL);
    pthread_join(rd, NULL);
    pthread_join(wt, NULL);
    sem_unlink("mutex"); sem_unlink("acc");
    EXIT_PROGRAM;
}