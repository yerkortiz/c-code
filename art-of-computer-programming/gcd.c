#include <stdio.h>
#define SWAP(a, b, type) {type temp = a; a = b; b = temp;}
int gcd(int m, int n)
{
    int r = m % n;
    return (m < n) ? gcd(n, m) : (r == 0) ? n : gcd(n, r);
}
int main(void)
{
    printf("%d\n", gcd(4, 2));
    return 0;
}