/*
* ARBOL DE N HIJOS
*/
#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h>
int main() 
{ 
    int N; N = 5;
    for(int i = 0; i < N; i++) { 
        int pid = fork();
        if(pid < 0){
            printf("ERROR");
            EXIT_FAILURE;
        }
        else if(pid == 0) {
            printf(" HIJO (pid %d) DEL PADRE (pid %d)\n", getpid(), getppid()); 
            exit(0); 
        } else {
            //parent
            wait(NULL);
        }
    }
    return 0;
} 