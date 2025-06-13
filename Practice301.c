#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_MEMBERS 8
#define DAYS 6
#define MAX_NAME 50

// Milliways members data
char milliways_members[MAX_MEMBERS][2][MAX_NAME] = {
    {"Goeun", "Eun"},
    {"Woncheol", "Cheoly"},
    {"Youngjin", "Jin"},
    {"Hyekyung", "Kyun"},
    {"Arthur", "Art"},
    {"Minji", "Min"},
    {"Jisoo", "Soo"},
    {"Taeyong", "Tae"}
};

// Fitness data and routine arrays
float health_scores[MAX_MEMBERS][8];
char member_routine[MAX_MEMBERS][DAYS][MAX_NAME];

// Exercise types
const char* exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"},
    {"Push-ups", "Squats", ""},
    {"Leg Press", "Leg Curl", ""},
    {"Pull-ups", "Chin-ups", ""},
    {"Plank", "Crunches", ""}
};

// Mentor struct
typedef struct {
    int id;
    char name[MAX_NAME];
    int mentee_index;
} Mentor;

Mentor mentors[MAX_MEMBERS];
int mentor_count = 0;

// Utilities
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void displayMembers() {
    printf("\n--- Milliways Members ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("%d. %s (%s)\n", i + 1, milliways_members[i][0], milliways_members[i][1]);
    }
}

// Health Management
void setHealth() {
    displayMembers();
    printf("Enter member index to input fitness data (1-%d): ", MAX_MEMBERS);
    int idx;
    scanf("%d", &idx);
    clearBuffer();

    if (idx < 1 || idx > MAX_MEMBERS) return;
    idx--;

    printf("Enter 7 fitness values (comma-separated): ");
    char input[256];
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, ",");
    for (int i = 0; i < 7 && token; i++) {
        health_scores[idx][i] = atof(token);
        token = strtok(NULL, ",");
    }
    printf("Fitness data saved for %s.\n", milliways_members[idx][0]);
}

void getHealth() {
    displayMembers();
    printf("Enter member nickname to view fitness data: ");
    char nick[MAX_NAME];
    fgets(nick, sizeof(nick), stdin);
    nick[strcspn(nick, "\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(nick, milliways_members[i][1]) == 0) {
            printf("\nFitness Data for %s (%s):\n", milliways_members[i][0], milliways_members[i][1]);
            for (int j = 0; j < 7; j++) {
                printf("Test %d: %.2f\n", j + 1, health_scores[i][j]);
            }
            return;
        }
    }
    printf("Nickname not found.\n");
}

// Exercise Routine
void setExerciseRoutine() {
    displayMembers();
    printf("Enter member index to set routine: ");
    int idx;
    scanf("%d", &idx);
    clearBuffer();
    if (idx < 1 || idx > MAX_MEMBERS) return;
    idx--;

    printf("Select exercises for Mon to Sat (Cardio + Strength/Core; Core only once/week):\n");
    int coreUsed = 0;
    for (int d = 0; d < DAYS; d++) {
        printf("\nDay %d:\n", d + 1);
        int cardio, strength;

        printf("Choose Cardio (0:Running, 1:Cycling, 2:Fast Walking): ");
        scanf("%d", &cardio);
        clearBuffer();

        printf("Choose Strength/Core (1:Full-body, 2:Lower, 3:Upper, 4:Core): ");
        scanf("%d", &strength);
        clearBuffer();

        if (strength == 4) {
            if (coreUsed) {
                printf("Core already used this week. Choose another.\n");
                d--;
                continue;
            } else coreUsed = 1;
        }

        snprintf(member_routine[idx][d], MAX_NAME, "%s + %s",
                 exercise_types[0][cardio], exercise_types[strength][0]);
    }
    printf("Routine saved for %s.\n", milliways_members[idx][0]);
}

