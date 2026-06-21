//wap to find longest word//
// WAP to find the longest word in a string

#include <stdio.h>
#include <string.h>

int main() {
    char str[200], word[50], longest[50];
    int i = 0, j = 0, maxLen = 0;

    printf("Enter a sentence: ");
    fgets(str, sizeof(str), stdin);

    while (1) {
        if (str[i] != ' ' && str[i] != '\0' && str[i] != '\n') {
            word[j++] = str[i];
        } else {
            word[j] = '\0';

            if (j > maxLen) {
                maxLen = j;
                strcpy(longest, word);
            }

            j = 0;

            if (str[i] == '\0' || str[i] == '\n')
                break;
        }

        i++;
    }

    printf("Longest word: %s\n", longest);
    printf("Length: %d\n", maxLen);
    return 0;
}