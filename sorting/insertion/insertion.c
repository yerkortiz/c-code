#include <stdio.h>
#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)
#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))
void insertion(int *p, int *end)
{   
    for(int *i = p + 1; i != end; ++i){
        int key = *i, *j = i - 1;
        for(; j != p - 1 && *j > key; *(j + 1) = *j, --j);
        *(j + 1) = key;
    }
}
void print_array(int *pa, int *end)
{
    for(; pa != end; ++pa)
        printf("%d%c", *pa, (pa == end - 1)? '\n': ' ');
}
int main()
{
    int array[7] = {3, 7, 1, 9, 2, 6, 3};
    int size = ARRAY_SIZE(array);
    int *p = &array[0];
    int *end = p + size;
    print_array(p, end);
    insertion(p, end);
    print_array(p, end);
    return 0;
}