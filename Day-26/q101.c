//wap to create number guessing game//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int secret, guess, attempts = 0;
    int maxTries = 7;

    srand(time(0));  // seed random number generator
    secret = (rand() % 100) + 1;  // random number between 1 and 100

    printf("=== Number Guessing Game ===\n");
    printf("I have picked a number between 1 and 100.\n");
    printf("You have %d attempts. Good luck!\n\n", maxTries);

    while (attempts < maxTries) {
        printf("Attempt %d/%d — Enter your guess: ", attempts + 1, maxTries);
        scanf("%d", &guess);
        attempts++;

        if (guess == secret) {
            printf("\nCorrect! You guessed it in %d attempt%s!\n",
                   attempts, attempts == 1 ? "" : "s");
            return 0;
        } else if (guess < secret) {
            printf("Too low! Try a higher number.\n");
        } else {
            printf("Too high! Try a lower number.\n");
        }
        if (attempts < maxTries) {
            printf("%d tries remaining.\n\n", maxTries - attempts);
        }
    }
    printf("\nGame over! The number was %d. Better luck next time!\n", secret);
    return 0;
}