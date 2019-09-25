/*
 * BINARY PROCESS TREE
 * AUTHOR: YERKO ORTIZ
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define WAIT_TREE for(; wait(NULL) > 0; )
#define NOT !
#define OR ||
#define MAX_HEIGHT 3
#define EXIT_PROGRAM return 0

void processTree(int current_height)
{
    if (current_height > MAX_HEIGHT)
        return;
    if (NOT fork() OR NOT fork())
       processTree(current_height + 1);
    else {
        printf("OWN PID: %d | PARENT PID: %d\n", getpid(), getppid());
        WAIT_TREE;
    }
}
int main(void)
{
    printf("ROOT PID %d\n", getpid());
    processTree(0);
    EXIT_PROGRAM;
}
