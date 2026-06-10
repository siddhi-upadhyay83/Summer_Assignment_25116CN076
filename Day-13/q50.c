//wap to find sum and avg of array//
#include <stdio.h>
int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    int sum = 0;
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element [%d]: ", i);
        scanf("%d", &arr[i]);
        sum += arr[i];  
    }
    float avg = (float)sum/n;
    printf("\nArray elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nSum     = %d", sum);
    printf("\nAverage = %.2f\n", avg);
    return 0;
}