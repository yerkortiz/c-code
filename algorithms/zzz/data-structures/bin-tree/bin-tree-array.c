/* 
* AUTHOR: YERKO ORTIZ
*/
#include <stdio.h>
#include <string.h>
#define MAX_SIZE ((1 << 4) | 1)
#define NOT !
#define RIGHT(i) (i << 1)
#define LEFT(i) ((i << 1) | 1)
int tree[MAX_SIZE];
void insert(int n)
{
    //printf("INSERTANDO %d\n", n);
    for(int i = 1; i < MAX_SIZE; i = (tree[i] < n)? (LEFT(i)):(RIGHT(i))){
        if(NOT tree[i]) {
            tree[i] = n;
            //printf("ELEMENTO INSERTADO EN INDICE %d\n", i);
            return; // INSERTED
        } 
    }
    return; // NOT INSERTED
}
void printTree(void)
{
    for(int i = 1; i < MAX_SIZE; ++i)
        if(tree[i]) printf("%d ", tree[i]);
}
int logTwo(int n) // FLOOR POWER OF TWO
{
    return (n >> 1) ? logTwo(n >> 1) + 1 : 0;
}
void fillString(char *s, char value, int size)
{
    for(int i = 0; i < size - 1; ++i){
        *(s + i) = value;
        *(s + i + 1) = '\0';
    }
}
void asciiTree(void)
{
    int height = logTwo(MAX_SIZE);
    int x_size = (MAX_SIZE << 1) | 1;
    char x[x_size];
    fillString(x, '_', x_size);
    for(int i = 0, count = 1; i < height; ++i) {
        for(int j = 1; j <= (1 << i); ++j, ++count) {
            printf("%s", x);
            printf("%d", tree[count]);
        }
        x_size >>= 1;
        x[x_size + 1] = '\0';
        printf("\n");
    }
       /*
    for(int i = 0, j = 0; i < height; ++i, j ^= 1) {
        if(NOT j) {
            x[(x_size >> 1) - i] = 'a';
            x[(x_size >> 1) + i] = 'a';
            printf("%s\n", x);
            x[(x_size >> 1) - i] = '_';
            x[(x_size >> 1) + i] = '_';
            continue;
        }
        x[(x_size >> 1) - i] = '/';
        x[(x_size >> 1) + i] = '\\';
        printf("%s\n", x);
        x[(x_size >> 1) - i] = '_';
        x[(x_size >> 1) + i] = '_';
    }
    */
}
void asciiPrint(int delta, int height, int pos)
{
    if(height <= 0) return;
    int x_size = (MAX_SIZE << 1) | 1;
    char x[x_size];
    fillString(x, '_', x_size); // lo mejor es tenerlo en referencia
    x[(pos) - delta] = '/';
    x[(pos) + delta] = '\\';
    printf("%s\n", x);
    x[(pos) - delta] = '_';
    x[(pos) + delta] = '_';
    ++delta;
    x[(pos) - delta] = 'a';
    x[(pos) + delta] = 'a';
    ++delta;
    printf("%s\n", x);
    //asciiPrint(delta, height - 1, pos + delta);
    //asciiPrint(delta, height - 1, pos - delta);
}
int main()
{   /*
    int arr[] = {10, 6, 12, 7, 4, 11, 13};
    for(int i = 0; i < 7; ++i)
        insert(arr[i]);
    //printTree();
    asciiTree();
    */
    int x_size = (MAX_SIZE << 1) | 1;
    char x[x_size];
    fillString(x, '_', x_size);
    x[(x_size >> 1)] = 'a';
    printf("%s\n", x);
    asciiPrint(1, 2, x_size >> 1);
    return 0;
}