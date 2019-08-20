#include <stdio.h>
void mystrcat(char *s,char *t)
{
    while(*s != '\0') s++;
    s--; 
    while((*s=*t)!='\0') {   
        s++;
        t++;
    }
}
int main(){
    return 0;
}