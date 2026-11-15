#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Student Profile Management
class Student {
public:
    int id;
    string name;
    string skills;
    string role;
};

// Team & Skill Gap Analysis
struct TeamMember {
    string name;
    vector<string> skills;
};

void addMember(vector<TeamMember>& team) {
    TeamMember member;
    int n;
    cout << "Enter student name: ";
    cin >> member.name;
    cout << "How many skills? "; cin >> n;
    for (int i = 0; i < n; i++) {
        string skill;
        cout << "Enter skill " << i+1 << ": ";
        cin >> skill;
        member.skills.push_back(skill);
    }
    team.push_back(member);
}

bool hasSkill(const TeamMember& member, string skill) {
    for (auto &s : member.skills) if (s == skill) return true;
    return false;
}

bool teamHasSkill(const vector<TeamMember>& team, string skill) {
    for (auto &m : team) if (hasSkill(m, skill)) return true;
    return false;
}

void analyzeSkillGaps(const vector<TeamMember>& team, const vector<string>& requiredSkills) {
    cout << "\n===== SKILL GAP ANALYSIS =====\n";
    for (auto &skill : requiredSkills) {
        if (teamHasSkill(team, skill)) cout << "[AVAILABLE] " << skill << endl;
        else cout << "[MISSING]   " << skill << endl;
    }
}

int main() {
    vector<TeamMember> team;
    vector<string> requiredSkills = {"C++", "DSA", "Backend", "Database", "UI/UX"};

    addMember(team);
    analyzeSkillGaps(team, requiredSkills);

    return 0;
}
