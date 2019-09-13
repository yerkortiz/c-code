#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    printf("MODO NORMAL\n");
    int fd = atoi(argv[1]);     
    char str[] = "TOMO NOTA\n";
    printf("USAR SYSCALL WRITE\n\n");
    write(fd, str, strlen(str));
    return 0;
}
 