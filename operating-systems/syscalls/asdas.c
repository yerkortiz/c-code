#include <stdio.h>
#include <unistd.h>
int main(void)
{
    int i, n;
    for(i = 0, n = 0; i < 3; ++i, ++n) {
        printf("asdas%d\n", n);
        fork(); 
    }
    return 0;
}