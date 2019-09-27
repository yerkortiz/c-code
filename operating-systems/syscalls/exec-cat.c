/*
 * USO DE EXEC PARA USAR COMANDOS DE LA SHELL
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
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
        myargs[1] = strdup("bin-tree1.c"); 
        myargs[2] = NULL; 
        execvp(myargs[0], myargs); 
        printf("HICE CAT DEL ARCHIVO bin-tree1.c\n");
    } else { 
        wait(NULL);
        printf("CHAO LOH VIMOH\n");
    }
    return 0;
}