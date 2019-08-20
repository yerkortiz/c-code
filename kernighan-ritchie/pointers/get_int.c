#include <stdio.h>
#include <ctype.h>

#define BUF_SIZE 100
#define SIZE 1000

char buf[BUF_SIZE];
int bufp = 0;

int getch(void) 
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) 
{
    if (bufp >= BUF_SIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;
    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}
int strlen(char *s)
{
    int n;
    for (n = 0; *s != '\0', s++)
        n++;
    return n;
}
int main()
{   
    int n,s,array[SIZE],getint(int *);
    for(n=0;n<SIZE && getint(&array[n]) !=EOF; n++){
       printf("storing in n = %d, getint %d\n", n, array[n]);
    }
    printf("storing in n = %d, getint %d\n", n, array[n]);
    for(s = 0; s <= n; s++)
        printf("%d, ",array[s]);

    return 0;
}