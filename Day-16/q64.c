//wap to remove duplicates from array//
#include <stdio.h>
int removeDuplicates(int arr[], int n) {
    int temp[n], k = 0;
    for (int i = 0; i < n; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < k; j++) {
            if (arr[i] == temp[j]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate)
            temp[k++] = arr[i];
    }
    for (int i = 0; i < k; i++)
        arr[i] = temp[i];   
    return k;
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main() {
    int arr[] = {1, 2, 3, 2, 4, 3, 5, 1, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array:  ");
    printArray(arr, n);
    n = removeDuplicates(arr, n);
    printf("After removing duplicates: ");
    printArray(arr, n);
    return 0;
}