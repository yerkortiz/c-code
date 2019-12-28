#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXIT_PROGRAM return 0
#define MAIN_PROGRAM main

uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}
int randInt(int a, int b)
{
    srand(rdtsc());
    return a + (rand() % b);
}

int MAIN_PROGRAM(int argc, char **argv)
{
    /* command line input: matrix dimensions */
    int i, j, n = atoi(argv[1]), m = atoi(argv[2]), a = atoi(argv[3]), b = atoi(argv[4]);
    for(i = 0; i < n; ++i)
        for(j = 0; j < m; ++j)
            printf("%d%c", randInt(a, b), (j == m - 1)? '\n':' ');
    EXIT_PROGRAM;
}