//wap to find diagonal sum//
#include <stdio.h>
int main() {
    int n;
    printf("Enter size of square matrix: ");
    scanf("%d", &n);
    int A[n][n];
    int primary = 0, secondary = 0;

    printf("Enter matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    for (int i = 0; i < n; i++) {
        primary   += A[i][i];          // top-left to bottom-right
        secondary += A[i][n - 1 - i];  // top-right to bottom-left
    }
    printf("Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    printf("Primary diagonal sum:   %d\n", primary);
    printf("Secondary diagonal sum: %d\n", secondary);
    printf("Total diagonal sum:     %d\n", primary + secondary);
    return 0;
}