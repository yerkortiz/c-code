#include <stdio.h>
void swap(int *px, int *py) /* interchange *px and *py */
{
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}
int main(){
    int x = 1, y = 2, z[10];
    int *ip; /* pointer */
    ip = &x; /* ip points to x */
    y = *ip; /* y = 1 */
    *ip = 0; /* x = 0 */
    ip = &z[0]; /* ip points to z[0] */
    *ip += 10; /* z[10] = 10 */
    printf("%d\n", z[0]);
    ++ip; /* ip points to z[1] */
    *ip += 20;
    printf("%d\n", z[0] + z[1]);
    y = *ip;
    printf("%d\n", y);
    return 0;
}