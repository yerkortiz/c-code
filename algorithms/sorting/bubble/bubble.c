#include <stdio.h>
#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)
#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))
void bubbleSort(int *pa, int size)
{
    for(int i = 0; i < size; ++i)
        for(int j = i; j < size; ++j)
            if(*(pa + i) > *(pa +j))
                SWAP(*(pa + i), *(pa + j), int);
        
}
void print_array(int *pa, int *end)
{
    for(; pa != end; ++pa)
        printf("%d%c", *pa, (pa == end - 1)? '\n': ' ');
}
int main()
{
    int array[10] = {2, 7, 1, 9, 8, 5, 3, 10, 4, 6};
    int array_size = ARRAY_SIZE(array);
    int *pa = array;
    int *end = array + array_size;
    print_array(pa, end);
    bubbleSort(pa, array_size);
    print_array(pa, end);
    return 0;
}