//wap to find maximum freguency element//
#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 2, 4, 6, 5, 6, 6, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxFreq = 0, maxElem = arr[0];
    for (int i = 0; i < n; i++) {
        int freq = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i])
                freq++;
        }
        if (freq > maxFreq) {
            maxFreq = freq;
            maxElem = arr[i];
        }
    }
    printf("Maximum frequency element: %d (appears %d times)\n", maxElem, maxFreq);
    return 0;
}