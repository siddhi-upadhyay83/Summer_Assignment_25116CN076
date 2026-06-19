//wap to count vowels and consonants//
#include <stdio.h>

int isVowel(char ch) {
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U');
}

int main() {
    char str[100];
    int vowels = 0, consonants = 0;

    printf("Enter a string: ");
    scanf("%[^\n]", str);

    for (int i = 0; str[i] != '\0'; i++) {
        char ch = str[i];

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            if (isVowel(ch)) {
                vowels++;
            } else {
                consonants++;
            }
        }
    }

    printf("Vowels     = %d\n", vowels);
    printf("Consonants = %d\n", consonants);

    return 0;
}