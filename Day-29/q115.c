//wap to create menu-driven string operations system//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

// Function prototypes
void inputString(char str[]);
void displayString(char str[]);
void findLength(char str[]);
void copyString(char str[]);
void concatenateStrings(char str[]);
void compareStrings(char str[]);
void reverseString(char str[]);
void isPalindrome(char str[]);
void toUpperCase(char str[]);
void toLowerCase(char str[]);
void countVowelsConsonants(char str[]);
void countWords(char str[]);
void searchSubstring(char str[]);
void replaceCharacter(char str[]);
void displayMenu();

int main() {
    char str[MAX] = "";
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1:  inputString(str);           break;
            case 2:  displayString(str);         break;
            case 3:  findLength(str);            break;
            case 4:  copyString(str);            break;
            case 5:  concatenateStrings(str);    break;
            case 6:  compareStrings(str);        break;
            case 7:  reverseString(str);         break;
            case 8:  isPalindrome(str);          break;
            case 9:  toUpperCase(str);           break;
            case 10: toLowerCase(str);           break;
            case 11: countVowelsConsonants(str); break;
            case 12: countWords(str);            break;
            case 13: searchSubstring(str);       break;
            case 14: replaceCharacter(str);      break;
            case 0:  printf("\nExiting... Goodbye!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void displayMenu() {
    printf("\n========= STRING OPERATIONS MENU =========\n");
    printf("   1.  Input String\n");
    printf("   2.  Display String\n");
    printf("   3.  Find Length\n");
    printf("   4.  Copy String\n");
    printf("   5.  Concatenate Strings\n");
    printf("   6.  Compare Strings\n");
    printf("   7.  Reverse String\n");
    printf("   8.  Check Palindrome\n");
    printf("   9.  Convert to UPPERCASE\n");
    printf("   10. Convert to lowercase\n");
    printf("   11. Count Vowels & Consonants\n");
    printf("   12. Count Words\n");
    printf("   13. Search Substring\n");
    printf("   14. Replace a Character\n");
    printf("   0.  Exit\n");
    printf("===========================================\n");
}

// 1. Input string
void inputString(char str[]) {
    printf("\nEnter a string: ");
    fgets(str, MAX, stdin);
    // Remove trailing newline
    int len = strlen(str);
    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
    printf("String stored successfully!\n");
}

// 2. Display string
void displayString(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    printf("\nCurrent String: \"%s\"\n", str);
}

// 3. Find length (without strlen)
void findLength(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    int len = 0;
    while (str[len] != '\0')
        len++;
    printf("\nLength of \"%s\" = %d\n", str, len);
}

// 4. Copy string
void copyString(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    char dest[MAX];
    // Manual copy
    int i = 0;
    while (str[i] != '\0') {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    printf("\nOriginal : \"%s\"\n", str);
    printf("Copied   : \"%s\"\n", dest);
}

// 5. Concatenate two strings
void concatenateStrings(char str[]) {
    char str2[MAX], result[MAX * 2];
    printf("\nCurrent string : \"%s\"\n", str);
    printf("Enter string to append: ");
    fgets(str2, MAX, stdin);
    int len = strlen(str2);
    if (str2[len - 1] == '\n')
        str2[len - 1] = '\0';

    // Manual concatenation
    int i = 0, j = 0;
    while (str[i] != '\0')  { result[i] = str[i]; i++; }
    while (str2[j] != '\0') { result[i] = str2[j]; i++; j++; }
    result[i] = '\0';

    printf("Concatenated   : \"%s\"\n", result);

    // Update main string
    strcpy(str, result);
}

// 6. Compare two strings
void compareStrings(char str[]) {
    char str2[MAX];
    printf("\nCurrent string : \"%s\"\n", str);
    printf("Enter string to compare: ");
    fgets(str2, MAX, stdin);
    int len = strlen(str2);
    if (str2[len - 1] == '\n')
        str2[len - 1] = '\0';

    int result = strcmp(str, str2);
    if (result == 0)
        printf("Strings are EQUAL.\n");
    else if (result < 0)
        printf("\"%s\" comes BEFORE \"%s\" alphabetically.\n", str, str2);
    else
        printf("\"%s\" comes AFTER \"%s\" alphabetically.\n", str, str2);
}

// 7. Reverse string
void reverseString(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    int left = 0, right = strlen(str) - 1;
    char temp;
    while (left < right) {
        temp        = str[left];
        str[left]   = str[right];
        str[right]  = temp;
        left++;  right--;
    }
    printf("Reversed String: \"%s\"\n", str);
}

// 8. Check palindrome
void isPalindrome(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }

    char temp[MAX];
    strcpy(temp, str);

    // Convert to lowercase for case-insensitive check
    for (int i = 0; temp[i]; i++)
        temp[i] = tolower(temp[i]);

    int left = 0, right = strlen(temp) - 1, flag = 1;
    while (left < right) {
        if (temp[left] != temp[right]) { flag = 0; break; }
        left++;  right--;
    }
    printf("\n\"%s\" is %sa palindrome.\n", str, flag ? "" : "NOT ");
}

// 9. Convert to uppercase
void toUpperCase(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    for (int i = 0; str[i]; i++)
        str[i] = toupper(str[i]);
    printf("Uppercase: \"%s\"\n", str);
}

// 10. Convert to lowercase
void toLowerCase(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
    printf("Lowercase: \"%s\"\n", str);
}

// 11. Count vowels and consonants
void countVowelsConsonants(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    int vowels = 0, consonants = 0;
    for (int i = 0; str[i]; i++) {
        char ch = tolower(str[i]);
        if (isalpha(ch)) {
            if (ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u')
                vowels++;
            else
                consonants++;
        }
    }
    printf("\nString    : \"%s\"\n", str);
    printf("Vowels    : %d\n", vowels);
    printf("Consonants: %d\n", consonants);
}

// 12. Count words
void countWords(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    int words = 0, inWord = 0;
    for (int i = 0; str[i]; i++) {
        if (!isspace(str[i]) && !inWord) {
            words++;
            inWord = 1;
        } else if (isspace(str[i])) {
            inWord = 0;
        }
    }
    printf("\nString : \"%s\"\n", str);
    printf("Words  : %d\n", words);
}

// 13. Search substring
void searchSubstring(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    char sub[MAX];
    printf("\nEnter substring to search: ");
    fgets(sub, MAX, stdin);
    int len = strlen(sub);
    if (sub[len - 1] == '\n')
        sub[len - 1] = '\0';

    char *pos = strstr(str, sub);
    if (pos)
        printf("Substring \"%s\" found at index %ld.\n", sub, pos - str);
    else
        printf("Substring \"%s\" NOT found.\n", sub);
}

// 14. Replace a character
void replaceCharacter(char str[]) {
    if (strlen(str) == 0) { printf("\nString is empty!\n"); return; }
    char oldCh, newCh;
    int count = 0;
    printf("\nEnter character to replace: ");
    scanf("%c", &oldCh);
    getchar();
    printf("Enter new character      : ");
    scanf("%c", &newCh);
    getchar();

    for (int i = 0; str[i]; i++) {
        if (str[i] == oldCh) {
            str[i] = newCh;
            count++;
        }
    }
    printf("Replaced %d occurrence(s). Updated string: \"%s\"\n", count, str);
}