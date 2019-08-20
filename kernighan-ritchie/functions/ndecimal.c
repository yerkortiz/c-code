#include <stdio.h>
typedef unsigned uint;
void print_decimal(uint n){
    int k = n / 10;
    if(k)
        print_decimal(k);
    putchar(n % 10 + '0');
}
int main(){
    print_decimal(200);
    return 0;    
}