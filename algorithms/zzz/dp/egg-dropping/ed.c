# include <stdio.h> 
# include <limits.h> 
#define EXIT_PROGRAM return 0
#define OR ||
#define N_MAX (unsigned)(1e9)
int max(int a, int b) { return (a > b)? a: b; } 
int eggDrop(int n, int k) 
{ 
	int eggFloor[n+1][k+1]; 
	int res; 
	int i, j, x; 
	for (i = 1; i <= n; i++) { 
		eggFloor[i][1] = 1; 
		eggFloor[i][0] = 0; 
	} 
	for (j = 1; j <= k; j++) 
		eggFloor[1][j] = j; 
	for (i = 2; i <= n; i++) { 
		for (j = 2; j <= k; j++) { 
			eggFloor[i][j] = N_MAX; 
			for (x = 1; x <= j; x++) { 
				res = 1 + max(eggFloor[i-1][x-1], eggFloor[i][j - x]); 
				if (res < eggFloor[i][j]) 
					eggFloor[i][j] = res; 
			} 
		} 
	} 
	return eggFloor[n][k]; 
} 
int main() { 
	int n = 2, k = 36; 
	printf ("Numero minimo de intentos para %d huevos y "
			"%d pisos es %d \n", n, k, eggDrop(n, k)); 
	return 0; 
} 
