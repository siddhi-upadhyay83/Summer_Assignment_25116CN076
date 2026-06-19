//wap to frequency of an element//
#include <stdio.h>
int main() {
    int arr[50], freq[50], n, i, j;

    printf("Enter size of array: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        freq[i] = -1;  // mark as unvisited
    }

    printf("\nElement\t\tFrequency\n");
    printf("-------------------------\n");

    for (i = 0; i < n; i++) {
        int count = 1;

        if (freq[i] == -1) {  // only process unvisited elements
            for (j = i + 1; j < n; j++) {
                if (arr[j] == arr[i]) {
                    count++;
                    freq[j] = 0;  // mark as visited (duplicate)
                }
            }
            freq[i] = count;
            printf("%d\t\t%d\n", arr[i], freq[i]);
        }
    }

    return 0;
}