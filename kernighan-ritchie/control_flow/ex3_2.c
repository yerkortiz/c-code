#include <stdio.h>
#define MAX_STR 10000
void scape(char str[], char str_cpy[]){
    int index_str, index_cpy;
    for(index_str = 0; str[index_str] != '\0'; ++index_str){
        switch (str[index_str]){
            case '\n': str_cpy[index_cpy++] = '\\';
                       str_cpy[index_cpy++] = 'n';
                       break;
            case '\t': str_cpy[index_cpy++] = '\\';
                       str_cpy[index_cpy++] = 't';
                       break;
            default: str_cpy[index_cpy++] = str[index_str];
                     break;
        }
    }
}
int main(){
    return 0;    
}