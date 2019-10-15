#include <stdio.h>
#include <unistd.h>
int c;
int main(void)
{
    if(fork() == fork())
		++c;
	else
		--c;
    printf("%d \n", c);
	wait(NULL);
    return 0;
}