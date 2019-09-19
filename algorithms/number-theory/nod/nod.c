/*
*NUMBER OF DIVISORS
*/
#include <stdio.h>
#include <math.h>
#define printd(n) printf("%d\n", n)
/*
*O(n^1/2) solution
*/
int nod(int n)
{
    int cnt, i;
    for(cnt = 0, i = 1; i <= sqrt(n); ++i) 
        if(n % i == 0) cnt += (n / i == i) ? 1 : 2;
    return cnt;
}
int main()
{   
    printd(nod(8));
    printd(nod(9));
    return 0;
}
