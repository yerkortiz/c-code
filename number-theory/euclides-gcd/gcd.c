#include <stdio.h>
#define SWAP(a, b, type) do {type temp = a; a = b; b = temp;} while(0);
#define WEAITA printf("_________weaita_______\n")
int gcd(int a, int b)
{
    if(a < b) SWAP(a, b, int);
    printf("A = %d, B = %d, A mod B = %d, A / B = %d\n", a, b, a % b, a / b);
    return (a % b == 0) ? b : gcd(a, a % b);
}
int main()
{
    WEAITA;
    gcd(12075, 4655);
    WEAITA;
    gcd(1071, 462);
    WEAITA;
    gcd(1001, 367);
    WEAITA;
    gcd(4854, 3788);
    WEAITA;
    gcd(24140, 16762);
    WEAITA;
    gcd(28733, 1283);
    WEAITA;
    gcd(12802, 7806);

    return 0;
}