void getExerciseRoutine() {
    displayMembers();
    printf("Enter member name to view routine: ");
    char name[MAX_NAME];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(name, milliways_members[i][0]) == 0) {
            printf("\nWorkout Routine for %s (%s):\n", milliways_members[i][0], milliways_members[i][1]);
            for (int d = 0; d < DAYS; d++) {
                printf("Day %d: %s\n", d + 1, member_routine[i][d]);
            }
            return;
        }
    }
    printf("Member not found.\n");
}

// Mentoring
int parseIntMember(char* nick) {
    int sum = 0;
    for (int i = 0; nick[i]; i++) sum += nick[i];
    return sum;
}

int getRandomAbility() {
    return rand() % 901 + 100; // 100 to 1000
}

void initializeTrainees(int abilities[MAX_MEMBERS], int ids[MAX_MEMBERS]) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        ids[i] = parseIntMember(milliways_members[i][1]);
        abilities[i] = getRandomAbility();
    }
}

void inputMentors() {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        mentors[i].id = i + 1;
        printf("Enter mentor name for ID %d: ", i + 1);
        fgets(mentors[i].name, MAX_NAME, stdin);
        mentors[i].name[strcspn(mentors[i].name, "\n")] = 0;
    }
    mentor_count = MAX_MEMBERS;
}

void matchMentoring() {
    int ids[MAX_MEMBERS], abilities[MAX_MEMBERS];
    initializeTrainees(abilities, ids);
    inputMentors();

    for (int i = 0; i < MAX_MEMBERS; i++) {
        int match_id = (ids[i] % MAX_MEMBERS);
        mentors[match_id].mentee_index = i;
    }

    printf("\n--- Mentor Assignments ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Trainee %d: %s (%s) → Mentor %d: %s\n", i + 1,
               milliways_members[i][0], milliways_members[i][1],
               (ids[i] % MAX_MEMBERS) + 1,
               mentors[ids[i] % MAX_MEMBERS].name);
    }
}

// Menu
void trainingMenu() {
    while (1) {
        printf("\n[II. Training]\n");
        printf("1. Physical Strength & Knowledge\n");
        printf("2. Self-Management & Teamwork\n");
        printf("0. Back\n> ");
        char choice;
        scanf(" %c", &choice);
        clearBuffer();

        if (choice == '0') break;
        else if (choice == '1') {
            while (1) {
                printf("\n[1. Physical Strength & Knowledge]\n");
                printf("A. Enter Fitness Data\n");
                printf("B. View Fitness Data\n");
                printf("C. Set Basic Workout Routine\n");
                printf("D. View Basic Workout Routine\n");
                printf("0. Back\n> ");
                char sub;
                scanf(" %c", &sub);
                clearBuffer();

                if (sub == '0') break;
                else if (sub == 'A' || sub == 'a') setHealth();
                else if (sub == 'B' || sub == 'b') getHealth();
                else if (sub == 'C' || sub == 'c') setExerciseRoutine();
                else if (sub == 'D' || sub == 'd') getExerciseRoutine();
            }
        } else if (choice == '2') {
            while (1) {
                printf("\n[2. Self-Management & Teamwork]\n");
                printf("A. Mentoring\n");
                printf("0. Back\n> ");
                char sub;
                scanf(" %c", &sub);
                clearBuffer();
                if (sub == '0') break;
                else if (sub == 'A' || sub == 'a') matchMentoring();
            }
        }
    }
}

int main() {
    srand((unsigned) time(NULL));
    while (1) {
        printf("\nMain Menu\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("Q. Quit\n> ");
        char input;
        scanf(" %c", &input);
        clearBuffer();

        if (input == 'Q' || input == 'q' || input == '0') break;
        else if (input == 'I' || input == 'i') {
            printf("[Audition Management] - Feature coming soon.\n");
        } else if (input == 'II' || input == 'i') {
            trainingMenu();
        } else if (input == 'III' || input == 'i') {
            printf("[Debut] - Feature coming soon.\n");
        }
    }
    return 0;
}
