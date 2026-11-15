#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50

// Structure for Student Profile
struct Student {
    int id;
    char name[50];
    char skills[50];
    char role[50];
};

// Function to add student
void addStudent(struct Student s[], int *n) {
    printf("Enter Student ID: ");
    scanf("%d", &s[*n].id);
    printf("Enter Name: ");
    scanf("%s", s[*n].name);
    printf("Enter Skills: ");
    scanf("%s", s[*n].skills);
    printf("Enter Role: ");
    scanf("%s", s[*n].role);
    (*n)++;
}

// Function to display students
void displayStudents(struct Student s[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nID: %d | Name: %s | Skills: %s | Role: %s\n",
               s[i].id, s[i].name, s[i].skills, s[i].role);
    }
}

// Function to search student by ID
void searchStudent(struct Student s[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (s[i].id == id) {
            printf("Found: %s with skill %s\n", s[i].name, s[i].skills);
            return;
        }
    }
    printf("Student not found.\n");
}

int main() {
    struct Student s[MAX_STUDENTS];
    int n = 0, choice, id;

    do {
        printf("\n--- CampusConnect (C Version) ---\n");
        printf("1. Add Student\n2. Display Students\n3. Search Student\n0. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) addStudent(s, &n);
        else if (choice == 2) displayStudents(s, n);
        else if (choice == 3) {
            printf("Enter ID: "); scanf("%d", &id);
            searchStudent(s, n, id);
        }
    } while (choice != 0);

    return 0;
}
