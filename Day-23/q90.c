//wap to find first repeating character//
#include <stdio.h>
#include <string.h>

char firstRepeating(char str[]) {
    int freq[256] = {0};
    int n = strlen(str);

    for (int i = 0; i < n; i++) {
        unsigned char ch = (unsigned char)str[i];
        freq[ch]++;
        if (freq[ch] == 2)   // second occurrence = first repeat found
            return str[i];
    }

    return '\0';  // no repeating character found
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    char result = firstRepeating(str);

    if (result != '\0')
        printf("First repeating character: %c\n", result);
    else
        printf("No repeating character found.\n");

    return 0;
}