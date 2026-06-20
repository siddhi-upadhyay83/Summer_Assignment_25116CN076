//wap to check anagram strings//
#include <stdio.h>
#include <string.h>

int isAnagram(char s1[], char s2[]) {
    if (strlen(s1) != strlen(s2))
        return 0;  // different lengths can't be anagrams

    int freq[256] = {0};

    // increment for s1, decrement for s2
    for (int i = 0; s1[i] != '\0'; i++) {
        freq[(unsigned char)s1[i]]++;
        freq[(unsigned char)s2[i]]--;
    }

    // if all counts are 0, strings are anagrams
    for (int i = 0; i < 256; i++)
        if (freq[i] != 0)
            return 0;

    return 1;
}

int main() {
    char s1[100], s2[100];

    printf("Enter first string:  ");
    scanf("%s", s1);
    printf("Enter second string: ");
    scanf("%s", s2);

    if (isAnagram(s1, s2))
        printf("\"%s\" and \"%s\" ARE anagrams.\n", s1, s2);
    else
        printf("\"%s\" and \"%s\" are NOT anagrams.\n", s1, s2);

    return 0;
}
