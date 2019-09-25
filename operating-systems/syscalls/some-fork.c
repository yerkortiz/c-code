/*
 * SOME FORK EXAMPLES
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <errno.h>
#define WAIT_TREE  for(; wait(NULL) > 0; ) 
void processInfo(void)
{
    printf("Parent PID: %d Own PID: %d\n", getppid(), getpid());
}
int main()
{
    printf("PROGRAMA INICIALIZADO\n");
    /* N forks */
    /*
    fork();
    fork();
    fork();
    processInfo();
    WAIT_TREE;
    */
    /* if(not fork or not fork) */
    /*
    processInfo();
    if(!fork() || !fork()) {
        processInfo();
    }
    WAIT_TREE;
    */
    /* 2 hijos */
    /*
    fork() && fork();
    processInfo();
    WAIT_TREE;
    */
    /* lista */
    /*
    fork() || fork();
    processInfo();
    WAIT_TREE;
    */
    printf("PROGRAMA TERMINADO\n");
    return 0;
}