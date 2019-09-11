#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define OR ||
int main(int argc, char *argv[])
{
    char line[16];
    memset(line,'-',6);
    while(1) {
    int answer;
    printf("ESCOJA UNA OPCIÓN(presione el número):\n");
    printf("1] Escribir una oración en un archivo llamado letter.txt\n");
    printf("2] Imprimir el contenido del archivo letter.txt\n");
    printf("3] Presione cualquier otra tecla para finalizar este programa\n");
    scanf("%d", &answer);
    if(answer == 1){
        int pid = fork();
        if(pid < 0) {
            perror("FORK ERROR\n");
            exit(1);
        } else if(pid == 0) {
            system("gcc -o a.out wrt.c");
            execl("a.out", "a.out", NULL);
        } else {
            wait(NULL);
            printf("%s\n", line);
        }
    } else if(answer == 2){
        int pid = fork();
        if(pid < 0) {
            perror("FORK ERROR\n");
            exit(1);
        } else if(pid == 0) {
            printf("IMPRIMIENDO CONTENIDOS DE letter.txt:\n");
            char *myargs[3];
            myargs[0] = strdup("cat"); 
            myargs[1] = strdup("letter.txt"); 
            myargs[2] = NULL; 
            execvp(myargs[0], myargs);
        } else {
            wait(NULL);
            printf("%s\n", line);
        }
    } else {
        break;
        } 
    }
    return 0;
}