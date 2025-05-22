#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Added for strcspn

// Structure to store candidate information
struct Candidate {
    char name[50];
    char dob[9]; // Format: YYYYMMDD
    char gender;
    char email[50];
    char nationality[50];
    float bmi;
    char primary_skill[20];
    char secondary_skill[20];
    int korean_level;
    char mbti[5];
    char introduction[200];
};

int main() {
    // Variables
    struct Candidate candidates[6]; // Array for 6 candidates
    char group_name[50];
    int i = 0;
    char temp_dob[11];
    
    // Get group name
    printf("Enter the audition group name (e.g., Milliways): ");
    fgets(group_name, 50, stdin);
    group_name[strcspn(group_name, "\n")] = '\0'; // Remove newline
    
    // Input screen
    printf("\n####################################\n");
    printf("     [%s] Audition Candidate Data Entry\n", group_name);
    printf("####################################\n");
    
    // Input data for each candidate
    while (i < 6) {
        printf("\nEntering information for candidate %d\n", i+1);
        printf("---------------------------------\n");
        
        // Name
        printf("1. Name: ");
        fgets(candidates[i].name, 50, stdin);
        candidates[i].name[strcspn(candidates[i].name, "\n")] = '\0';
        
        // Date of Birth
        printf("2. Date of Birth (YYYY/MM/DD format): ");
        fgets(temp_dob, 11, stdin);
        temp_dob[strcspn(temp_dob, "\n")] = '\0';
        // Convert to YYYYMMDD format
        sprintf(candidates[i].dob, "%.4s%.2s%.2s", temp_dob, temp_dob+5, temp_dob+8);
        
        // Gender
        printf("3. Gender (F for Female, M for Male): ");
        scanf(" %c", &candidates[i].gender);
        while(getchar() != '\n'); // Clear input buffer
        
        // Email
        printf("4. Email: ");
        fgets(candidates[i].email, 50, stdin);
        candidates[i].email[strcspn(candidates[i].email, "\n")] = '\0';
        
        // Nationality
        printf("5. Nationality: ");
        fgets(candidates[i].nationality, 50, stdin);
        candidates[i].nationality[strcspn(candidates[i].nationality, "\n")] = '\0';
        
        // BMI
        printf("6. BMI: ");
        scanf("%f", &candidates[i].bmi);
        while(getchar() != '\n'); // Clear input buffer
        
        // Primary Skill
        printf("7. Primary Skill: ");
        fgets(candidates[i].primary_skill, 20, stdin);
        candidates[i].primary_skill[strcspn(candidates[i].primary_skill, "\n")] = '\0';
        
        // Secondary Skill
        printf("8. Secondary Skill: ");
        fgets(candidates[i].secondary_skill, 20, stdin);
        candidates[i].secondary_skill[strcspn(candidates[i].secondary_skill, "\n")] = '\0';
        
        // Korean Level
        printf("9. Korean Proficiency Level (0-4): ");
        scanf("%d", &candidates[i].korean_level);
        while(getchar() != '\n'); // Clear input buffer
        
        // MBTI
        printf("10. MBTI: ");
        fgets(candidates[i].mbti, 5, stdin);
        candidates[i].mbti[strcspn(candidates[i].mbti, "\n")] = '\0';
        
        // Introduction
        printf("11. Introduction: ");
        fgets(candidates[i].introduction, 200, stdin);
        candidates[i].introduction[strcspn(candidates[i].introduction, "\n")] = '\0';
        
        printf("=================================\n");
        i++; // Move to next candidate
    }
    
    // Display screen
    printf("\n####################################\n");
    printf("     [%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    
    // Table header
    printf("=============================================================================================\n");
    printf("Name          | DOB       | Gender | Email                 | Nationality | BMI  | Primary Skill | Secondary Skill | TOPIK | MBTI |\n");
    printf("=============================================================================================\n");
    
    // Display each candidate's information
    for (i = 0; i < 6; i++) {
        // Calculate age (simplified - assumes current year is 2023)
        int birth_year;
        sscanf(candidates[i].dob, "%4d", &birth_year);
        int age = 2023 - birth_year;
        
        // Print name with age
        char name_with_age[60];
        sprintf(name_with_age, "%s (%d)", candidates[i].name, age);
        printf("%-18s | %-8s | %-6c | %-20s | %-11s | %-4.1f | %-13s | %-15s | ",
               name_with_age, candidates[i].dob, candidates[i].gender, candidates[i].email,
               candidates[i].nationality, candidates[i].bmi,
               candidates[i].primary_skill, candidates[i].secondary_skill);
        
        // Print Korean level
        switch(candidates[i].korean_level) {
            case 0: printf("Native  | "); break;
            case 1: printf("Level 1 | "); break;
            case 2: printf("Level 2 | "); break;
            case 3: printf("Level 3 | "); break;
            case 4: printf("Level 4 | "); break;
            default: printf("Unknown | ");
        }
        
        // Print MBTI
        printf("%-4s |\n", candidates[i].mbti);
        
        // Print introduction
        printf("-------------------------------------------------------------------------------------\n");
        printf("%-80s     |\n", candidates[i].introduction);
        printf("---------------------------------------------------------------------------------------------\n");
    }
    
    return 0;
}
