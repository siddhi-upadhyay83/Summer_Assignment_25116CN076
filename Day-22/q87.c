//wap to remove spaces from string//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeSpaces(char str[]) {
    int i, j = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (!isspace(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';  // Null-terminate the modified string
}

int main() {
    char str[200];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove trailing newline
    str[strcspn(str, "\n")] = '\0';

    printf("Original : \"%s\"\n", str);
    removeSpaces(str);
    printf("Modified : \"%s\"\n", str);

    return 0;
}