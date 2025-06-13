#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 5
#define TEST_COUNT 7
#define MAX_STAGE 8

// === Member Data ===
char *milliways_members[MAX_MEMBERS][2] = {
    {"Kim Hyekyung", "Hye"},
    {"Lee Goeun", "Gogo"},
    {"Choi Woncheol", "WC"},
    {"Park Youngjin", "Jin"},
    {"Arthur Dent", "Art"}
};

// === Health Test Names ===
char *test_names[TEST_COUNT] = {
    "1-Mile Run (min)",
    "100m Sprint (sec)",
    "30 Push-ups (min)",
    "50 Squats (min)",
    "50 Push-ups (min)",
    "400m Swim (min)",
    "Weightlifting (xBW)"
};

// === Health Scores [member][test] ===
float health_scores[MAX_MEMBERS][TEST_COUNT];

// === Training Results for 8 stages ===
char training_results[MAX_STAGE] = {'-', '-', '-', '-', '-', '-', '-', '-'};

// === Function Prototypes ===
void mainMenu();
void trainingMenu();
void debutMenu();
void handleTrainingStage(int stage);
void setHealth();
void getHealth();
void parseAndStoreHealthData(int memberIndex, char *input);

// === Main Function ===
int main() {
    mainMenu();
    return 0;
}

// === Main Menu ===
void mainMenu() {
    char input[10];

    while (1) {
        printf("\n==== Magrathea System ====\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("Enter your choice (I/II/III), or Q to quit: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '0' || input[0] == '\n') {
            printf("Exiting program.\n");
            break;
        } else if (input[0] == 'I' || input[0] == 'i') {
            printf("Audition Management is under construction.\n");
        } else if (input[0] == 'II' || input[0] == 'i') {
            trainingMenu();
        } else if (input[0] == 'I' || input[0] == 'i') {
            debutMenu();
        } else if (input[0] == 'I' || input[0] == 'i') {
            printf("Invalid input.\n");
        }
    }
}

// === Training Menu ===
void trainingMenu() {
    char input[10];

    while (1) {
        printf("\n==== Training Menu ====\n");
        printf("1. Physical Strength & Knowledge [%c]\n", training_results[0]);
        printf("2. Self-Management & Teamwork [%c]\n", training_results[1]);
        printf("3. Language & Pronunciation [%c]\n", training_results[2]);
        printf("4. Vocal [%c]\n", training_results[3]);
        printf("5. Dance [%c]\n", training_results[4]);
        printf("6. Visual & Image [%c]\n", training_results[5]);
        printf("7. Acting & Stage Performance [%c]\n", training_results[6]);
        printf("8. Fan Communication [%c]\n", training_results[7]);
        printf("Enter stage number (1-8), or Q to return: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '0' || input[0] == '\n') {
            break;
        }

        int stage = atoi(input);

        if (stage < 1 || stage > 8) {
            printf("Invalid stage number.\n");
            continue;
        }

        // Rule enforcement
        if (stage > 1 && training_results[0] != 'P') {
            printf("You must complete Stage 1 first.\n");
            continue;
        }
        if (stage > 2 && training_results[1] != 'P') {
            printf("You must complete Stage 2 first.\n");
            continue;
        }

        if (training_results[stage - 1] == 'P') {
            printf("Stage already completed with 'P'. Cannot re-select.\n");
            continue;
        }

        handleTrainingStage(stage);
    }
}

