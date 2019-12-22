#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int i, n;
    fork();
    execl("./asdas", NULL);
    return 0;
}