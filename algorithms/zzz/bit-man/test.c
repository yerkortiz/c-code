#include <stdio.h>
/* count the number of 1's in a bit sequence*/
/* linear approach O(n)*/
int countBitSet(int n) 
{
    return (n == 0)? 0 : (n & 1) + countBitSet(n >> 1);
}
/* kernighan approach, still linear but it's number of cycles
is equal to the number of set bits in a given integer. O(n)*/
unsigned int countBitSet1(int n)
{
    return (n == 0)? 0 : 1 + countBitSet1(n & (n -1));
}
/* function from gcc compiler, it takes O(n) but the constant is really small*/
unsigned int lookUpBitSet(int n)
{
    return __builtin_popcount(n);
}
void bin(unsigned int n)
{
    if(n > 1)
        bin(n >> 1);
    printf("%d ", n & 1);
}
int main()
{
    bin(83712);
    return 0;
}
