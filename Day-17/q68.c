//wap to find common elements//
#include <stdio.h>
int main() {
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[] = {3, 4, 5, 7, 8, 6};
    int n = 6, m = 6;
    int common[10], k = 0;
    // Find common elements
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                common[k++] = a[i];
                break;
            }
        }
    }
    printf("Common Elements: ");
    for (int i = 0; i < k; i++)
        printf("%d ", common[i]);
    printf("\n");
    printf("Count: %d\n", k);
    return 0;
}


