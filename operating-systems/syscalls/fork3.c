#include <stdio.h>
#include <unistd.h>
int c;
int main(void)
{
    printf("pid %d ppid %d\n", getpid(), getppid());
    fork() || fork();
    printf("pid %d ppid %d\n", getpid(), getppid());
    printf("%d\n", c);
    wait(NULL);
    return 0;
}