//wap to add matrices//
#include <stdio.h>
int main() {
    int r, c;
    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);

    int A[r][c], B[r][c], C[r][c];
    printf("Enter matrix A:\n");
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            scanf("%d", &B[i][j]);

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            C[i][j] = A[i][j] + B[i][j];

    printf("Sum matrix:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }
    return 0;
}