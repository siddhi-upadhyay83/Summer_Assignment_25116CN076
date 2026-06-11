//wap to find duplicates in array//
#include <stdio.h>
int main() {
    int arr[50], n, i, j;
    int visited[50];

    printf("Enter size of array: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        visited[i] = 0;  
    }

    printf("\nArray elements: ");
    for (i = 0; i < n; i++)
        printf("%d\t", arr[i]);

    printf("\n\nDuplicate elements:\n");
    printf("-------------------------\n");

    int found = 0; 

    for (i = 0; i < n; i++) {
        if (visited[i] == 0) {
            int count = 1;

            for (j = i + 1; j < n; j++) {
                if (arr[j] == arr[i]) {
                    count++;
                    visited[j] = 1; 
                }
            }

            if (count > 1) {
                printf("%d appears %d times\n", arr[i], count);
                found = 1;
            }
            visited[i] = 1;
        }
    }

    if (found == 0)
        printf("No duplicates found.\n");

    return 0;
}