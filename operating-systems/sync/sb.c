/*
 * BARBERO DORMILON
*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define EXIT_PROGRAM
#define N 1

sem_t *customers, *barber, *mutex;
int current_seats = N;

void *barber_work(void *arg){ 
      while(1) { 
            sem_wait(customers); 
            sem_wait(mutex);
            if(current_seats == N) {
                printf("ZZZZZZ\n");
                sleep(1);
            }
            printf("ATIENDE AL PELELE, QUEDAN %d ASIENTOS\n", current_seats);
            current_seats++; 
            sleep(1);
            sem_post(barber); 
            sem_post(mutex); 
      } 
} 
void *customer(void *arg) { 
      while(1) { 
            sem_wait(mutex);
            if(current_seats > 0) { 
                printf("LLEGA UN PELELE, QUEDAN %d ASIENTOS\n", current_seats);
                current_seats--; 
                sem_post(customers); 
                sem_post(mutex);
                sem_wait(barber); 
            } else { 
                  sem_post(mutex); 
            } 
      } 
} 
int main(void)
{
    sem_unlink("customers"); sem_unlink("barber"); sem_unlink("mutex");
    customers = sem_open("customers", O_CREAT, 0644, 0);
    barber = sem_open("barber", O_CREAT, 0644, 0);
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    pthread_t b, c;
    pthread_create(&b, NULL, barber_work, NULL);
    pthread_create(&c, NULL, customer, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    sem_unlink("customers"); sem_unlink("barber"); sem_unlink("mutex");
    EXIT_PROGRAM;
}