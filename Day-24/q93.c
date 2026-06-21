//wap to check string rotation//
// WAP to check whether one string is a rotation of another string

#include <stdio.h>
#include <string.h>

int main() {
    char str1[100], str2[100], temp[200];

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);

    // Check if lengths are equal
    if (strlen(str1) != strlen(str2)) {
        printf("String is not a rotation.\n");
    }
    else {
        // Concatenate str1 with itself
        strcpy(temp, str1);
        strcat(temp, str1);

        // Check if str2 is a substring of temp
        if (strstr(temp, str2) != NULL) {
            printf("String is a rotation.\n");
        } else {
            printf("String is not a rotation.\n");
        }
    }
    return 0;
}