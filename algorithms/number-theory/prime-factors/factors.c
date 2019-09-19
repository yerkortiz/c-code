/*
* FACTORS OF A NUMBER
*/
#include <stdio.h>
#define MAX_SIZE (1 << 8)
int factors[MAX_SIZE];
int *end = factors;
void printFactors(void)
{
    for(int *it = factors; it < end; ++it) 
        printf("%d ", *it);
}
void factor(int n)
{
    for(int x = 2; x * x <= n; ++x)
        for(; n % x == 0; n /= x){
            *(end++) = x;
        }
    if(n > 1) 
        *(end++) = n;
    printFactors();
}
int main()
{
    factor(20);
    return 0;
}