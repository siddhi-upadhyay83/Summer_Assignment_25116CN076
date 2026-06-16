//wap to transpose matrix//
#include <stdio.h>
int main() {
    int r, c;
    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);
    int A[r][c], T[c][r];
    printf("Enter matrix:\n");
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            scanf("%d", &A[i][j]);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            T[j][i] = A[i][j];
    printf("Original matrix:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    printf("Transposed matrix:\n");
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++)
            printf("%d ", T[i][j]);
        printf("\n");
    }
    return 0;
}