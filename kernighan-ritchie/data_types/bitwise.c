#include <stdio.h>

#define pint(d) printf("%u\n", d);

unsigned rmbits(unsigned x, unsigned n){
    return (x & ~(~0 << n));//rightmost (n)
} unsigned getbits(unsigned x, int p, int n){
    return rmbits(x >> (p + 1 - n), n);//bits (p,n)
} unsigned sobits(unsigned x, int p, int n){
    return (x & ~(~(~0 << n) << (p + 1 - n)));//setoff (p,n)
} void ubin(unsigned n){
    if (n > 1){
        ubin(n >> 1);
    } printf("%u ", n & 1);
} unsigned setbits(unsigned x, int p, int n, unsigned y){
    return sobits(x, p, n) | rmbits(y, n); 
} unsigned sbits(int p, int n){//shift n bits to p
    return ~(~0 << n) << (p + 1 - n);
} unsigned ibits(unsigned x, int p, int n){
    return x ^ sbits(p, n); // invert (p, n)
} unsigned rrbits(unsigned x, int n){
    return (x >> n) | (x << (8 * sizeof(x) - n));
} unsigned bitcount(unsigned x){
    int b;
    for(b = 0; x != 0; x >>= 1)
        if(x & 01) ++b;
    return b;
} unsigned bitcount1(unsigned x){ //usa propiedad de complemento a 2.
    int b; //esto funciona para int tambien.
    for(b = 0; x != 0; x &= (x - 1))
        ++b;
    return b;
}   
int main(){
    // ~(~0 << n) = (1 << n) - 1 = 2 ^ n - 1
    // (~(~0 << n) << (p + 1 - n)) = 2 ^ (p + 1) - 1 - 2 ^ n - 1
    /* << mueves los bits n espacios a la izquierda
    es equivalente a multiplicar por 2 ^ n */
    //pint (1 << 1);
    //pint (1 << 2);
    //pint (1 << 3);
    /* >> mueves los bits n espacios a la derecha
    es equivalente a dividir por 2 ^ n */
    //pint (2 >> 1);
    //pint (4 >> 2);
    //pint (12 >> 1);
    //pint (12 >> 2);
    /* & dejar prendidos n bits de derecha
    a izquierda*/
    //pint(7 & ((1 << 0) - 1));
    //pint(7 & ((1 << 1) - 1));
    //pint(7 & ((1 << 2) - 1));
    //pint(7 & ((1 << 3) - 1));
    /* | prender n bits de derecha a izquierda*/
    //pint(0 | ((1 << 0) - 1));
    //pint(0 | ((1 << 1) - 1));
    //pint(0 | ((1 << 2) - 1));
    //pint(0 | ((1 << 3) - 1));
    /* */
    //pint(setbits(140, 3, 2, 1));
    //pint(ibits(140, 3, 3));
    //pint(rrbits(12, 2));
    return 0;
}