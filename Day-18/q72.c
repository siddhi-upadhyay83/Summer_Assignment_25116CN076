//wap to sort array in descending order//
#include <stdio.h>
int main() {
    int arr[] = {46, 5, 10, 92, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i, j, temp;
    // Bubble sort in descending order
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {  // change < to > for ascending
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Sorted array (descending): ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}