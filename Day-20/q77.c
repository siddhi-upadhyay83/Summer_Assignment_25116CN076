//wap to multiply matrices//
#include <stdio.h>
#define MAX 10
int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int m, n, p;
    printf("Enter rows and columns of A (m n): ");
    scanf("%d %d", &m, &n);
    printf("Enter columns of B (p): ");
    scanf("%d", &p);
    printf("Enter elements of A (%dx%d):\n", m, n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
    printf("Enter elements of B (%dx%d):\n", n, p);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            scanf("%d", &B[i][j]);
    // Multiply
    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    // Print result
    printf("\nResult matrix C (%dx%d):\n", m, p);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++)
            printf("%4d", C[i][j]);
        printf("\n");
    }
    return 0;
}