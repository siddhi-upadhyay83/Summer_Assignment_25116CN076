//wap to create quiz application//
#include <stdio.h>
#include <string.h>

#define TOTAL_QUESTIONS 5
#define OPTIONS         4
#define MARKS_PER_Q    10

struct Question {
    char question[200];
    char options[OPTIONS][100];
    int  answer;   // 0-indexed correct option
};
void displayQuestion(struct Question q, int num) {
    printf("\nQ%d: %s\n", num, q.question);
    for (int i = 0; i < OPTIONS; i++) {
        printf("  %c. %s\n", 'A' + i, q.options[i]);
    }
}
int main() {
    struct Question quiz[TOTAL_QUESTIONS] = {
        {
            "Which header file is required for printf() and scanf()?",
            {"stdlib.h", "math.h", "stdio.h", "string.h"},
            2
        },
        {
            "What is the size of an int on a 32-bit system?",
            {"1 byte", "2 bytes", "4 bytes", "8 bytes"},
            2
        },
        {
            "Which keyword exits a loop immediately in C?",
            {"exit", "stop", "break", "return"},
            2
        },
        {
            "What does %d represent in printf()?",
            {"Float", "Character", "String", "Integer"},
            3
        },
        {
            "Which function returns the length of a string?",
            {"length()", "strlen()", "strcat()", "size()"},
            1
        }
    };
    int score = 0, correct = 0, wrong = 0;
    char chosen;

    printf("=============================\n");
    printf("   Welcome to C Quiz App!   \n");
    printf("=============================\n");
    printf("Total Questions : %d\n", TOTAL_QUESTIONS);
    printf("Marks per Q     : %d\n", MARKS_PER_Q);
    printf("No negative marks\n");
    printf("=============================\n");

    for (int i = 0; i < TOTAL_QUESTIONS; i++) {
        displayQuestion(quiz[i], i + 1);
        printf("Your answer (A/B/C/D): ");
        scanf(" %c", &chosen);

        // Convert to uppercase then to 0-based index
        if (chosen >= 'a' && chosen <= 'd') chosen -= 32;
        int idx = chosen - 'A';

        if (idx == quiz[i].answer) {
            printf("  Correct!\n");
            score += MARKS_PER_Q;
            correct++;
        } else {
            printf("  Wrong! Correct answer: %c. %s\n",
                   'A' + quiz[i].answer,
                   quiz[i].options[quiz[i].answer]);
            wrong++;
        }
    }
    printf("\n=============================\n");
    printf("         RESULTS             \n");
    printf("=============================\n");
    printf("Correct  : %d\n", correct);
    printf("Wrong    : %d\n", wrong);
    printf("Score    : %d / %d\n", score, TOTAL_QUESTIONS * MARKS_PER_Q);

    float pct = (float)correct / TOTAL_QUESTIONS * 100;
    if (pct == 100)       printf("Grade: Outstanding!\n");
    else if (pct >= 60)   printf("Grade: Good job!\n");
    else                  printf("Grade: Keep practising!\n");
    return 0;
}