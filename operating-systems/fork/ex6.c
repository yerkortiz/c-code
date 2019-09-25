/*
* fork or fork
* mostrar que sucede sin los fork
*/
#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h>
#define OR ||
int main() 
{ 
    if (fork() OR fork()) 
        fork(); 
        wait(NULL);
    printf("1 "); 
    wait(NULL);
    return 0; 
} 