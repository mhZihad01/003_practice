#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 5
#define MAX_TESTS 7
#define MAX_ROUTINE_LEN 50
#define DAYS_PER_WEEK 6

char *milliways_members[MAX_MEMBERS][2] = {
    {"Goeun", "G"},
    {"Woncheol", "W"},
    {"Youngjin", "Y"},
    {"Hyekyung", "H"},
    {"Arthur", "A"}
};

char *test_names[MAX_TESTS] = {
    "1-Mile Running Test",
    "Speed Sprint",
    "Push-ups",
    "Squats",
    "Arm Strength",
    "Swimming",
    "Weightlifting"
};

char health_scores[MAX_MEMBERS][MAX_TESTS][10];
char *exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"},
    {"Push-ups", "Squats", NULL},
    {"Leg Press", "Leg Curl", NULL},
    {"Pull-ups", "Chin-ups", NULL},
    {"Plank", "Crunches", NULL}
};

char *day_names[DAYS_PER_WEEK] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

char member_routine[MAX_MEMBERS][DAYS_PER_WEEK][MAX_ROUTINE_LEN];

void printMemberList() {
    printf("\n=== Milliways Members ===\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s)\n", i + 1, milliways_members[i][0], milliways_members[i][1]);
    }
}

void setHealth() {
    char input[256];
    printMemberList();
    printf("Enter member number (1-%d): ", MAX_MEMBERS);
    fgets(input, sizeof(input), stdin);
    int idx = atoi(input) - 1;
    if (idx < 0 || idx >= MAX_MEMBERS) {
        printf("Invalid member index.\n");
        return;
    }

    printf("Enter 7 fitness test values (comma-separated): ");
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, ",");
    int i = 0;
    while (token != NULL && i < MAX_TESTS) {
        strncpy(health_scores[idx][i], token, sizeof(health_scores[idx][i]) - 1);
        health_scores[idx][i][strcspn(health_scores[idx][i], "\n")] = 0;
        token = strtok(NULL, ",");
        i++;
    }
    printf("Fitness data saved for %s.\n", milliways_members[idx][0]);
}

void getHealth() {
    char input[50];
    printf("Enter member nickname or 'all': ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "all") == 0) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("%s (%s):\n", milliways_members[i][0], milliways_members[i][1]);
            for (int j = 0; j < MAX_TESTS; j++) {
                printf("  %s: %s\n", test_names[j], health_scores[i][j]);
            }
        }
    } else {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(input, milliways_members[i][1]) == 0) {
                printf("%s (%s):\n", milliways_members[i][0], milliways_members[i][1]);
                for (int j = 0; j < MAX_TESTS; j++) {
                    printf("  %s: %s\n", test_names[j], health_scores[i][j]);
                }
                return;
            }
        }
        printf("Member not found.\n");
    }
}

void setExerciseRoutine() {
    char input[100];
    int i, day, memberIndex;

    printMemberList();
    printf("Enter member number to set routine (1-%d): ", MAX_MEMBERS);
    fgets(input, sizeof(input), stdin);
    memberIndex = atoi(input) - 1;

    if (memberIndex < 0 || memberIndex >= MAX_MEMBERS) {
        printf("Invalid member selection.\n");
        return;
    }

    int core_used = 0;

    for (day = 0; day < DAYS_PER_WEEK; day++) {
        printf("\n-- %s Routine for %s (%s) --\n", day_names[day],
               milliways_members[memberIndex][0],
               milliways_members[memberIndex][1]);

        printf("Choose at least one Cardio Exercise (0-2):\n");
        for (i = 0; i < 3; i++) {
            printf("  %d. %s\n", i, exercise_types[0][i]);
        }
        printf("Cardio Choice: ");
        fgets(input, sizeof(input), stdin);
        int cardio = atoi(input);
        if (cardio < 0 || cardio > 2) {
            printf("Invalid cardio input.\n");
            day--;
            continue;
        }

        printf("Choose one Strength/Core type:\n");
        printf("1. Full-body\n2. Lower-body\n3. Upper-body\n4. Core (Only once/week)\n");
        printf("Select type (1-4): ");
        fgets(input, sizeof(input), stdin);
        int strength_type = atoi(input);

        if (strength_type == 4 && core_used) {
            printf("Core already used this week.\n");
            day--;
            continue;
        }

        int selected = (strength_type == 4) ? 4 : strength_type;

        printf("Choose exercise (0 or 1):\n");
        for (i = 0; i < 2; i++) {
            if (exercise_types[selected][i])
                printf("  %d. %s\n", i, exercise_types[selected][i]);
        }

        fgets(input, sizeof(input), stdin);
        int strength_ex = atoi(input);
        if (strength_ex < 0 || strength_ex > 1) {
            printf("Invalid strength choice.\n");
            day--;
            continue;
        }

        if (strength_type == 4) core_used = 1;

        snprintf(member_routine[memberIndex][day], MAX_ROUTINE_LEN,
                 "%s + %s",
                 exercise_types[0][cardio],
                 exercise_types[selected][strength_ex]);

        printf("Saved: %s\n", member_routine[memberIndex][day]);
    }
    printf("Workout routine set for %s.\n", milliways_members[memberIndex][0]);
}

void getExerciseRoutine() {
    char input[100];
    int memberIndex = -1;

    printMemberList();
    printf("Enter member name to view routine: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(input, milliways_members[i][0]) == 0) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("\n=== Workout Routine for %s (%s) ===\n",
           milliways_members[memberIndex][0],
           milliways_members[memberIndex][1]);

    for (int day = 0; day < DAYS_PER_WEEK; day++) {
        printf("%s: %s\n", day_names[day], member_routine[memberIndex][day]);
    }
}

void trainingMenu() {
    char input[10];
    while (1) {
        printf("\n== Training Menu ==\n");
        printf("1. Physical Strength & Knowledge\n");
        printf("Select training stage or Q to quit: ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '0' || input[0] == '\n') break;
        if (input[0] == '1') {
            printf("\nA. Enter Fitness Data\nB. View Fitness Data\n");
            printf("C. Set Basic Workout Routine\nD. View Basic Workout Routine\n");
            printf("Select option (A-D): ");
            fgets(input, sizeof(input), stdin);
            if (input[0] == 'A' || input[0] == 'a') setHealth();
            else if (input[0] == 'B' || input[0] == 'b') getHealth();
            else if (input[0] == 'C' || input[0] == 'c') setExerciseRoutine();
            else if (input[0] == 'D' || input[0] == 'd') getExerciseRoutine();
        }
    }
}

int main() {
    char input[10];
    while (1) {
        printf("\n== Main Menu ==\n");
        printf("I. Audition Management\nII. Training\nIII. Debut\n");
        printf("Select menu or Q to quit: ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Q' || input[0] == 'q' || input[0] == '0' || input[0] == '\n') break;
        if (input[0] == 'I' || input[0] == 'i') printf("(Audition feature not implemented)\n");
        else if (input[0] == 'II' || input[0] == 'i') trainingMenu();
        else if (input[0] == 'I' || input[0] == 'i') printf("(Debut feature not implemented)\n");
    }
    return 0;
}
