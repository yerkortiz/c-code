/* JEROGLIFICO 6 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("SOY EL PROCESO MAIN (pid:%d)\n", (int) getpid());
    int child = fork();
    if (child < 0) { 
        printf("ERROR\n");
        exit(1);
    } else if (child == 0) { 
        printf("HOLI, SOY UN PROCESO HIJO (PID:%d)\n", (int) getpid());
        char *myargs[3];
        myargs[0] = strdup("cat"); 
        myargs[1] = strdup("ls_fork.c"); 
        myargs[2] = NULL; 
        execvp(myargs[0], myargs); 
        printf("HICE CAT DEL ARCHIVO ls_fork.c\n");
    } else { 
        wait(NULL);
        printf("CHAO LOH VIMOH\n");
    }
    return 0;
}