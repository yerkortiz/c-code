#include <stdio.h>
#define SWAP(x, y, T) do { T SWAP = x; x = y; y = SWAP; } while (0)
#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))
void print_array(int *pa, int *end)
{
    for(; pa != end; ++pa)
        printf("%d%c", *pa, (pa == end - 1)? '\n': ' ');
}
void selection(int *srt, int *end)
{
    for(int *i = srt; i != end; ++i){
        int *min = i;
        for(int *j = i; j != end; ++j)
            if(*min > *j) min = j;
        SWAP(*i, *min, int);
    }
}
int main()
{
    int array[7] = {3, 7, 1, 9, 2, 6, 3};
    int *p = &array[0];
    int *end = p + ARRAY_SIZE(array);
    print_array(p, end);
    selection(p, end);
    print_array(p, end);
    return 0;
}