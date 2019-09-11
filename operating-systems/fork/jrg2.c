/*
JEROGLIFICO 5
LA CONJETURA DE COLLATZ ES UN CLÁSICO EN 
CIENCIAS DE COMPUTACION, EN MUCHOS LIBROS DE ALGORITMOS
O MATES DISCRETAS LES SALDRÁ
ESTA SIMPATICA FUNCIÓN RECURSIVA, ES MÁS, EXISTE
UN PROBLEMA IRRESUELTO EN LA ACTUALIDAD QUE CONSISTE
EN DEMOSTRAR MATEMATICAMENTE QUE PARA TODO NÚMERO
N, LA SECUENCIA DE COLLATZ LLEGA A TERMINO.
SI, SÉ QUE MUCHOS ESTÁN PENSANDO EN QUE SOLO 
LES IMPORTA EL FORK, PERO UN POCO DE BELLEZA
MATEMÁTICA NUNCA ESTÁ DEMÁS (?,
DESPUES DE TODO UN COMPUTADOR ES UNA CALCULADORA
*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

void collatz(int n)
{
    printf("%d, ", n);
    if(n == 1) {
        printf("\nPROCESO HIJO TERMINÓ SU TRABAJO, SECUENCIA TERMINADA\n"); 
        return;
        }
    return (n & 1) ? collatz(((n << 1) | 1) + n) : collatz(n >> 1);
}
int main()
{
    printf("PROCESO PADRE CREARÁ UN HIJO PARA QUE EJECUTE LA SECUENCIA DE COLLATZ\n");
    pid_t pid = fork();
    if (pid < 0) printf("ERROR\n");
    else if(pid == 0) {
        printf("PROCESO HIJO EJECUTRÁ SECUENCIA DE COLLATZ PARA N = 787\n");
        collatz(787);
        } else{ 
        wait(NULL); 
        printf("PROCESO PADRE TERMINÓ SU TRABAJO\n");
    }
    return 0;
}