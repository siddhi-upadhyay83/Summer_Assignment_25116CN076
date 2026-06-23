//wap to create voting eligiblity system//
#include <stdio.h>
int main() {
    int age;
    char citizen, registered;
    printf("=== Voting Eligibility System ===\n\n");

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Are you a citizen? (y/n): ");
    scanf(" %c", &citizen);

    printf("Are you a registered voter? (y/n): ");
    scanf(" %c", &registered);

    printf("\n--- Result ---\n");

    if (age < 18) {
        printf("Not eligible: You must be at least 18 years old.\n");
    } else if (citizen != 'y' && citizen != 'Y') {
        printf("Not eligible: You must be a citizen to vote.\n");
    } else if (registered != 'y' && registered != 'Y') {
        printf("Not eligible: You must be a registered voter.\n");
    } else {
        printf("Eligible: You are eligible to vote!\n");
    }
    return 0;
}