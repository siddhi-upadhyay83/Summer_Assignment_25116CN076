//wap to find first non-repeating character//
#include <stdio.h>
#include <string.h>

char firstNonRepeating(char str[]) {
    int freq[256] = {0};  // frequency array for all ASCII chars
    int n = strlen(str);

    // Pass 1: count frequencies
    for (int i = 0; i < n; i++)
        freq[(unsigned char)str[i]]++;

    // Pass 2: find first char with frequency 1
    for (int i = 0; i < n; i++)
        if (freq[(unsigned char)str[i]] == 1)
            return str[i];

    return '\0';  // no non-repeating character found
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    char result = firstNonRepeating(str);

    if (result != '\0')
        printf("First non-repeating character: %c\n", result);
    else
        printf("No non-repeating character found.\n");

    return 0;
}