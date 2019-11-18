#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void)
{
    int i;
    for(i = 0; i < 3; ++i){
        printf("Hola %d\n", i);
        fork();
        wait(NULL);
    }
    return 0;
}