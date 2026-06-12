//wap to rotate array left//
#include <stdio.h>
void rotateLeft(int arr[], int n, int k) {
    k = k % n; // handle k > n
    // Reverse first k elements
    int left = 0, right = k - 1;
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
        left++; 
        right--;
    }
    // Reverse entire array
    left = 0; right = n - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main() {
    int arr[] = {6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2; 
    printf("Original: ");
    printArray(arr, n);
    rotateLeft(arr, n, k);
    printf("Rotated left by %d: ", k);
    printArray(arr, n);
    return 0;
}