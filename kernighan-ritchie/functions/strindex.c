#include <stdio.h>
int strindex(char str_source[], char str_check[]){
    int i, j, k, rightmost_index = 0, max = 0, index = -1;
    for(i = 0; str_source[i] != '\0'; ++i){
        for(j = i, k = 0; str_source[j] == str_check[k] \
        && str_check[k] != '\0'; ++j, ++k){
            ++rightmost_index;
            if(rightmost_index > max){
                max = rightmost_index;
                index = j;
            }
        } 
        if(str_check[k] == '\0')
            return index;
        rightmost_index = 0;
    }
    return index;
}
int main(){
    return 0;
}