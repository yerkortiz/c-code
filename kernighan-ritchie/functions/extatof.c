#include <stdio.h>
#include <ctype.h>

double atof(char str[]);

int main(){
    printf("%lf", 1e-1);
    return 0;
}
double atof(char s[]){
    double val, pow;
    int i, sign;
    int power(int base,int exp); 
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (pow = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        pow *= 10;
    }
    if(s[i] == 'e') ++i;
    int psign = (s[i] == '-')? -1 : 1;
    int exp;
    for(exp=0; isdigit(s[i]);i++)
        exp=10.0 * exp + (s[i] - '0');

    if(psign == '-')
        return sign * (val / pow) / power(10,exp);
    else
        return sign * (val / pow) * power(10,exp);
}
int power(int base,int exp){
    int power;
    power=1;
    while(exp-- > 0)
        power *=base;

    return power;
}