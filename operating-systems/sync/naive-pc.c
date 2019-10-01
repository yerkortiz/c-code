/*
 * EJEMPLO NO CONCURRENTE DE PRODUCTOR CONSUMIDOR
 * PERO LA GRACIA ES HACERLO CONCURRENTE 
*/
#include <stdio.h>
#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
int cont, in, out;
void producer(void)
{
    while(cont == BUFFER_SIZE)
        ;
    buffer[in++] = 1;
    in %= BUFFER_SIZE;
    ++cont;
}
void consumer(void)
{
    while(cont == 0)
        ;
    buffer[out++] = 0;
    out %= BUFFER_SIZE;
    --cont;
}
int main(void)
{
    for(int i = 0; i < 2; ++i) {
        producer();
        printf("IN %d COUNT %d\n", in, cont);
        consumer();
        printf("OUT %d COUNT %d\n", out, cont);
    }
    return 0;
}