// === Handle Specific Stage ===
void handleTrainingStage(int stage) {
    char input[10];

    printf("\nStage %d selected.\n", stage);
    printf("Would you like to enter the evaluation result? (Y/N): ");
    fgets(input, sizeof(input), stdin);

    if (input[0] == 'Y' || input[0] == 'y') {
        if (stage == 1) {
            printf("A. Enter Fitness Data\n");
            printf("B. View Fitness Data\n");
            printf("Select option (A/B): ");
            fgets(input, sizeof(input), stdin);

            if (input[0] == 'A' || input[0] == 'a') {
                setHealth();
            } else if (input[0] == 'B' || input[0] == 'b') {
                getHealth();
            }
        }

        printf("Did you complete the training and pass the certification? (P/F): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'P' || input[0] == 'p') {
            training_results[stage - 1] = 'P';
            printf("Stage %d marked as PASSED.\n", stage);
        } else {
            training_results[stage - 1] = 'F';
            printf("Stage %d marked as FAILED.\n", stage);
        }
    } else {
        printf("Returning to training menu.\n");
    }
}

// === Set Health Data ===
void setHealth() {
    char input[256];
    int memberIndex;

    printf("\n== Enter Fitness Data ==\n");

    for (memberIndex = 0; memberIndex < MAX_MEMBERS; memberIndex++) {
        printf("\nMember: %s (%s)\n", milliways_members[memberIndex][0], milliways_members[memberIndex][1]);
        printf("Enter 7 comma-separated test results:\n");
        for (int j = 0; j < TEST_COUNT; j++) {
            printf("  %s\n", test_names[j]);
        }
        printf("Input: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        parseAndStoreHealthData(memberIndex, input);
    }

    printf("\nAll fitness data recorded successfully.\n");
}

// === Parse and Store Input ===
void parseAndStoreHealthData(int memberIndex, char *input) {
    char *token = strtok(input, ",");
    int i = 0;

    while (token != NULL && i < TEST_COUNT) {
        health_scores[memberIndex][i] = atof(token);
        token = strtok(NULL, ",");
        i++;
    }

    if (i < TEST_COUNT) {
        printf("Incomplete data. Expected %d values.\n", TEST_COUNT);
    }
}

// === Get Health Data ===
void getHealth() {
    char input[50];
    int i, j;

    printf("\n== View Fitness Data ==\n");
    printf("A. View All Data\n");
    printf("B. View by Member Nickname\n");
    printf("C. View Specific Test for Member\n");
    printf("Select option (A/B/C): ");
    fgets(input, sizeof(input), stdin);

    if (input[0] == 'A' || input[0] == 'a') {
        for (i = 0; i < MAX_MEMBERS; i++) {
            printf("\nMember: %s (%s)\n", milliways_members[i][0], milliways_members[i][1]);
            for (j = 0; j < TEST_COUNT; j++) {
                printf("  %s: %.2f\n", test_names[j], health_scores[i][j]);
            }
        }
    } else if (input[0] == 'B' || input[0] == 'b') {
        printf("Enter member nickname: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        for (i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(input, milliways_members[i][1]) == 0) {
                printf("\nMember: %s (%s)\n", milliways_members[i][0], milliways_members[i][1]);
                for (j = 0; j < TEST_COUNT; j++) {
                    printf("  %s: %.2f\n", test_names[j], health_scores[i][j]);
                }
                return;
            }
        }
        printf("Nickname not found.\n");
    } else if (input[0] == 'C' || input[0] == 'c') {
        printf("Enter member nickname: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        int found = -1;
        for (i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(input, milliways_members[i][1]) == 0) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            printf("Nickname not found.\n");
            return;
        }

        printf("Select test (1-7):\n");
        for (j = 0; j < TEST_COUNT; j++) {
            printf("%d. %s\n", j + 1, test_names[j]);
        }
        fgets(input, sizeof(input), stdin);
        int testIndex = atoi(input) - 1;

        if (testIndex >= 0 && testIndex < TEST_COUNT) {
            printf("\n%s (%s) - %s: %.2f\n",
                   milliways_members[found][0],
                   milliways_members[found][1],
                   test_names[testIndex],
                   health_scores[found][testIndex]);
        } else {
            printf("Invalid test number.\n");
        }
    } else {
        printf("Invalid selection.\n");
    }
}

// === Debut Menu Placeholder ===
void debutMenu() {
    printf("Debut menu is under construction.\n");
}
