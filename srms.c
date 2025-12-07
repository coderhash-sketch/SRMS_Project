#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"
#define MAX_NAME 50
#define MAX_ADDRESS 100

// Student structure with 10+ fields
typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    char gender;
    char address[MAX_ADDRESS];
    char phone[15];
    char email[MAX_NAME];
    float math;
    float physics;
    float chemistry;
    float english;
    float computer;
    float total;
    float percentage;
    char grade;
} Student;

// Function prototypes
void menu();
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void calculateMarks(Student *s);
char calculateGrade(float percentage);
void displayStudent(Student s);
int getNextId();

int main() {
    int choice;
    
    printf("\n========================================\n");
    printf("   STUDENT RECORD MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    
    while(1) {
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    
    return 0;
}

void menu() {
    printf("\n========================================\n");
    printf("              MAIN MENU\n");
    printf("========================================\n");
    printf("1. Add New Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student by ID\n");
    printf("4. Update Student Record\n");
    printf("5. Delete Student Record\n");
    printf("6. Exit\n");
    printf("========================================\n");
}

void addStudent() {
    Student s;
    FILE *fp;
    
    fp = fopen(FILENAME, "ab");
    if(fp == NULL) {
        printf("\nError opening file!\n");
        return;
    }
    
    printf("\n--- ADD NEW STUDENT ---\n");
    
    s.id = getNextId();
    printf("Student ID (Auto-generated): %d\n", s.id);
    
    printf("Enter Name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0; // Remove newline
    
    printf("Enter Age: ");
    scanf("%d", &s.age);
    getchar();
    
    printf("Enter Gender (M/F): ");
    scanf("%c", &s.gender);
    getchar();
    
    printf("Enter Address: ");
    fgets(s.address, MAX_ADDRESS, stdin);
    s.address[strcspn(s.address, "\n")] = 0;
    
    printf("Enter Phone Number: ");
    fgets(s.phone, 15, stdin);
    s.phone[strcspn(s.phone, "\n")] = 0;
    
    printf("Enter Email: ");
    fgets(s.email, MAX_NAME, stdin);
    s.email[strcspn(s.email, "\n")] = 0;
    
    printf("\n--- ENTER MARKS (out of 100) ---\n");
    printf("Mathematics: ");
    scanf("%f", &s.math);
    printf("Physics: ");
    scanf("%f", &s.physics);
    printf("Chemistry: ");
    scanf("%f", &s.chemistry);
    printf("English: ");
    scanf("%f", &s.english);
    printf("Computer Science: ");
    scanf("%f", &s.computer);
    
    calculateMarks(&s);
    
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    
    printf("\n*** Student record added successfully! ***\n");
    printf("Total: %.2f | Percentage: %.2f%% | Grade: %c\n", 
           s.total, s.percentage, s.grade);
}

void displayAllStudents() {
    Student s;
    FILE *fp;
    int count = 0;
    
    fp = fopen(FILENAME, "rb");
    if(fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("        ALL STUDENT RECORDS\n");
    printf("========================================\n");
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        displayStudent(s);
        count++;
        printf("----------------------------------------\n");
    }
    
    fclose(fp);
    
    if(count == 0) {
        printf("No records found!\n");
    } else {
        printf("\nTotal Students: %d\n", count);
    }
}

void searchStudent() {
    Student s;
    FILE *fp;
    int id, found = 0;
    
    fp = fopen(FILENAME, "rb");
    if(fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.id == id) {
            printf("\n--- STUDENT FOUND ---\n");
            displayStudent(s);
            found = 1;
            break;
        }
    }
    
    fclose(fp);
    
    if(!found) {
        printf("\nStudent with ID %d not found!\n", id);
    }
}

void updateStudent() {
    Student s;
    FILE *fp, *temp;
    int id, found = 0;
    
    fp = fopen(FILENAME, "rb");
    temp = fopen("temp.dat", "wb");
    
    if(fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);
    getchar();
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.id == id) {
            found = 1;
            printf("\n--- CURRENT RECORD ---\n");
            displayStudent(s);
            
            printf("\n--- ENTER NEW DETAILS ---\n");
            printf("Enter Name: ");
            fgets(s.name, MAX_NAME, stdin);
            s.name[strcspn(s.name, "\n")] = 0;
            
            printf("Enter Age: ");
            scanf("%d", &s.age);
            getchar();
            
            printf("Enter Gender (M/F): ");
            scanf("%c", &s.gender);
            getchar();
            
            printf("Enter Address: ");
            fgets(s.address, MAX_ADDRESS, stdin);
            s.address[strcspn(s.address, "\n")] = 0;
            
            printf("Enter Phone Number: ");
            fgets(s.phone, 15, stdin);
            s.phone[strcspn(s.phone, "\n")] = 0;
            
            printf("Enter Email: ");
            fgets(s.email, MAX_NAME, stdin);
            s.email[strcspn(s.email, "\n")] = 0;
            
            printf("\n--- ENTER MARKS ---\n");
            printf("Mathematics: ");
            scanf("%f", &s.math);
            printf("Physics: ");
            scanf("%f", &s.physics);
            printf("Chemistry: ");
            scanf("%f", &s.chemistry);
            printf("English: ");
            scanf("%f", &s.english);
            printf("Computer Science: ");
            scanf("%f", &s.computer);       
            
            calculateMarks(&s);
            printf("\n*** Record updated successfully! ***\n");
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }
    
    fclose(fp);
    fclose(temp);
    
    remove(FILENAME);
    rename("temp.dat", FILENAME);
    
    if(!found) {
        printf("\nStudent with ID %d not found!\n", id);
    }
}

void deleteStudent() {
    Student s;
    FILE *fp, *temp;
    int id, found = 0;
    
    fp = fopen(FILENAME, "rb");
    temp = fopen("temp.dat", "wb");
    
    if(fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.id == id) {
            found = 1;
            printf("\n--- DELETED RECORD ---\n");
            displayStudent(s);
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }
    
    fclose(fp);
    fclose(temp);
    
    remove(FILENAME);
    rename("temp.dat", FILENAME);
    
    if(found) {
        printf("\n*** Record deleted successfully! ***\n");
    } else {
        printf("\nStudent with ID %d not found!\n", id);
    }
}

void calculateMarks(Student *s) {
    s->total = s->math + s->physics + s->chemistry + s->english + s->computer;
    s->percentage = (s->total / 500.0) * 100.0;
    s->grade = calculateGrade(s->percentage);
}

char calculateGrade(float percentage) {
    if(percentage >= 90) return 'A';
    else if(percentage >= 80) return 'B';
    else if(percentage >= 70) return 'C';
    else if(percentage >= 60) return 'D';
    else if(percentage >= 50) return 'E';
    else return 'F';
}

void displayStudent(Student s) {
    printf("\nID: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Age: %d\n", s.age);
    printf("Gender: %c\n", s.gender);
    printf("Address: %s\n", s.address);
    printf("Phone: %s\n", s.phone);
    printf("Email: %s\n", s.email);
    printf("\n--- MARKS ---\n");
    printf("Mathematics: %.2f\n", s.math);
    printf("Physics: %.2f\n", s.physics);
    printf("Chemistry: %.2f\n", s.chemistry);
    printf("English: %.2f\n", s.english);
    printf("Computer Science: %.2f\n", s.computer);
    printf("\n--- PERFORMANCE ---\n");
    printf("Total: %.2f/500\n", s.total);
    printf("Percentage: %.2f%%\n", s.percentage);
    printf("Grade: %c\n", s.grade);
}

int getNextId() {
    Student s;
    FILE *fp;
    int maxId = 0;
    
    fp = fopen(FILENAME, "rb");
    if(fp == NULL) {
        return 1; // First student
    }
    
    while(fread(&s, sizeof(Student), 1, fp)) {
        if(s.id > maxId) {
            maxId = s.id;
        }
    }
    
    fclose(fp);
    return maxId + 1;       
}