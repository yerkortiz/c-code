#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("L0\n");
	printf("pid %d ppid %d\n", getpid(), getppid());
 	fork();
	printf("pid %d ppid %d\n", getpid(), getppid());
 	printf("L1\n");
 	fork();
	printf("pid %d ppid %d\n", getpid(), getppid());
 	printf("Bye\n");
	wait(NULL);
	return 0;
}
