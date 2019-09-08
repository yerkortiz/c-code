/* JEROGLIFICO 2 */
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0) { 
        printf("ERROR\n");
        return 1;
    }
    else if (pid == 0)  
        execlp("/bin/ls", "ls", NULL);
    else { 
        wait(NULL);
        printf("LS DEL DIRECTORIO ACTUAL\n");
    }
    return 0;
}