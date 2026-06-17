//wap to find row-wise-sum//
#include <stdio.h>
#define MAX 10
int main() {
    int A[MAX][MAX];
    int m, n, sum;
    printf("Enter rows and columns (m n): ");
    scanf("%d %d", &m, &n);
    printf("Enter elements of matrix (%dx%d):\n", m, n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    // Print matrix
    printf("\nMatrix:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", A[i][j]);
        printf("\n");
    }
    // Row-wise sum
    printf("\nRow-wise Sum:\n");
    for (int i = 0; i < m; i++) {
        sum = 0;
        for (int j = 0; j < n; j++)
            sum += A[i][j];
        printf("Row %d sum = %d\n", i + 1, sum);
    }
    return 0;
}