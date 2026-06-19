//wap to find missing number in array//
#include <stdio.h>
int findMissing(int arr[], int n) {
    int total = (n + 1) * (n + 2) / 2;
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return total - sum;
}
int main() {
    int arr[] = {1, 2, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Missing number: %d\n", findMissing(arr, n));
    return 0;
}