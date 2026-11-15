
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstring>
using namespace std;

#define MAX_STUDENTS 100
#define MAX_SKILLS 10
#define MAX_DAYS 7
#define TEXT 64
#define MAX_ROLES 4

/* Same data structures are declared here so C++ can call the C functions. */

struct Student {
    int id;
    char name[TEXT], domain[TEXT], preferredRole[TEXT];
    int experience;
    char skills[MAX_SKILLS][TEXT];
    int skillCount;
    char days[MAX_DAYS][TEXT];
    int dayCount;
};

struct Role {
    char name[TEXT], domain[TEXT];
    char skills[MAX_SKILLS][TEXT];
    int skillCount;
};

struct Recommendation {
    int index, score;
};

extern "C" {
    void loadSampleStudents(Student students[], int *count);

    int addStudent(Student students[], int *count, Student s);

    void displayStudents(const Student students[], int count);

    int calculateScore(const Student *s, const Role *r);

    int recommendStudents(const Student students[], int count,
                          const Role *role,
                          Recommendation output[], int limit);

    int shareAvailability(const Student *a, const Student *b);

    void showCommonAvailability(const Student students[],
                                const int team[], int teamCount);

    int buildBalancedTeam(const Student students[], int studentCount,
                          const Role roles[], int roleCount, int team[]);

    void analyzeSkillGaps(const Student students[], const int team[],
                          int teamCount, const Role roles[], int roleCount);
}

Role roles[MAX_ROLES];

void copyText(char destination[TEXT], const char *source) {
    snprintf(destination, TEXT, "%s", source);
}

/* SETUP PROJECT ROLES */

void setupRoles() {
    memset(roles, 0, sizeof(roles));

    copyText(roles[0].name, "Backend Developer");
    copyText(roles[0].domain, "Web Development");

    const char *backend[] = {"Python", "REST API", "Django"};
    roles[0].skillCount = 3;

    for (int i = 0; i < 3; i++)
        copyText(roles[0].skills[i], backend[i]);


    copyText(roles[1].name, "UI/UX Designer");
    copyText(roles[1].domain, "Web Development");

    const char *design[] = {"UI/UX", "Figma"};
    roles[1].skillCount = 2;

    for (int i = 0; i < 2; i++)
        copyText(roles[1].skills[i], design[i]);


    copyText(roles[2].name, "Database Developer");
    copyText(roles[2].domain, "Database");

    const char *database[] = {"SQL", "MySQL", "Database"};
    roles[2].skillCount = 3;

    for (int i = 0; i < 3; i++)
        copyText(roles[2].skills[i], database[i]);


    copyText(roles[3].name, "DSA/Programming");
    copyText(roles[3].domain, "Software");

    const char *programming[] = {"C++", "DSA", "C"};
    roles[3].skillCount = 3;

    for (int i = 0; i < 3; i++)
        copyText(roles[3].skills[i], programming[i]);
}

/* INPUT VALIDATION */

