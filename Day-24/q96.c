//wap to remove duplicate characters//
// WAP to remove duplicate characters from a string
// Example: programming -> progamin

#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int i, j, k;

    printf("Enter a string: ");
    scanf("%s", str);

    for (i = 0; str[i] != '\0'; i++) {
        for (j = i + 1; str[j] != '\0'; ) {
            if (str[i] == str[j]) {
                // Shift characters to the left
                for (k = j; str[k] != '\0'; k++) {
                    str[k] = str[k + 1];
                }
            } else {
                j++;
            }
        }
    }

    printf("String after removing duplicates: %s\n", str);
    return 0;
}