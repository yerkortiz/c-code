#include <stdio.h>
#define sandwich(a, b, c) (a >= b && b >= c)
void itob(unsigned n, char str[], int base){
    int i = 0;
    while(n > 0){
        int k = n % base;
        if(sandwich(9, k, 0)){
            str[i++] = k + '0';
        }
        else
            str[i++] = 'A' + k - 10;
        n /= base;
    }
    str[i] = '\0';
    printf("%s\n", str);
}
int main(){
    char str[1000];
    itob(12, str, 16);
}