//wap to reverse a string//
#include <stdio.h>

void reverseString(char str[], int length) {
    int start = 0;
    int end = length - 1;
    char temp;

    while (start < end) {
        // Swap characters
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%[^\n]", str);

    // Find length without strlen()
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    reverseString(str, length);
    printf("Reversed string: %s\n", str);

    return 0;
}