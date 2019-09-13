#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    printf("PROCESO ALUMNO (PID %d) INICIADO\n", getpid());
    int fd = open("nota.txt", O_CREAT|O_WRONLY|O_APPEND, 0777);
    int pid = fork();
    if(pid == 0) {
        system("gcc -o normal.out normal.c");
        dup2(fd, 0);
        execl("p2.out", NULL);
    } else {
        printf("ALUMNO DECIDIRÁ ALGO\n");
        printf("CHAO LOH VIMOH\n");
    }
    wait(NULL);
    close(fd);
}