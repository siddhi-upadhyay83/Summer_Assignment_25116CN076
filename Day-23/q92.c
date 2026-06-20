//wap to find maximum occuring character//
#include <stdio.h>
#include <string.h>

char maxOccurring(char str[]) {
    int freq[256] = {0};

    // count frequencies
    for (int i = 0; str[i] != '\0'; i++)
        freq[(unsigned char)str[i]]++;

    // find character with maximum frequency
    int maxCount = 0;
    char maxChar = '\0';

    for (int i = 0; i < 256; i++) {
        if (freq[i] > maxCount) {
            maxCount = freq[i];
            maxChar  = (char)i;
        }
    }

    return maxChar;
}
int main() {
    char str[100];

    printf("Enter a string: ");
    scanf("%s", str);

    char result = maxOccurring(str);

    printf("Maximum occurring character: '%c'\n", result);
    return 0;
}