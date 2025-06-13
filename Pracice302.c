#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_MEMBERS 8
#define DAYS 6
#define MAX_NAME 50
#define MAX_RESPONSES 3
#define MAX_RESPONSE_LEN 101

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

// Trauma management
typedef struct {
    char nickname[MAX_NAME];
    int age;
    char trauma[256];
} Trauma;

Trauma traumas[MAX_MEMBERS];
int trauma_count = 0;

typedef struct {
    int id;
    char question[256];
} CounselingQuestion;

CounselingQuestion questions[5] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

typedef struct {
    char nickname[MAX_NAME];
    char question[256];
    char response[MAX_RESPONSE_LEN];
} CounselingResponse;

CounselingResponse responses[MAX_MEMBERS * MAX_RESPONSES];
int response_count = 0;

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

// Trauma Management
void traumaInput() {
    char nick[MAX_NAME], trauma[256];
    while (1) {
        displayMembers();
        printf("Enter nickname to input trauma or type 'exit': ");
        fgets(nick, sizeof(nick), stdin);
        nick[strcspn(nick, "\n")] = 0;
        if (strcmp(nick, "exit") == 0) break;

        int found = 0;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(nick, milliways_members[i][1]) == 0) {
                printf("Enter trauma description: ");
                fgets(trauma, sizeof(trauma), stdin);
                trauma[strcspn(trauma, "\n")] = 0;
                traumas[trauma_count++] = (Trauma){ .age = 20, .trauma = "", .nickname = "" };
                strcpy(traumas[trauma_count - 1].nickname, nick);
                strcpy(traumas[trauma_count - 1].trauma, trauma);
                found = 1;
                break;
            }
        }
        found ? printf("Saved.\n") : printf("Nickname not found.\n");
    }
}

void counselingSession() {
    printf("\n--- Counseling Candidates ---\n");
    for (int i = 0; i < trauma_count; i++) {
        printf("%d. %s\n", i + 1, traumas[i].nickname);
    }
    printf("Select by number: ");
    int t;
    scanf("%d", &t);
    clearBuffer();
    if (t < 1 || t > trauma_count) return;
    t--;

    int used[5] = {0};
    for (int i = 0; i < MAX_RESPONSES; ) {
        int q = rand() % 5;
        if (used[q]) continue;
        used[q] = 1;

        char ans[MAX_RESPONSE_LEN];
        while (1) {
            printf("%s\n> ", questions[q].question);
            fgets(ans, sizeof(ans), stdin);
            ans[strcspn(ans, "\n")] = 0;
            if (strlen(ans) > 0 && strlen(ans) < MAX_RESPONSE_LEN) break;
            printf("Invalid. Retry.\n");
        }

        CounselingResponse cr;
        strcpy(cr.nickname, traumas[t].nickname);
        strcpy(cr.question, questions[q].question);
        strcpy(cr.response, ans);
        responses[response_count++] = cr;
        i++;
    }
    printf("Counseling complete for %s.\n", traumas[t].nickname);
}

void viewCounseling() {
    char nick[MAX_NAME];
    printf("Enter nickname to view session: ");
    fgets(nick, sizeof(nick), stdin);
    nick[strcspn(nick, "\n")] = 0;
    for (int i = 0; i < trauma_count; i++) {
        if (strcmp(nick, traumas[i].nickname) == 0) {
            printf("\nNickname: %s\nTrauma: %s\n", traumas[i].nickname, traumas[i].trauma);
            for (int j = 0; j < response_count; j++) {
                if (strcmp(nick, responses[j].nickname) == 0) {
                    printf("Q: %s\nA: %s\n", responses[j].question, responses[j].response);
                }
            }
            return;
        }
    }
    printf("Nickname not found.\n");
}

void overcomeTrauma() {
    while (1) {
        printf("\n[B. Trauma Management]\n");
        printf("1. Input Trauma\n2. Start Counseling\n3. View Session\n0. Back\n> ");
        char c;
        scanf(" %c", &c);
        clearBuffer();
        if (c == '0') break;
        else if (c == '1') traumaInput();
        else if (c == '2') counselingSession();
        else if (c == '3') viewCounseling();
    }
}

// Health Management
// (functions unchanged)

// Exercise Routine
// (functions unchanged)

// Mentoring
// (functions unchanged)

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
                printf("B. Trauma Management\n");
                printf("0. Back\n> ");
                char sub;
                scanf(" %c", &sub);
                clearBuffer();
                if (sub == '0') break;
                else if (sub == 'A' || sub == 'a') matchMentoring();
                else if (sub == 'B' || sub == 'b') overcomeTrauma();
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
