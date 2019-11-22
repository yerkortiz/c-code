/*
 * SUFFIX ARRAY
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define EXIT return 0
#define MAIN int main
#define MAX_SIZE (1 << 10)
int suffixArr[MAX_SIZE]; 
struct suffix 
{ 
    int index; 
    char *suff; 
}; 
int ComparFuncStructName(const void *x, const void *y){
    const struct suffix* pa = (const struct suffix*) x;
    const struct suffix* pb = (const struct suffix*) y;
    return strcmp(pa -> suff, pb -> suff);
}
void buildSuffixArray(char *txt, int n) 
{ 
    struct suffix suffixes[n]; 
    for (int i = 0; i < n; i++) 
    { 
        suffixes[i].index = i; 
        suffixes[i].suff = (txt+i); 
    } 
    int stringLen = sizeof(suffixes) / sizeof(suffixes[0]);
    qsort(suffixes, stringLen, sizeof(suffixes[0]), ComparFuncStructName);
    for (int i = 0; i < n; i++) 
        suffixArr[i] = suffixes[i].index; 
    for (int l = 0; l < n; printf("%s ", suffixes[l].suff), l++);
    return;
} 
MAIN(void)
{
    char *s; scanf("%s", s);
    buildSuffixArray(s, strlen(s));
    EXIT;
}