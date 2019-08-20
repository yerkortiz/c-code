#include <stdio.h>
#include <string.h>

#define MAX_STR 100
#define sandwich(a,b,c) (a <= b && b <= c)

void reverse(char str[]);
void itob(char str[], unsigned n, int base);

int main() {
    int primes[] = {1, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    for(int i = 0; i < 15; ++i){
        char str[MAX_STR];
        itob(str, primes[i], 2);
    }
    return 0;
}
void reverse(char str[]){
    int i, j;
    for(i = strlen(str) - 1, j = 0; i > j; ++j, --i){
        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;
    }
}
void itob(char str[], unsigned n, int base){
    int i = 0;
    do{
        int k = n % base;
        //printf("%d\n", k);
        if(sandwich(0, k, 9)) { 
            str[i++] = k + '0';
        }else {
            str[i++] = 'A' + k - 10;
        }
    } while((n /= base) > 0);
    str[i++] = '\0';
    //printf("%s\n", str);
    reverse(str);
    printf("%s\n", str);
}