//wap to create ATM simulation//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ATTEMPTS 3
#define MAX_HISTORY  10

float balance = 10000.0;
char  pin[5]  = "1234";

void checkBalance() {
    printf("\nCurrent Balance: Rs. %.2f\n", balance);
}
void deposit() {
    float amount;
    printf("Enter amount to deposit: Rs. ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }
    balance += amount;
    printf("Rs. %.2f deposited. New Balance: Rs. %.2f\n", amount, balance);
}
void withdraw() {
    float amount;
    printf("Enter amount to withdraw: Rs. ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }
    if (amount > balance) {
        printf("Insufficient balance! Available: Rs. %.2f\n", balance);
        return;
    }
    balance -= amount;
    printf("Rs. %.2f withdrawn. Remaining Balance: Rs. %.2f\n", amount, balance);
}
void changePin() {
    char oldPin[5], newPin[5];
    printf("Enter current PIN: ");
    scanf("%4s", oldPin);
    if (strcmp(oldPin, pin) != 0) {
        printf("Incorrect PIN.\n");
        return;
    }
    printf("Enter new PIN: ");
    scanf("%4s", newPin);
    strcpy(pin, newPin);
    printf("PIN changed successfully.\n");
}
int login() {
    char entered[5];
    int attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        printf("Enter PIN: ");
        scanf("%4s", entered);
        if (strcmp(entered, pin) == 0) return 1;
        attempts++;
        printf("Wrong PIN. %d attempt(s) remaining.\n", MAX_ATTEMPTS - attempts);
    }
    printf("Card blocked after %d wrong attempts!\n", MAX_ATTEMPTS);
    return 0;
}
int main() {
    printf("=== ATM Simulation ===\n");

    if (!login()) return 0;

    int choice;
    do {
        printf("\n--- Main Menu ---\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Change PIN\n");
        printf("5. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: checkBalance(); break;
            case 2: deposit();      break;
            case 3: withdraw();     break;
            case 4: changePin();    break;
            case 5: printf("Thank you for using the ATM. Goodbye!\n"); break;
            default: printf("Invalid option. Try again.\n");
        }
    } while (choice != 5);
    return 0;
}