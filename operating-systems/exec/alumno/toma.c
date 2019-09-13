#define _POSIX_SOURCE
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    printf("MODO TOMA\n");
    printf("USAR SYSCALL KILL PARA MATAR PADRE\n");
    //kill(getppid(), SIGKILL);// no es necesario xD
    printf("TERMINANDO PROGRAMA\n\n");
    return 0;
}