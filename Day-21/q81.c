//wap to find string length wihout strlen()//
#include <stdio.h>

int stringLength(char str[]) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%[^\n]", str);
    
    int length = stringLength(str);
    printf("Length of \"%s\" = %d\n", str, length);
    
    return 0;
}