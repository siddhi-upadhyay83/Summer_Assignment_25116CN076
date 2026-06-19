//wap to rotate array right//
#include <stdio.h>
void rotateRight(int arr[], int n, int k) {
    k = k % n; 
    // Reverse entire array
    int left = 0, right = n - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++; right--;
    }
    // Reverse first k elements
    left = 0; right = k - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++; right--;
    }
    // Reverse remaining elements
    left = k; right = n - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++; right--;
    }
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main() {
    int arr[] = {11, 22, 33, 44, 55};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2; // rotate right by 2
    printf("Original: ");
    printArray(arr, n);
    rotateRight(arr, n, k);
    printf("Rotated right by %d: ", k);
    printArray(arr, n);
    return 0;
}
