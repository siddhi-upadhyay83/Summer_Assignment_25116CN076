//wap to merge two sorted arrays//
#include <stdio.h>
int main() {
    int n1, n2, i, j, k;
    // Input size of first array
    printf("Enter size of first array: ");
    scanf("%d", &n1);

    int arr1[n1];
    printf("Enter elements of first sorted array:\n");
    for(i = 0; i < n1; i++) {
        scanf("%d", &arr1[i]);
    }
    // Input size of second array
    printf("Enter size of second array: ");
    scanf("%d", &n2);

    int arr2[n2];
    printf("Enter elements of second sorted array:\n");
    for(i = 0; i < n2; i++) {
        scanf("%d", &arr2[i]);
    }

    int merged[n1 + n2];
    i = 0;
    j = 0;
    k = 0;
    // Merge the arrays
    while(i < n1 && j < n2) {
        if(arr1[i] <= arr2[j]) {
            merged[k] = arr1[i];
            i++;
        } else {
            merged[k] = arr2[j];
            j++;
        }
        k++;
    }
    // Copy remaining elements of arr1
    while(i < n1) {
        merged[k] = arr1[i];
        i++;
        k++;
    }
    // Copy remaining elements of arr2
    while(j < n2) {
        merged[k] = arr2[j];
        j++;
        k++;
    }
    // Display merged array
    printf("Merged sorted array: ");
    for(i = 0; i < n1 + n2; i++) {
        printf("%d ", merged[i]);
    }

    return 0;
}