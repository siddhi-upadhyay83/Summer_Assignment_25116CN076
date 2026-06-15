//wap to binary search//
#include <stdio.h>
int main() {
    int arr[] = {21, 11, 23, 29, 34, 54, 98};  // must be sorted
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 29;
    int low = 0, high = n - 1, result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = mid;
            break;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (result != -1)
        printf("%d found at index %d\n", target, result);
    else
        printf("%d not found\n", target);
    return 0;
}