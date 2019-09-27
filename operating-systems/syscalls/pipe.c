#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
void low_up(char *s)
{
    for(; *s != '\0'; ++s)
        if(isalpha(*s)) 
            *s = (islower(*s)) ? toupper(*s) : tolower(*s); 
}
int main() {
    printf("MI NOMBRE ES PIPEÑO (PID:%d)\n", getpid());
    int pipe1[2];
    int returnstatus, pid;
    char sl2[20] = {"HoLI Ke zaRPA"};
    char sl1[20];
    returnstatus = pipe(pipe1);
    if (returnstatus == - 1) {
        printf("ERROR\n");
        return 1;
    }
    pid = fork();
    if (pid == 0) {
        printf("MI NOMBRE ES BALTIKAPO (PID:%d)\n", getpid());
        read(pipe1[0], sl1, sizeof(sl1));
        low_up(sl1);
        printf("BALTIKAPO: %s PIPEÑO\n", sl1);
    } else { 
        printf("PIPEÑO: %s BALTIKAPO?\n", sl2);
        write(pipe1[1], sl2, sizeof(sl2));  
   }
   return 0;
}