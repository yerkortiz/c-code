/*
 * AUTHOR YERKO ORTIZ
*/
#include <stdio.h>
#include <stdlib.h>

#define EXIT_PROGRAM return 0
int main(int argc, char **argv)
{
    if(!argc) return 0;
    int v = strtol(argv[1]); 
    int **adjList = (int *)malloc(v * sizeof(int *));
    return 0;
}