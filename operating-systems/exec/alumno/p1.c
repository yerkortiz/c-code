#define _POSIX_SOURCE
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
unsigned long long rdtsc(){ 
/* 
* este trucazo sirve para crear números random, ya que
* el numero de ciclos del proce varía, al usarlo de semilla
* los numeros resultantes serán mas variados.
* asm permite escribir en asembly jeje
*/
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}
int main()
{
    printf("PROCESO ALUMNO (PID %d) INICIADO\n\n", getpid());
    int fd = open("nota.txt", O_CREAT|O_WRONLY|O_APPEND, 0777);
    int open_file = TRUE;
    for(int i = 0; i < 20; ++i) {
        srand(rdtsc());
        int dice = rand() % 3;
        if(dice == 0) {
            int pid = fork();
            if(pid < 0) {
                perror("ERROR\n");
                exit(1);//exit(1) da aviso que hubo un error, 0 que fue exitoso
            } else if(pid == 0) {
                system("gcc -o normal.out normal.c");
                dup2(fd, 0);
                if(!open_file) fd = open("nota.txt", O_CREAT|O_WRONLY|O_APPEND, 0777);
                open_file = TRUE;
                execl("normal.out", NULL);
            } else {
                printf("ALUMNO ENTRANDO A MODO NORMAL\n");
                wait(NULL);
            }
        } else if(dice == 1) {
            int pid = fork();
            if(pid < 0) {
                perror("ERROR\n");
                exit(1);//exit(1) da aviso que hubo un error, 0 que fue exitoso
            } else if(pid == 0) {
                system("gcc -o paro.out paro.c");
                dup2(fd, 0);
                open_file = FALSE;
                execl("paro.out", NULL);
            } else {
                printf("ALUMNO ENTRANDO A MODO PARO\n");
                wait(NULL);
            }
        } else {
            int pid = fork();
            if(pid < 0) {
                perror("ERROR\n");
                exit(1);//exit(1) da aviso que hubo un error, 0 que fue exitoso
            } else if(pid == 0) {
                system("gcc -o toma.out toma.c");
                execl("toma.out", NULL);
                //printf("MODO TOMA\n");
                //printf("TERMINANDO PROGRAMA\n");
                //return 0;
            } else {
                wait(NULL);
                printf("PROGRAMA FINALIZADO\n");
                break;
            }
        }
    }    
    return 0;
}