#include <stdio.h>
#include <string.h>

void ritoa(int number, char str[])
{
    static int index = 0;
    if(number / 10)
        ritoa(number / 10, str);
    else
        index = 0;
    str[index++] = number % 10 + '0';
    str[index] = '\0';
}
void reverse(char str[], int j)
{
    static int i = 0;
    if(i >= j) return;
    char temp = str[i];
    str[i++] = str[j];
    str[j--] = temp;
    reverse(str, j);
}
int main()
{
    char str[10];
    ritoa(11112222, str);
    printf("%s\n", str);
    reverse(str, strlen(str) - 1);
    printf("%s\n", str);
    return 0;
}
