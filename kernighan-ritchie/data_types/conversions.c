#include <stdio.h>
#include <ctype.h>

#define EDL putchar('\n');
#define pint(d) printf("%d\n", d);
#define sandwich(a,b,c) (a >= b && b >= c)
#define MAX_STR (int) 1e5

int aatoi(char s[]){
    int i, n;
    for (i = 0; isdigit(s[i]); ++i){
        n = 10 * n + (s[i] - '0');
    }
    return n;
} char lower(char c) {
    if (sandwich('Z', c, 'A'))
        return c + 'a' - 'A';
    else 
        return c;
} int htoi(char s[]){
    int n = 0, size =0, p16 = 1;
    for (; s[size + 1] != '\0'; ++size);
    for (; size >= 0 ; --size){
        if(isdigit(s[size]))
            n += p16 * (s[size] - '0');
        else
            n += p16 * (s[size] - 'A' + 10);
        p16 <<= 4;
    }   
    return n;
} void squeeze(char str[], char c){
    int i, j;
    for(i = j = 0; str[i] != '\0'; ++i){
        if (str[i] != c)
            str[j++] = str[i];
        str[j] = '\0';
    }
} void squeeze_str(char str1[], char str2[]){
    int i;
    for(i = 0; str1[i] != '\0'; ++i)
        squeeze(str2, str1[i]);
} /* bit-field de largo n, que empieza en posicion p.
*/ unsigned getbits(unsigned x, int p, int n){
return (x >> (p+1-n)) & ~(~0 << n);
} char lower1(char c){
    return sandwich('Z', c, 'A')? c + 'a' - 'A' : 'c';
}
int main(){
    putchar(lower1('Z'));
    return 0;
}