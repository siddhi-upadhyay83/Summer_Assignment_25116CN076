#include <stdio.h>
void moveZeroesToEnd(int arr[], int n) {
    int pos = 0; // position to place next non-zero
    // Move all non-zero elements forward
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0)
            arr[pos++] = arr[i];
    }
    // Fill remaining positions with 0
    while (pos < n)
        arr[pos++] = 0;
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main() {
    int arr[] = {0, 5, 4, 0, 22, 3, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original: ");
    printArray(arr, n);
    moveZeroesToEnd(arr, n);
    printf("After:    ");
    printArray(arr, n);
    return 0;
}