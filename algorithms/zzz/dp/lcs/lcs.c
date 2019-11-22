#include<stdio.h>
#include<string.h>
#define EXIT_PROGRAM return 0
#define OR ||
#define MAX_SEQUENCE (1 << 5)
int i, j, m, n, 
    c[MAX_SEQUENCE][MAX_SEQUENCE];
char x[MAX_SEQUENCE], y[MAX_SEQUENCE],
    b[MAX_SEQUENCE][MAX_SEQUENCE];
void print(int i,int j)
{
    if(i==0 || j==0)
        return;
    if(b[i][j]=='c') {
        print(i-1,j-1);
        printf("%c",x[i-1]);
    } else if(b[i][j]=='u')
        print(i-1,j);
    else
        print(i,j-1);
}
void lcs()
{
    m = strlen(x);
    n = strlen(y);
    for(i=0;i<=m;i++)
        c[i][0]=0;
    for(i=0;i<=n;i++)
        c[0][i]=0;
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++) {
            if(x[i-1]==y[j-1]) {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]='c';
            } else if(c[i-1][j]>=c[i][j-1]) {
                c[i][j]=c[i-1][j];
                b[i][j]='u';
            } else {
                c[i][j]=c[i][j-1];
                b[i][j]='l';
            }
        }
}
int main()
{
    printf("INGRESE PRIMERA SECUENCIA: ");
    scanf("%s",x);
    printf("INGRESE SEGUNDA SECUENCIA: ");
    scanf("%s",y);
    printf("LCS(X, Y) = ");
    lcs();
    print(m,n);
    putchar('\n');
    return 0;
}
