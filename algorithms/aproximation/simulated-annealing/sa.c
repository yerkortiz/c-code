/*
 * Author: Yerko Ortiz
 * Input: initial temperature, minimun temperature, decrease temperature
 * Output:
*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "rnd_.h"

double objF(double *x, int n)
{
    double value = 0;
    for(int i = 0; i < n; ++i)
        value += (x[i]*x[i]*x[i]);
    return value;
}
double acceptP(double *c, double *x, int n) 
{ 
    return exp(objF(c, n) - objF(x, n)); 
}
int main(void)
{
    double t, t_min, alpha;
    int n, max_it;
    double *x = malloc(n * sizeof(double));
    for(int i = 0; i < n; ++i) x[i] = rndF(0.0, 1.0);
    double y = objF(x, n);
    free(x); free(y);
    return 0;
}