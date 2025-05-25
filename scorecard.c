#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Candidate structure to store name and ID
typedef struct {
    char name[50];
    int id;
} Candidate;

// Judge structure to store judge information
typedef struct {
    char name[50];
    char expertise[20];
} Judge;

// Score sheet structure for each candidate
typedef struct {
    int judgeId;
    int music;
    int dance;
    int vocal;
    int visual;
    int expression;
    int total;
} ScoreSheet;

// Function prototypes
void initializeCandidates(Candidate candidates[]);
void inputJudgeInfo(Judge *judge);
void inputScores(ScoreSheet scores[], Candidate candidates[], Judge judge);
void reviewScores(ScoreSheet scores[], Candidate candidates[]);
bool confirmSubmission();
void modifyScores(ScoreSheet scores[], Candidate candidates[]);
void calculateTotals(ScoreSheet scores[]);
void displayFinalResults(ScoreSheet scores[], Candidate candidates[]);

int main() {
    // Initialize candidates
    Candidate candidates[6];
    initializeCandidates(candidates);
    
    // Judge information
    Judge judge;
    inputJudgeInfo(&judge);
    
    // Score sheets for each candidate
    ScoreSheet scores[6];
    
    bool submitted = false;
    while (!submitted) {
        // Input scores
        inputScores(scores, candidates, judge);
        
        // Review and confirm
        reviewScores(scores, candidates);
        submitted = confirmSubmission();
        
        if (!submitted) {
            // Allow modifications
            modifyScores(scores, candidates);
        }
    }
    
    printf("***Final submission completed.***\n");
    
    // Calculate totals and display results (bonus feature)
    calculateTotals(scores);
    displayFinalResults(scores, candidates);
    
    return 0;
}

// Initialize candidate data
void initializeCandidates(Candidate candidates[]) {
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
    
    strcpy(candidates[5].name, "Takeshi Yamamoto");
    candidates[5].id = 100006;
}

// Input judge information
void inputJudgeInfo(Judge *judge) {
    printf("####################################\n");
    printf("#     Audition Evaluation Entry    #\n");
    printf("####################################\n");
    
    printf("> Judge Name: ");
    fgets(judge->name, 50, stdin);
    judge->name[strcspn(judge->name, "\n")] = '\0'; // Remove newline
    
    printf("> Expertise: ");
    fgets(judge->expertise, 20, stdin);
    judge->expertise[strcspn(judge->expertise, "\n")] = '\0'; // Remove newline
    
    printf("++++++++++++++++++++++++++++++++++++\n");
}

// Input scores for all candidates
void inputScores(ScoreSheet scores[], Candidate candidates[], Judge judge) {
    for (int i = 0; i < 6; i++) {
        printf("Candidate: %s\n", candidates[i].name);
        
        // Store judge ID (using first letter of name as simple ID)
        scores[i].judgeId = judge.name[0];
        
        // Input scores with validation
        do {
            printf("%s Proficiency: ", judge.expertise);
            scanf("%d", &scores[i].music);
        } while (scores[i].music < 10 || scores[i].music > 100);
        
        do {
            printf("Dance: ");
            scanf("%d", &scores[i].dance);
        } while (scores[i].dance < 10 || scores[i].dance > 100);
        
        do {
            printf("Vocal: ");
            scanf("%d", &scores[i].vocal);
        } while (scores[i].vocal < 10 || scores[i].vocal > 100);
        
        do {
            printf("Visual: ");
            scanf("%d", &scores[i].visual);
        } while (scores[i].visual < 10 || scores[i].visual > 100);
        
        do {
            printf("Expression: ");
            scanf("%d", &scores[i].expression);
        } while (scores[i].expression < 10 || scores[i].expression > 100);
        
        printf("------------------------------------\n");
        getchar(); // Consume newline
    }
}

// Review all entered scores
void reviewScores(ScoreSheet scores[], Candidate candidates[]) {
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Submission completed.\n");
    printf("Please review your input!\n");
    printf("------------------------------------\n");
    
    for (int i = 0; i < 6; i++) {
        printf("%s: %d %d %d %d %d\n", 
               candidates[i].name, 
               scores[i].music, 
               scores[i].dance, 
               scores[i].vocal, 
               scores[i].visual, 
               scores[i].expression);
    }
}

// Confirm submission
bool confirmSubmission() {
    char choice;
    printf("Would you like to submit? (Y/N) ");
    scanf(" %c", &choice);
    getchar(); // Consume newline
    
    return (choice == 'Y' || choice == 'y');
}

// Modify scores if needed
void modifyScores(ScoreSheet scores[], Candidate candidates[]) {
    char name[50];
    int id;
    bool found = false;
    int index = -1;
    
    do {
        printf("Enter candidate name to modify: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove newline
        
        printf("Enter candidate ID (6 digits): ");
        scanf("%d", &id);
        getchar(); // Consume newline
        
        // Find candidate
        for (int i = 0; i < 6; i++) {
            if (strcmp(candidates[i].name, name) == 0 && candidates[i].id == id) {
                found = true;
                index = i;
                break;
            }
        }
        
        if (!found) {
            printf("Candidate not found. Please try again.\n");
        }
    } while (!found);
    
    // Modify scores for found candidate
    printf("Modifying scores for %s:\n", candidates[index].name);
    
    do {
        printf("Music Proficiency: ");
        scanf("%d", &scores[index].music);
    } while (scores[index].music < 10 || scores[index].music > 100);
    
    do {
        printf("Dance: ");
        scanf("%d", &scores[index].dance);
    } while (scores[index].dance < 10 || scores[index].dance > 100);
    
    do {
        printf("Vocal: ");
        scanf("%d", &scores[index].vocal);
    } while (scores[index].vocal < 10 || scores[index].vocal > 100);
    
    do {
        printf("Visual: ");
        scanf("%d", &scores[index].visual);
    } while (scores[index].visual < 10 || scores[index].visual > 100);
    
    do {
        printf("Expression: ");
        scanf("%d", &scores[index].expression);
    } while (scores[index].expression < 10 || scores[index].expression > 100);
    
    getchar(); // Consume newline
}

// Calculate total scores
void calculateTotals(ScoreSheet scores[]) {
    for (int i = 0; i < 6; i++) {
        scores[i].total = scores[i].music + scores[i].dance + scores[i].vocal + 
                         scores[i].visual + scores[i].expression;
    }
}

// Display final results with top 4 candidates
void displayFinalResults(ScoreSheet scores[], Candidate candidates[]) {
    // Simple sorting by total score (bubble sort)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            if (scores[j].total < scores[j+1].total) {
                // Swap scores
                ScoreSheet temp = scores[j];
                scores[j] = scores[j+1];
                scores[j+1] = temp;
                
                // Swap candidates
                Candidate tempC = candidates[j];
                candidates[j] = candidates[j+1];
                candidates[j+1] = tempC;
            }
        }
    }
    
    printf("=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");
    
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i+1, candidates[i].name);
    }
    printf("\n");
}
