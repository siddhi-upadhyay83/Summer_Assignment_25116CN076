//wap to intersection of arrays//
#include <stdio.h>
// works for unsorted arrays
int main() {
    int a[] = {21, 22, 23, 24, 25};
    int b[] = {23, 24, 25, 26, 27};
    int n = 5, m = 5;
    printf("Intersection: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                printf("%d ", a[i]);
                break;
            }
        }
    }
    printf("\n");
    return 0;
}