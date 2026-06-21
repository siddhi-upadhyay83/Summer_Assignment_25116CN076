//wap to compress a string//
// WAP to compress a string
// Example: aaabbccccd → a3b2c4d1

#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int i, count;

    printf("Enter a string: ");
    scanf("%s", str);

    for (i = 0; str[i] != '\0'; i++) {
        count = 1;

        while (str[i] == str[i + 1]) {
            count++;
            i++;
        }

        printf("%c%d", str[i], count);
    }
    return 0;
}