int getNumber(const char *message) {
    int n;

    cout << message;

    while (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter a valid number: ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return n;
}

/* ADD NEW STUDENT */

void addNewStudent(Student students[], int &count) {
    Student s{};

    cout << "\n--- ADD STUDENT ---\n";

    s.id = getNumber("Student ID: ");

    cout << "Name: ";
    cin.getline(s.name, TEXT);

    cout << "Domain (Software/Web Development/Database/AI): ";
    cin.getline(s.domain, TEXT);

    cout << "Preferred role: ";
    cin.getline(s.preferredRole, TEXT);

    s.experience = getNumber(
        "Experience (0 Beginner, 1 Intermediate, 2 Advanced): ");

    if (s.experience < 0 || s.experience > 2)
        s.experience = 0;

    s.skillCount = getNumber("Number of skills (0-10): ");

    if (s.skillCount < 0)
        s.skillCount = 0;

    if (s.skillCount > MAX_SKILLS)
        s.skillCount = MAX_SKILLS;

    for (int i = 0; i < s.skillCount; i++) {
        cout << "Skill " << i + 1 << ": ";
        cin.getline(s.skills[i], TEXT);
    }

    s.dayCount = getNumber("Number of available days (0-7): ");

    if (s.dayCount < 0)
        s.dayCount = 0;

    if (s.dayCount > MAX_DAYS)
        s.dayCount = MAX_DAYS;

    cout << "Enter days like Mon, Tue, Wed.\n";

    for (int i = 0; i < s.dayCount; i++) {
        cout << "Day " << i + 1 << ": ";
        cin.getline(s.days[i], TEXT);
    }

    int result = addStudent(students, &count, s);

    if (result == 1)
        cout << "Student added successfully.\n";

    else if (result == -1)
        cout << "Student ID already exists.\n";

    else
        cout << "Student list is full.\n";
}

/* ROLE-BASED RECOMMENDATIONS */

void roleRecommendations(const Student students[], int count) {
    cout << "\nSelect role:\n";

    for (int i = 0; i < MAX_ROLES; i++)
        cout << i + 1 << ". " << roles[i].name << "\n";

    int choice = getNumber("Choice: ");

    if (choice < 1 || choice > MAX_ROLES) {
        cout << "Invalid role.\n";
        return;
    }

    Recommendation results[MAX_STUDENTS]{};

    int total = recommendStudents(
        students,
        count,
        &roles[choice - 1],
        results,
        MAX_STUDENTS
    );

    cout << "\nRecommendations for "
         << roles[choice - 1].name << "\n";

    for (int i = 0; i < total; i++) {
        const Student &s = students[results[i].index];

        cout << i + 1 << ". " << s.name
             << " (ID " << s.id << ")"
             << " - Match score: "
             << results[i].score << "%\n";
    }
}

/* DISPLAY BALANCED TEAM */

void printTeam(const Student students[], const int team[], int count) {
    cout << "\n--- BALANCED PROJECT TEAM ---\n";

    for (int i = 0; i < count; i++) {
        const Student &s = students[team[i]];

        cout << roles[i].name << " : "
             << s.name
             << " (ID: " << s.id << ")\n";
    }
}

/* MAIN FUNCTION */

int main() {
    Student students[MAX_STUDENTS]{};

    int studentCount = 0;

    int team[MAX_ROLES]{};

    int teamCount = 0;

    setupRoles();

    loadSampleStudents(students, &studentCount);

    cout << "========================================\n";
    cout << "             CAMPUS CONNECT             \n";
    cout << " Student Project Team Recommendation    \n";
    cout << "========================================\n";

    int choice;

    do {
        cout << "\n--------------- MAIN MENU ---------------\n";

        cout << "1. View student profiles\n";
        cout << "2. Add student profile\n";
        cout << "3. Role-based recommendations\n";
        cout << "4. Build balanced project team\n";
        cout << "5. Analyze skill gaps\n";
        cout << "6. Check common availability\n";
        cout << "0. Exit\n";

        cout << "-----------------------------------------\n";

        choice = getNumber("Enter your choice: ");

        switch (choice) {

            case 1:
                displayStudents(students, studentCount);
                break;

            case 2:
                addNewStudent(students, studentCount);
                break;

            case 3:
                roleRecommendations(students, studentCount);
                break;

            case 4:
                teamCount = buildBalancedTeam(
                    students,
                    studentCount,
                    roles,
                    MAX_ROLES,
                    team
                );

                printTeam(students, team, teamCount);
                break;

            case 5:
                analyzeSkillGaps(
                    students,
                    team,
                    teamCount,
                    roles,
                    MAX_ROLES
                );
                break;

            case 6:
                showCommonAvailability(
                    students,
                    team,
                    teamCount
                );
                break;

            case 0:
                cout << "Thank you for using CampusConnect!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
