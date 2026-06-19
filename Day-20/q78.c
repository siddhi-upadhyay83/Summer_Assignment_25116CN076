//wap to check symmetric matrix//
#include <stdio.h>
#define MAX 10
int main() {
    int A[MAX][MAX];
    int n, symmetric = 1;
    printf("Enter size of square matrix (n): ");
    scanf("%d", &n);

    printf("Enter elements of matrix (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    // Check if A[i][j] == A[j][i]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] != A[j][i]) {
                symmetric = 0;
                break;
            }
        }
        if (!symmetric) break;
    }
    // Print matrix
    printf("\nMatrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d", A[i][j]);
        printf("\n");
    }
    if (symmetric)
        printf("\nThe matrix IS symmetric.\n");
    else
        printf("\nThe matrix is NOT symmetric.\n");
    return 0;
}