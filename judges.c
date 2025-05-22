#include <stdio.h>
#include <string.h>

#define MAX_JUDGES 50

struct Judge {
    char name[50];
    char gender[10];
    char affiliation[50];
    char title[50];
    char expertise[50];
    char email[50];
    char phone[20];
};

int main() {
    char project[50];
    int num_judges, num_members;
    struct Judge judges[MAX_JUDGES];
    char choice;
    
    // Show header
    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");
    
    // Get project info
    printf("Participating Project: ");
    fgets(project, 50, stdin);
    project[strlen(project)-1] = '\0'; // Remove newline
    
    // Get number of judges
    while(1) {
        printf("Total Number of Judges: ");
        scanf("%d", &num_judges);
        getchar(); // Clear input
        
        if(num_judges > 0 && num_judges <= MAX_JUDGES) break;
        printf("Please enter between 1 and %d\n", MAX_JUDGES);
    }
    
    printf("Number of Selected Members: ");
    scanf("%d", &num_members);
    getchar(); // Clear input
    
    printf("\n++++++++++++++++++++++++++++++++++++\n");
    printf("Enter info for %d judges (one line each):\n", num_judges);
    printf("Format: Name, Gender, Affiliation, Title, Expertise, Email, Phone\n");
    printf("Example: Kim Young-Soo, Male, JYK Studio, Producer, Music, youngsu@outlook.com, 010-1234-5678\n");
    printf("++++++++++++++++++++++++++++++++++++\n\n");
    
    // Input judge data
    for(int i = 0; i < num_judges; i++) {
        printf("Judge %d: ", i+1);
        
        char input[200];
        fgets(input, 200, stdin);
        input[strlen(input)-1] = '\0'; // Remove newline
        
        // Try to parse all fields
        int parsed = sscanf(input, "%49[^,], %9[^,], %49[^,], %49[^,], %49[^,], %49[^,], %19[^\n]",
            judges[i].name,
            judges[i].gender,
            judges[i].affiliation,
            judges[i].title,
            judges[i].expertise,
            judges[i].email,
            judges[i].phone);
            
        // Check if all fields were entered
        if(parsed != 7) {
            printf("Missing information! Please enter all fields.\n");
            i--; // Try this judge again
            continue;
        }
    }
    
    printf("\n++++++++++++++++++++++++++++++++++++\n");
    printf("Data entry complete!\n");
    printf("++++++++++++++++++++++++++++++++++++\n");
    
    // Ask to review
    printf("\n[%s] Check judge info? (Y/N): ", project);
    scanf(" %c", &choice);
    
    if(choice == 'Y' || choice == 'y') {
        printf("\n####################################\n");
        printf("#        Judge Information        #\n");
        printf("####################################\n");
        
        for(int i = 0; i < num_judges; i++) {
            printf("\n[Judge %d]\n", i+1);
            printf("Name: %s\n", judges[i].name);
            printf("Gender: %s\n", judges[i].gender);
            printf("Affiliation: %s\n", judges[i].affiliation);
            printf("Title: %s\n", judges[i].title);
            printf("Expertise: %s\n", judges[i].expertise);
            printf("Email: %s\n", judges[i].email);
            printf("Phone: %s\n", judges[i].phone);
            printf("----------------------------\n");
        }
    }
    
    printf("\nProgram ended.\n");
    return 0;
}
