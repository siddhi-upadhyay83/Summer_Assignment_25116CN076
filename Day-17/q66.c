//wap to union of arrays//
#include <stdio.h>
int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {3, 4, 5, 6, 7};
    int n = 5, m = 5;
    int result[n + m];
    int k = 0;
    // Add all elements of a
    for (int i = 0; i < n; i++)
        result[k++] = a[i];
    // Add elements of b only if not in a
    for (int j = 0; j < m; j++) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (b[j] == a[i]) {
                found = 1;
                break;
            }
        }
        if (!found)
            result[k++] = b[j];
    }
    printf("Union: ");
    for (int i = 0; i < k; i++)
        printf("%d ", result[i]);
    printf("\n");
    return 0;
}