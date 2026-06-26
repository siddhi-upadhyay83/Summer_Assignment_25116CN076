//wap to create menu-driven array operations system//
#include <stdio.h>

#define MAX 100

// Function prototypes
void inputArray(int arr[], int *n);
void displayArray(int arr[], int n);
void insertElement(int arr[], int *n);
void deleteElement(int arr[], int *n);
void searchElement(int arr[], int n);
void sortArray(int arr[], int n);
void reverseArray(int arr[], int n);
void findMinMax(int arr[], int n);
void sumAverage(int arr[], int n);
void displayMenu();

int main() {
    int arr[MAX], n = 0, choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: inputArray(arr, &n);       break;
            case 2: displayArray(arr, n);      break;
            case 3: insertElement(arr, &n);    break;
            case 4: deleteElement(arr, &n);    break;
            case 5: searchElement(arr, n);     break;
            case 6: sortArray(arr, n);         break;
            case 7: reverseArray(arr, n);      break;
            case 8: findMinMax(arr, n);        break;
            case 9: sumAverage(arr, n);        break;
            case 0: printf("\nExiting... Goodbye!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void displayMenu() {
    printf("\n======= ARRAY OPERATIONS MENU =======\n");
    printf("  1. Input Array\n");
    printf("  2. Display Array\n");
    printf("  3. Insert Element\n");
    printf("  4. Delete Element\n");
    printf("  5. Search Element (Linear Search)\n");
    printf("  6. Sort Array (Bubble Sort)\n");
    printf("  7. Reverse Array\n");
    printf("  8. Find Min & Max\n");
    printf("  9. Sum & Average\n");
    printf("  0. Exit\n");
    printf("======================================\n");
}

// 1. Input array elements
void inputArray(int arr[], int *n) {
    printf("\nEnter number of elements (max %d): ", MAX);
    scanf("%d", n);
    if (*n <= 0 || *n > MAX) {
        printf("Invalid size!\n");
        *n = 0;
        return;
    }
    printf("Enter %d elements:\n", *n);
    for (int i = 0; i < *n; i++) {
        printf("  arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }
    printf("Array stored successfully!\n");
}

// 2. Display array
void displayArray(int arr[], int n) {
    if (n == 0) { printf("\nArray is empty!\n"); return; }
    printf("\nArray elements: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nSize: %d\n", n);
}

// 3. Insert element at a given position
void insertElement(int arr[], int *n) {
    if (*n >= MAX) { printf("\nArray is full!\n"); return; }
    int pos, val;
    printf("\nEnter position to insert (0 to %d): ", *n);
    scanf("%d", &pos);
    if (pos < 0 || pos > *n) { printf("Invalid position!\n"); return; }
    printf("Enter value to insert: ");
    scanf("%d", &val);

    // Shift elements right
    for (int i = *n; i > pos; i--)
        arr[i] = arr[i - 1];

    arr[pos] = val;
    (*n)++;
    printf("Element %d inserted at position %d.\n", val, pos);
}

// 4. Delete element at a given position
void deleteElement(int arr[], int *n) {
    if (*n == 0) { printf("\nArray is empty!\n"); return; }
    int pos;
    printf("\nEnter position to delete (0 to %d): ", *n - 1);
    scanf("%d", &pos);
    if (pos < 0 || pos >= *n) { printf("Invalid position!\n"); return; }

    printf("Deleted element: %d\n", arr[pos]);

    // Shift elements left
    for (int i = pos; i < *n - 1; i++)
        arr[i] = arr[i + 1];

    (*n)--;
    printf("Array updated. New size: %d\n", *n);
}

// 5. Linear search
void searchElement(int arr[], int n) {
    if (n == 0) { printf("\nArray is empty!\n"); return; }
    int key, found = 0;
    printf("\nEnter element to search: ");
    scanf("%d", &key);

    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            printf("Element %d found at index %d.\n", key, i);
            found = 1;
        }
    }
    if (!found)
        printf("Element %d not found in the array.\n", key);
}

// 6. Bubble sort (ascending)
void sortArray(int arr[], int n) {
    if (n == 0) { printf("\nArray is empty!\n"); return; }
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp     = arr[j];
                arr[j]   = arr[j + 1];
                arr[j+1] = temp;
            }
        }
    }
    printf("Array sorted in ascending order.\n");
    displayArray(arr, n);
}

// 7. Reverse the array
void reverseArray(int arr[], int n) {
    if (n == 0) { printf("\nArray is empty!\n"); return; }
    int left = 0, right = n - 1, temp;
    while (left < right) {
        temp       = arr[left];
        arr[left]  = arr[right];
        arr[right] = temp;
        left++;  right--;
    }
    printf("Array reversed.\n");
    displayArray(arr, n);
}

// 8. Find minimum and maximum
void findMinMax(int arr[], int n) {
    if (n == 0) { printf("\nArray is empty!\n"); return; }
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    printf("\nMinimum element: %d\n", min);
    printf("Maximum element: %d\n", max);
}

// 9. Sum and average
void sumAverage(int arr[], int n) {
    if (n == 0) { printf("\nArray is empty!\n"); return; }
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    printf("\nSum     = %lld\n", sum);
    printf("Average = %.2lf\n", (double)sum / n);
}