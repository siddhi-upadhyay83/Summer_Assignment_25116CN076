#include <stdio.h>

int main() {
    int arr[50], n, i;
    int largest, second;

    printf("Enter size of array: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nArray elements: ");
    for (i = 0; i < n; i++)
        printf("%d\t", arr[i]);
    largest = second = -99999;

    for (i = 0; i < n; i++) {
        if (arr[i] > largest) {
            second = largest;    
            largest = arr[i];    
        } else if (arr[i] > second && arr[i] != largest) {
            second = arr[i];     
        }
    }

    if (second == -99999)
        printf("\n\nNo second largest element found.\n");
    else
        printf("\n\nSecond largest element = %d\n", second);

    return 0;
}