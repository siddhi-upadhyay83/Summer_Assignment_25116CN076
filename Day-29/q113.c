//wap to create menu-driven//
#include <stdio.h>

// Function prototypes
void addNumbers();
void subtractNumbers();
void multiplyNumbers();
void divideNumbers();
void findFactorial();
void checkPrimeNumber();
void displayMenu();

int main() {
    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNumbers();
                break;
            case 2:
                subtractNumbers();
                break;
            case 3:
                multiplyNumbers();
                break;
            case 4:
                divideNumbers();
                break;
            case 5:
                findFactorial();
                break;
            case 6:
                checkPrimeNumber();
                break;
            case 0:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

void displayMenu() {
    printf("\n========== MAIN MENU ==========\n");
    printf("  1. Addition\n");
    printf("  2. Subtraction\n");
    printf("  3. Multiplication\n");
    printf("  4. Division\n");
    printf("  5. Factorial\n");
    printf("  6. Prime Number Check\n");
    printf("  0. Exit\n");
    printf("================================\n");
}

void addNumbers() {
    double a, b;
    printf("\nEnter two numbers: ");
    scanf("%lf %lf", &a, &b);
    printf("Result: %.2lf + %.2lf = %.2lf\n", a, b, a + b);
}

void subtractNumbers() {
    double a, b;
    printf("\nEnter two numbers: ");
    scanf("%lf %lf", &a, &b);
    printf("Result: %.2lf - %.2lf = %.2lf\n", a, b, a - b);
}

void multiplyNumbers() {
    double a, b;
    printf("\nEnter two numbers: ");
    scanf("%lf %lf", &a, &b);
    printf("Result: %.2lf * %.2lf = %.2lf\n", a, b, a * b);
}

void divideNumbers() {
    double a, b;
    printf("\nEnter two numbers: ");
    scanf("%lf %lf", &a, &b);
    if (b == 0) {
        printf("Error: Division by zero is not allowed!\n");
    } else {
        printf("Result: %.2lf / %.2lf = %.2lf\n", a, b, a / b);
    }
}

void findFactorial() {
    int n;
    long long fact = 1;
    printf("\nEnter a non-negative integer: ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Error: Factorial of negative number is undefined!\n");
        return;
    }
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    printf("Factorial of %d = %lld\n", n, fact);
}

void checkPrimeNumber() {
    int n, isPrime = 1;
    printf("\nEnter a positive integer: ");
    scanf("%d", &n);
    if (n < 2) {
        isPrime = 0;
    } else {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                isPrime = 0;
                break;
            }
        }
    }
    if (isPrime)
        printf("%d is a PRIME number.\n", n);
    else
        printf("%d is NOT a prime number.\n", n);
}