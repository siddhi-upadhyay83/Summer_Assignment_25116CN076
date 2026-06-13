//wap to find pair with givem sum//
#include <stdio.h>
void findPairs(int arr[], int n, int target) {
    int found = 0;
    printf("Pairs with sum %d:\n", target); 
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] + arr[j] == target) {
                printf("(%d, %d)\n", arr[i], arr[j]);
                found = 1;
            }
        }
    }   
    if (!found)
        printf("No pairs found.\n");
}
int main() {
    int arr[] = {1, 4, 3, 2, 6, 7, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;
    findPairs(arr, n, target);
    return 0;
}