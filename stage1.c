#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Menu Titles
char *mainMenu[] = {
    "1. Audition Management",
    "2. Training",
    "3. Debut"
};

char *trainingMenu[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

// Training progress storage
char trainingResults[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};

// Function Declarations
void showMainMenu();
void showTrainingMenu();
void handleTrainingStage(int stage);

int main() {
    char input[10];

    while (1) {
        showMainMenu();
        printf("Select a menu (or Q to quit): ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'q' || input[0] == 'Q' || input[0] == '0' || input[0] == '\n') {
            printf("Exiting program.\n");
            break;
        }

        switch (input[0]) {
            case '1':
                printf("Audition Management selected.\n\n");
                break;
            case '2':
                showTrainingMenu();
                break;
            case '3':
                printf("Debut selected.\n\n");
                break;
            default:
                printf("Invalid input. Try again.\n");
        }
    }

    return 0;
}

void showMainMenu() {
    printf("\n=== Main Menu ===\n");
    for (int i = 0; i < 3; i++) {
        printf("%s\n", mainMenu[i]);
    }
}

void showTrainingMenu() {
    char input[10];

    while (1) {
        printf("\n=== Training Menu ===\n");
        for (int i = 0; i < 8; i++) {
            printf("%s [%c]\n", trainingMenu[i], trainingResults[i]);
        }

        printf("Select a training stage (1-8) or Q to return: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'q' || input[0] == 'Q' || input[0] == '0' || input[0] == '\n') {
            printf("Returning to Main Menu.\n");
            break;
        }

        int stage = input[0] - '0';
        if (stage >= 1 && stage <= 8) {
            handleTrainingStage(stage);
        } else {
            printf("Invalid stage. Try again.\n");
        }
    }
}

void handleTrainingStage(int stage) {
    // Index is stage-1
    int index = stage - 1;

    // Rule 1: If already passed, don't allow again
    if (trainingResults[index] == 'P') {
        printf("Stage %d already completed with 'P'. Choose another stage.\n", stage);
        return;
    }

    // Rule 2: Stages 1 and 2 must be done in order
    if (stage == 2 && trainingResults[0] != 'P') {
        printf("You must complete Stage 1 first.\n");
        return;
    }
    if (stage >= 3 && trainingResults[1] != 'P') {
        printf("You must complete Stages 1 and 2 before doing this stage.\n");
        return;
    }

    // Ask for evaluation
    char choice[10];
    printf("Would you like to enter the evaluation result? (Y/N): ");
    fgets(choice, sizeof(choice), stdin);

    if (choice[0] == 'Y' || choice[0] == 'y') {
        char result[10];
        printf("Did you complete the training and pass the certification? (P/F): ");
        fgets(result, sizeof(result), stdin);

        if (result[0] == 'P' || result[0] == 'p') {
            trainingResults[index] = 'P';
            printf("Stage %d marked as Passed.\n", stage);
        } else if (result[0] == 'F' || result[0] == 'f') {
            trainingResults[index] = 'F';
            printf("Stage %d marked as Failed.\n", stage);
        } else {
            printf("Invalid result. Returning to menu.\n");
        }
    } else {
        printf("Returning to Training Menu.\n");
    }
}
