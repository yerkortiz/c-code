#include <stdio.h>
#include <stdlib.h>
void getCofactor(int *A, int *temp, int p, int q, int n) 
{ 
	int i = 0, j = 0; 

	for (int row = 0; row < n; row++) { 
		for (int col = 0; col < n; col++) { 
			if (row != p && col != q) { 
				temp[i * n + j] = A[row * n + col];
                ++j; 
				if (j == n - 1) { 
					j = 0; 
					++i;
				} 
			} 
		} 
	} 
} 
int determinant(int *A, int n, int N) 
{ 
	int D = 0;
	if (n == 1) 
		return A[0]; 
	int temp[N * n + N]; 
	int sign = 1;

	for (int f = 0; f < n; f++) { 
		getCofactor(A, temp, 0, f, n); 
		D += sign * A[0 + f] * determinant(temp, n - 1, N); 
		sign = -sign; 
	} 
	return D; 
} 
void adjoint(int *A, int *adj, int N) 
{ 
    if (N == 1) { 
        adj[0] = 1; 
        return; 
    } 
    int sign = 1;
    int *temp = (int *) malloc(N * N * sizeof(int));
    for (int i=0; i<N; i++) { 
        for (int j=0; j<N; j++) { 
            getCofactor(A, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j * N + i] = (sign)*(determinant(temp, N - 1, N)); 
        } 
    } 
} 

int inverse(int *A, float *inverse, int N) { 
    int det = determinant(A, N, N); 
    if (det == 0) { 
        printf("DETERMINANTE 0, NO SE PUEDE INVERTIR\n");
        return 0; 
    } 
    int *adj = (int *) malloc(N * N * sizeof(int));
    adjoint(A, adj, N); 
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            inverse[i * N + j] = (float) adj[i * N + j]/det; 
    return 1; 
} 
int main(void)
{
    int N = 2;
    int *A = (int *) malloc(N * N * sizeof(int));
    float *A_ = (float *) malloc(N * N * sizeof(float));
    A[0] = 1;
    A[1] = 0;
    A[2] = 1;
    A[3] = 1;
    inverse(A, A_, N);
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j){
            printf("%f ", A_[i * N + j]);
        } putchar('\n');
    }
    return 0;
}