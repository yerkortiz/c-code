/*
*CHECK IF A NUMBER IS PRIME
*/
#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define EXIT_PROGRAM return 0
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define LOOP(start, end) for(start = 0; start < end; ++start)
int primeCheck(int n)
{
    if(n < 2) return FALSE;
    for(int k = 2; k * k <= n; ++k)
        if(n % k == 0) return FALSE;
    return TRUE;
}
int main()
{
    int i = 0;
    int test[] = {1, 2, 3, 4, 5, 7, 12, 15, 51, 91, 92};
    LOOP(i, ARRAY_SIZE(test)) {
        printf("THE NUMBER %d IS PRIME?: ", test[i]);
        printf("%s\n", (primeCheck(test[i])? "TRUE" : "FALSE"));
    }
    EXIT_PROGRAM;
}