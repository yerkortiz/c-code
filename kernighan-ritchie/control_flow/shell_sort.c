#include <stdio.h>
void print_array(int v[], int b) {
    int i;
    for(i = 0; i < b; ++i)
        printf((i == b - 1)? "%d\n": "%d ", v[i]);
}
void shellsort(int v[], int n) {
    int gap, i, j, temp;
    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++) {
            for (j = i - gap; j >= 0 && v[j]>v[j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }
            print_array(v, n);
        }
}
int main() {
    int v[] = {5, 4, 8, 1};
    shellsort(v, 4);
    return 0;   
}