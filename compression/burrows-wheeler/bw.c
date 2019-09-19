#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
  
struct rotation { 
    int index; 
    char* suffix; 
}; 
  
int cmpfunc(const void* x, const void* y) 
{ 
    struct rotation* rx = (struct rotation*)x; 
    struct rotation* ry = (struct rotation*)y; 
    return strcmp(rx->suffix, ry->suffix); 
} 
  
int* computeSuffixArray(char* input_text, int len_text) 
{ 
    struct rotation suff[len_text]; 
  
    for (int i = 0; i < len_text; i++) { 
        suff[i].index = i; 
        suff[i].suffix = (input_text + i); 
    } 
  
    qsort(suff, len_text, sizeof(struct rotation), 
          cmpfunc); 
  
    int* suffix_arr 
        = (int*)malloc(len_text * sizeof(int)); 
    for (int i = 0; i < len_text; i++) 
        suffix_arr[i] = suff[i].index; 
  
    return suffix_arr; 
} 
  
char* findLastChar(char* input_text, 
                   int* suffix_arr, int n) 
{ 
    char* bwt_arr = (char*)malloc(n * sizeof(char)); 
    int i; 
    for (i = 0; i < n; i++) { 
        int j = suffix_arr[i] - 1; 
        if (j < 0) 
            j = j + n; 
  
        bwt_arr[i] = input_text[j]; 
    } 
  
    bwt_arr[i] = '\0'; 
  
    return bwt_arr; 
} 
  
int main() 
{ 
    char input_text[] = "banana$"; 
    int len_text = strlen(input_text); 
  
    int* suffix_arr 
        = computeSuffixArray(input_text, len_text); 
  
    char* bwt_arr 
        = findLastChar(input_text, suffix_arr, len_text); 
  
    printf("Input text : %s\n", input_text); 
    printf("Burrows - Wheeler Transform : %s\n", 
           bwt_arr); 
    return 0; 
} 