#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to store student information
struct Student {
    string name;
    string role;
    int score;
};

// Compare students by skill score (descending order)
bool compareScore(Student a, Student b) {
    return a.score > b.score;
}

// Search students by their role
void searchByRole(vector<Student>& students, string role) {
    cout << "\nStudents for role: " << role << "\n";

    bool found = false;

    for (auto &s : students) {
        if (s.role == role) {
            cout << "Name: " << s.name
                 << " | Score: " << s.score << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No student found for this role.\n";
    }
}

int main() {

    int n;

    cout << "Enter number of students: ";
    cin >> n;

    vector<Student> students(n);

    // Input student details
    for (int i = 0; i < n; i++) {

        cout << "\nStudent " << i + 1 << ":\n";

        cout << "Name: ";
        cin >> students[i].name;

        cout << "Role (Backend/UIUX/Database/DSA): ";
        cin >> students[i].role;

        cout << "Skill Score (0-100): ";
        cin >> students[i].score;
    }

    // Sort students by skill score
    sort(students.begin(), students.end(), compareScore);

    // Display sorted students
    cout << "\n--- Students Sorted by Skill Score ---\n";

    for (auto &s : students) {
        cout << s.name << " | "
             << s.role << " | "
             << s.score << "\n";
    }
}
    // Search student by