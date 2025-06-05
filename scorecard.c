#include <stdio.h>
#include <string.h>

// Define the number of candidates and judges
#define NUM_CANDIDATES 6
#define NUM_JUDGES 5

// Structure to store candidate information
struct Candidate {
    char name[50];
    int id;
};

// Structure to store judge information
struct Judge {
    char name[50];
    char expertise[20];
};

// Structure to store scores
struct Score {
    int value;
};

// Global arrays
struct Candidate candidates[NUM_CANDIDATES];
struct Judge judges[NUM_JUDGES];
struct Score scores[NUM_JUDGES][NUM_CANDIDATES];

// Function to set up initial data
void setup_data() {
    // Set up candidates
    strcpy(candidates[0].name, "Jiyeon Park");
    candidates[0].id = 100001;
    strcpy(candidates[1].name, "Ethan Smith");
    candidates[1].id = 100002;
    strcpy(candidates[2].name, "Helena Silva");
    candidates[2].id = 100003;
    strcpy(candidates[3].name, "Liam Wilson");
    candidates[3].id = 100004;
    strcpy(candidates[4].name, "Aisha Khan");
    candidates[4].id = 100005;
    strcpy(candidates[5].name, "Oliver Chen");
    candidates[5].id = 100006;

    // Set up judges
    strcpy(judges[0].name, "Youngsoo Kim");
    strcpy(judges[0].expertise, "Music");
    strcpy(judges[1].name, "Sophia Lee");
    strcpy(judges[1].expertise, "Dance");
    strcpy(judges[2].name, "David Park");
    strcpy(judges[2].expertise, "Vocal");
    strcpy(judges[3].name, "Emma Johnson");
    strcpy(judges[3].expertise, "Visual");
    strcpy(judges[4].name, "Michael Brown");
    strcpy(judges[4].expertise, "Expression");
}

// Function to get a valid score between 10 and 100
int get_valid_score() {
    int score;
    while (1) {
        scanf("%d", &score);
        if (score >= 10 && score <= 100) {
            return score;
        }
        printf("Invalid score! Please enter between 10 and 100: ");
    }
}

// Function to show all scores entered by a judge
void show_scores(int judge_num) {
    printf("\n++++++++++++++++++++++++++++++++++++\n");
    printf("Submission completed.\n");
    printf("Please review your input!\n");
    printf("------------------------------------\n");
    
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: %d\n", candidates[i].name, scores[judge_num][i].value);
    }
    
    printf("------------------------------------\n");
}

// Function to modify scores if needed
void change_scores(int judge_num) {
    char choice;
    printf("Do you want to change any scores? (Y/N): ");
    scanf(" %c", &choice);
    
    if (choice == 'Y' || choice == 'y') {
        char name[50];
        int id, found = 0;
        
        printf("Enter candidate name to change: ");
        scanf(" %[^\n]", name);
        printf("Enter candidate ID: ");
        scanf("%d", &id);
        
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            if (strcmp(candidates[i].name, name) == 0 && candidates[i].id == id) {
                printf("Enter new score for %s: ", name);
                scores[judge_num][i].value = get_valid_score();
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("Candidate not found!\n");
        }
        
        // Show updated scores
        show_scores(judge_num);
    }
}

// Function to calculate final results
void show_results() {
    int total[NUM_CANDIDATES] = {0};
    
    // Add up all scores from all judges
    for (int i = 0; i < NUM_JUDGES; i++) {
        for (int j = 0; j < NUM_CANDIDATES; j++) {
            total[j] += scores[i][j].value;
        }
    }
    
    // Simple sorting to find top 4
    int top_scores[4] = {0};
    char *top_names[4] = {0};
    
    for (int i = 0; i < 4; i++) {
        int max = 0;
        int max_index = 0;
        
        for (int j = 0; j < NUM_CANDIDATES; j++) {
            if (total[j] > max) {
                max = total[j];
                max_index = j;
            }
        }
        
        top_scores[i] = max;
        top_names[i] = candidates[max_index].name;
        total[max_index] = -1; // Mark as already selected
    }
    
    // Display results
    printf("\n=======================================\n");
    printf("Final Selection Results:\n");
    printf("=======================================\n");
    printf("Top 4 Candidates:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i+1, top_names[i]);
    }
}

// Main function
int main() {
    setup_data();
    
    // Each judge enters scores
    for (int j = 0; j < NUM_JUDGES; j++) {
        printf("\n####################################\n");
        printf("#     Audition Evaluation Entry    #\n");
        printf("####################################\n");
        printf("Judge: %s (%s)\n", judges[j].name, judges[j].expertise);
        printf("++++++++++++++++++++++++++++++++++++\n");
        
        // Enter scores for each candidate
        for (int c = 0; c < NUM_CANDIDATES; c++) {
            printf("Candidate: %s\n", candidates[c].name);
            printf("Enter score (10-100): ");
            scores[j][c].value = get_valid_score();
            printf("------------------------------------\n");
        }
        
        // Show and confirm scores
        show_scores(j);
        change_scores(j);
    }
    
    // Show final results
    show_results();
    
    return 0;
}
