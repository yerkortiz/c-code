/*
* Ejemplo 3
* getpid, getppid
*/
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
int main() 
{ 
    fork();
    wait(NULL);
    fork();
    wait(NULL);
    printf("HOLI, Hijo (pid %d) del Padre (pid %d)\n", getpid(), getppid());
    return 0; 
} 