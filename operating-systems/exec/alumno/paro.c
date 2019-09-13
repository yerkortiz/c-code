#define _POSIX_SOURCE
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    printf("MODO PARO\n");
    int fd = atoi(argv[1]);
    printf("USAR SYSCALL CLOSE\n\n");
    close(fd);
    return 0;
}
 