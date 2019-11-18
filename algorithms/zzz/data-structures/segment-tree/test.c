#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define SWAP(x, y, type) do { type temp = x; x = y; y = temp; } while (0)
void print_arr(int *start, int *end)
{
    for(; start != end; ++start)
        printf("%d%c", *start, (start < end - 1)? ' ': '\n');
}
int m_bit(int n)//most significant bit
{
    return (n == 1)? 0 : 1 + m_bit(n >> 1);
}
void build(int t[], int n) { 
  for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}
int query(int t[], int n, int l, int r) {  
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l], ++l;
    if (r&1) --r, res += t[r];
  }
  printf("%d\n", res);
  return res;
}
void modify(int p, int value, int t[], int n) { 
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int main()
{
    int n; scanf("%d", &n);
    int t[n << 1]; memset(t, 0, 2 * n * sizeof(int));
    for(int i = 0; i < n; ++i) scanf("%d", t + n + i);
    build(t, n);
    print_arr(t, t + (n << 1));
    query(t, n, 0, 4);

    
    return 0;
}