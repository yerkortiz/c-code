#include <stdio.h>

void itoa(int n, char str[]){
    int i = 0; 
    do {
        str[i++] = n % 10 + '0';
    } while((n /= 10) > 0);
    str[i] = '\0';
    printf("%s\n", str);
}

int main(){
    char str[10000];
    itoa(20000, str);
    return 0;
}