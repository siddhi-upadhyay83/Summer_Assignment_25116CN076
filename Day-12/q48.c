//wap for perfect number using function//
#include <stdio.h>
#include <math.h>

int isPerfectSquare(int num) {
    int root = (int)sqrt(num);
    if (root * root == num) {
        printf("%d is a perfect square\n", num);
    } else {
        printf("%d is not a perfect square\n", num);
    }
    return 0;
}

int main() {
    int num;
    printf("Enter the number: ");
    scanf("%d", &num);
    isPerfectSquare(num);
    return 0;
}