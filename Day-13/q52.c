//wap to count even and odd elements//
#include <stdio.h>
int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element [%d]: ", i);
        scanf("%d", &arr[i]);
    }
    int evenCount = 0, oddCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            evenCount++;
        else
            oddCount++;
    }
    printf("\nArray elements: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\nEven count = %d", evenCount);
    printf("\nOdd  count = %d\n", oddCount);
    return 0;
}