#include <stdio.h>
#include <string.h>
#include <ctype.h>

void charFrequency(char str[]) {
    int freq[256] = {0};

    // Count frequency of each character
    for (int i = 0; str[i] != '\0'; i++) {
        freq[(unsigned char)str[i]]++;
    }

    // Display results
    printf("\nCharacter Frequencies:\n");
    printf("----------------------\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            if (isprint(i))
                printf("'%c' : %d\n", i, freq[i]);
        }
    }
}

int main() {
    char str[200];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove trailing newline
    str[strcspn(str, "\n")] = '\0';

    charFrequency(str);

    return 0;
}