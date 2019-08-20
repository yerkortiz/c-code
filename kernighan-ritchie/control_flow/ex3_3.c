#include <stdio.h>
#include <ctype.h>
void expand_alpha(char str[]){
    int i, c, lo, hi;
    for(i = 0, c = 0; str[i] != '\0'; ++i){
        if(isalpha(str[i]) && c == 0 && str[i + 1] == '-'){
            lo = str[i];
            ++c;
        } else if(isalpha(str[i]) && c == 1 && str[i - 1] == '-'){
            hi = str[i];
            c = 0;
            char j;
            for(j = lo; j <= hi; ++j)
                putchar(j);
        }
    }
}
int main(){
    char str[] = "a-z";
    expand_alpha(str);
    return 0;
}