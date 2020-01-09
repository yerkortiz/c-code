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
void sA(double t, double t_min, double alpha, int n, double *x, double y)
{
    int i, j, k;
    for(i = 0; i < n; ++i) x[i] = rndF(-100, 100);
    y = objF(x, n);
    double *x_ = malloc(n * sizeof(double));
    double y_, ap;
    while(t > t_min) {
        for(int i = 0; i < n; ++i)
            printf("%d%c", (x[i] < 0)? 1:0, (i == n - 1)? '\n':' ');
        for(i = 0; i < 100; ++i) {
            for(j = 0; j < n; ++j) x_[j] = rndF((x[i] - 100)*t/(j + 1), (x[i] + 100)*t/(j + 1));
            ap = exp((objF(x, n) - objF(x_, n))/t); 
            if(ap < rndF(0, 1)) continue;
            y_ = objF(x_, n);
            if(y_ < y) {
                for(j = 0; j < n; ++j) x[j] = x_[j];
                y = y_;
                break;
            }                
        }
        t *= alpha;
    }
}
int main(int argc, char **argv)
{
    /* max_it = 20 max_left = -100 max_right = 100 */
    double t = atof(argv[1]), t_min = atof(argv[2]), alpha = atof(argv[3]);
    int n = 3;
    double *x = malloc(n * sizeof(double));
    double y;
    sA(t, t_min, alpha, n, x, y);
    free(x);
    return 0;
}