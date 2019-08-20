#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUF_SIZE 100
#define MAXOP 100 
#define NUMBER '0'
#define MAXVAL 100

typedef unsigned uint;

char buf[BUF_SIZE];
int bufp = 0;
int sp = 0; 
double val[MAXVAL];

void mgetline(char s[],int lim)
{
    int i,c;
    for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n';++i)
        s[i]=c;
    if(c=='\n')
        s[i++]=c;
    s[i]='\0';
}
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
void ungets(char s[])
{
    int i;
    i = strlen(s);
    while(i>0)
        ungetch(s[--i]);
}
/* GETOP() FETCHES THE NEXT OPERATOR OR OPERAND */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; 
    i = 0;
    if (isdigit(c)) 
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') 
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
void print_top(void){
    if(sp > 0)
        printf("%lf\n", val[sp - 1]);
    else
        printf("error: stack empty\n");
}
void swap_top(void){
    if(sp > 1){
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    }
    else 
        printf("error: stack empty or with only one element\n");
}
void clear_stack(void){
    if(sp == 0)
        printf("note: stack is already empty\n");
    else{
        memset(val, 0.0, sizeof(val));
        sp = 0; // con esto basta para limpiar el arreglo
    }       
}
void duplicate_top(void){
    if(sp < MAXVAL){
        val[sp + 1] = val[sp];
        ++sp;
    }else
        printf("error: stack full, cant duplicate the top value\n");
}
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
            push(atof(s));
            break;
            case '+':
            push(pop() + pop());
            break;
            case '*':
            push(pop() * pop());
            break;
            case '-':
            op2 = pop();
            push(pop() - op2);
            break;
            case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
            case '%':
            op2 = pop();
            if (op2 != 0.0)
                push(fmod(pop(), op2));//cambiar / a fmod
            else
                printf("error: zero divisor\n");
            break;
            case 'p':
            print_top();
            break;
            case 's':
            swap_top();
            break;
            case 'c':
            clear_stack();
            break;
            case 'd':
            duplicate_top();
            break;
            case 'e':
            printf("chao loh vimoh\n");
            //limpiar memoria?
            //goto chao;
            return 0;
            case '\n':
            printf("\t%.8g\n", pop());
            break;
            default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    //chao:
    return 0;
}

