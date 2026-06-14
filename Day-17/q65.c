//wap to merge arrays//
#include <stdio.h>
int main() {
    int a[] = {11, 13, 15, 17, 19};
    int b[] = {12, 14, 16, 18, 10};
    int n = 5, m = 5;
    int merged[n + m];
    int i = 0, j = 0, k = 0;

    // Merge two sorted arrays
    while (i < n && j < m) {
        if (a[i] <= b[j])
            merged[k++] = a[i++];
        else
            merged[k++] = b[j++];
    }
    while (i < n) merged[k++] = a[i++];
    while (j < m) merged[k++] = b[j++];
    printf("Merged Array: ");
    for (int x = 0; x < n + m; x++)
        printf("%d ", merged[x]);
    printf("\n");
    return 0;
}

