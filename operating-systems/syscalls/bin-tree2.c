/*
 * OTRO EJEMPLO DE PROCESS TREE
 * SI SE MODIFICA UN POCO SE PUEDE HACER
 * PARA N NODOS EN LUGAR DE LLENAR EL ARBOL
 * EN COMPLETITUD.
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define WAIT_TREE for(; wait(NULL) > 0; )
#define NOT !
#define OR ||
#define EXIT_PROGRAM return 0

void processTree(int height)
{
    pid_t new_pid[3];
    int status[3];
    if(height > 0) {
        if (!(new_pid[0] = fork())) {
            printf("OWN ID %d | PARENT ID %d\n", getpid(), getppid());
            //processTree((height - 1) >> 1)
            processTree((height - 1));
        } else {
            for(int i = 1; i < 3; ++i) {
                if(new_pid[i - 1] > 0) {
                    if (height > 0) {
                    // if(height > 1)
                        if(!(new_pid[i] = fork())) {
                            printf("OWN ID %d | PARENT ID %d\n", getpid(), getppid());
                            processTree((height - 1));
                            //processTree((height - 2) >> 1)
                        } else if(new_pid[i] > 0) {
                            waitpid(new_pid[i], &status[i], 0);
                        }
                    }

                }
            }
            waitpid(new_pid[0], &status[0], 0);
        }
    }
}
int main(void)
{
    printf("start %d\n", getpid());
    processTree(2);
    EXIT_PROGRAM;
}