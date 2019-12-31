#include<stdio.h> 
#include <stdlib.h>
void multiply(int m1, int m2, int *mat1, int n1, int n2, int *mat2, int *res) 
{ 
	int x, i, j; 
	//int *res = (int *) malloc(m1 * n2 * sizeof(int)); 
	for (i = 0; i < m1; i++) { 
		for (j = 0; j < n2; j++) { 
			res[i * m1 + j] = 0; 
			for (x = 0; x < m2; x++) { 
				res[i * m1 + j] += mat1[i * m1 + x] * mat2[x * m2 + j]; 
			} 
		} 
	} 
} 

int main(void) 
{ 
    int m1 = 2, m2 = 2, n1 = 2, n2 = 2;
    int *res = (int *) malloc(m1 * n2 * sizeof(int));
	return 0; 
} 
