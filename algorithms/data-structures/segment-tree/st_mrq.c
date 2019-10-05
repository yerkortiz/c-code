#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#define SWAP(x, y, type) { type temp = x; x = y; y = temp; }
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
void print_arr(int *start, int *end)
{
    for(; start != end; ++start)
        printf("%d%c", *start, (start < end - 1)? ' ': '\n');
}
void build(int t[], int n) { 
  for (int i = n - 1; i > 0; --i) t[i] = MIN(t[i<<1], t[i<<1|1]);
}
int query(int t[], int n, int l, int r) {  
  int res = INT_MAX;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = MIN(t[l], res), ++l; 
    if (r&1) --r, res = MIN(t[r], res); 
  }
  printf("%d\n", res);
  return res;
}
  /* recordatorio: ver como cambiar los operadores de incremento
  para que esten como indices dentro de t[l++], t[--r] ya que 
  el macro min(a,b) no los considera y no actualiza los valores de
  l y r.*/
void update(int p, int value, int t[], int n) { 
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = MIN(t[p], t[p^1]);
}

int main()
{
    int n; scanf("%d", &n);
    int t[n << 1]; memset(t, 0, 2 * n * sizeof(int));
    for(int i = 0; i < n; ++i) scanf("%d", t + n + i);
    build(t, n);
    print_arr(t, t + (n << 1));
    query(t, n, 0, 3);
    return 0;
}
