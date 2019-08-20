#include <stdio.h>

#define swap(a, b) { int t = a; a = b; b = t; }

int main(){
    int a = 1, b = 10;
    swap(a, b);
    printf("%d", a);
    return 0;
}