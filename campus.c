
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define MAX_STUDENTS 100
#define MAX_SKILLS 10
#define MAX_DAYS 7
#define TEXT 64
#define MAX_ROLES 4

typedef struct {
    int id;
    char name[TEXT], domain[TEXT], preferredRole[TEXT];
    int experience;
    char skills[MAX_SKILLS][TEXT];
    int skillCount;
    char days[MAX_DAYS][TEXT];
    int dayCount;
} Student;

typedef struct {
    char name[TEXT], domain[TEXT];
    char skills[MAX_SKILLS][TEXT];
    int skillCount;
} Role;

typedef struct {
    int index, score;
} Recommendation;

/* MODULE 1: STUDENT PROFILE MANAGEMENT */

static void setStudent(Student *s, int id, const char *name,
                       const char *domain, const char *role, int exp,
                       const char *skills[], int skillCount,
                       const char *days[], int dayCount) {
    int i;
    memset(s, 0, sizeof(*s));
    s->id = id;
    snprintf(s->name, TEXT, "%s", name);
    snprintf(s->domain, TEXT, "%s", domain);
    snprintf(s->preferredRole, TEXT, "%s", role);
    s->experience = exp;
    s->skillCount = skillCount;
    s->dayCount = dayCount;

    for (i = 0; i < skillCount; i++)
        snprintf(s->skills[i], TEXT, "%s", skills[i]);

    for (i = 0; i < dayCount; i++)
        snprintf(s->days[i], TEXT, "%s", days[i]);
}

void loadSampleStudents(Student students[], int *count) {
    const char *s1[] = {"C", "C++", "DSA"};
    const char *s2[] = {"Figma", "UI/UX", "HTML", "CSS"};
    const char *s3[] = {"Python", "Django", "REST API", "SQL"};
    const char *s4[] = {"SQL", "MySQL", "MongoDB", "Database"};
    const char *s5[] = {"Java", "Spring", "REST API", "Git"};
    const char *s6[] = {"JavaScript", "React", "HTML", "CSS"};
    const char *s7[] = {"Python", "Machine Learning", "Statistics"};
    const char *s8[] = {"C++", "DSA", "Git", "Testing"};

    const char *d1[] = {"Mon", "Tue", "Wed", "Fri"};
    const char *d2[] = {"Tue", "Wed", "Thu", "Sat"};
    const char *d3[] = {"Mon", "Wed", "Thu", "Fri"};
    const char *d4[] = {"Mon", "Tue", "Thu", "Sat"};
    const char *d5[] = {"Wed", "Thu", "Fri", "Sat"};
    const char *d6[] = {"Mon", "Tue", "Wed", "Fri"};
    const char *d7[] = {"Tue", "Thu", "Fri", "Sat"};
    const char *d8[] = {"Mon", "Wed", "Fri", "Sat"};

    *count = 8;

    setStudent(&students[0], 101, "Aarav", "Software",
               "DSA/Programming", 2, s1, 3, d1, 4);

    setStudent(&students[1], 102, "Diya", "Web Development",
               "UI/UX Designer", 1, s2, 4, d2, 4);

    setStudent(&students[2], 103, "Kabir", "Web Development",
               "Backend Developer", 2, s3, 4, d3, 4);

    setStudent(&students[3], 104, "Anaya", "Database",
               "Database Developer", 2, s4, 4, d4, 4);

    setStudent(&students[4], 105, "Ishaan", "Software",
               "Backend Developer", 2, s5, 4, d5, 4);

    setStudent(&students[5], 106, "Meera", "Web Development",
               "Frontend Developer", 1, s6, 4, d6, 4);

    setStudent(&students[6], 107, "Vivaan", "AI",
               "Data Analyst", 1, s7, 3, d7, 4);

    setStudent(&students[7], 108, "Sara", "Software",
               "DSA/Programming", 2, s8, 4, d8, 4);
}

int addStudent(Student students[], int *count, Student s) {
    int i;

    if (*count >= MAX_STUDENTS)
        return 0;

    for (i = 0; i < *count; i++)
        if (students[i].id == s.id)
            return -1;

    students[*count] = s;
    (*count)++;

    return 1;
}

void displayStudents(const Student students[], int count) {
    int i, j;

    printf("\n--- STUDENT PROFILES ---\n");

    for (i = 0; i < count; i++) {
        printf("\nID: %d | Name: %s\n",
               students[i].id, students[i].name);

        printf("Domain: %s | Preferred role: %s\n",
               students[i].domain, students[i].preferredRole);

        printf("Skills: ");

        for (j = 0; j < students[i].skillCount; j++)
            printf("%s%s", students[i].skills[j],
                   j + 1 == students[i].skillCount ? "" : ", ");

        printf("\n");
    }
}

/* MODULE 2: SKILL MATCHING */

int calculateScore(const Student *s, const Role *r) {
    int i, j, matches = 0, score;

    for (i = 0; i < r->skillCount; i++) {
        for (j = 0; j < s->skillCount; j++) {
            if (strcasecmp(r->skills[i], s->skills[j]) == 0) {
                matches++;
                break;
            }
        }
    }

    score = r->skillCount ? matches * 65 / r->skillCount : 0;

    if (strcasecmp(s->preferredRole, r->name) == 0)
        score += 15;

    if (strcasecmp(s->domain, r->domain) == 0)
        score += 10;

    score += s->experience * 5;

    return score > 100 ? 100 : score;
}

/* MODULE 3: ROLE-BASED RECOMMENDATIONS */

int recommendStudents(const Student students[], int count,
                      const Role *role,
                      Recommendation output[], int limit) {
    int i, j, used = 0;

    for (i = 0; i < count; i++) {
        Recommendation item;

        item.index = i;
        item.score = calculateScore(&students[i], role);

        j = used;

        while (j > 0 && output[j - 1].score < item.score) {
            if (j < limit)
                output[j] = output[j - 1];

            j--;
        }

        if (j < limit) {
            output[j] = item;

            if (used < limit)
                used++;
        }
    }

    return used;
}

/* MODULE 4: AVAILABILITY MATCHING */

int shareAvailability(const Student *a, const Student *b) {
    int i, j;

    for (i = 0; i < a->dayCount; i++)
        for (j = 0; j < b->dayCount; j++)
            if (strcmp(a->days[i], b->days[j]) == 0)
                return 1;

    return 0;
}

void showCommonAvailability(const Student students[],
                            const int team[], int teamCount) {
    int i, j, k, allMatch;

    if (teamCount == 0) {
        printf("Build a team first.\n");
        return;
    }

    printf("Common days: ");
    allMatch = 0;

    for (i = 0; i < students[team[0]].dayCount; i++) {
        const char *day = students[team[0]].days[i];
        int common = 1;

        for (j = 1; j < teamCount; j++) {
            int found = 0;

            for (k = 0; k < students[team[j]].dayCount; k++)
                if (strcmp(day, students[team[j]].days[k]) == 0)
                    found = 1;

            if (!found)
                common = 0;
        }

        if (common) {
            printf("%s ", day);
            allMatch = 1;
        }
    }

    if (!allMatch)
        printf("No single common day found.");

    printf("\n");
}

/* MODULE 5: BALANCED TEAM BUILDER */

int buildBalancedTeam(const Student students[], int studentCount,
                      const Role roles[], int roleCount, int team[]) {
    int r, i, j, teamCount = 0;

    for (r = 0; r < roleCount; r++) {
        int best = -1, bestScore = -1;

        for (i = 0; i < studentCount; i++) {
            int selected = 0;
            int score;

            for (j = 0; j < teamCount; j++)
                if (team[j] == i)
                    selected = 1;

            if (selected)
                continue;

            score = calculateScore(&students[i], &roles[r]);

            for (j = 0; j < teamCount; j++)
                if (shareAvailability(&students[i], &students[team[j]]))
                    score += 3;

            if (score > bestScore) {
                bestScore = score;
                best = i;
            }
        }

        if (best >= 0)
            team[teamCount++] = best;
    }

    return teamCount;
}

/* MODULE 6: SKILL GAP ANALYZER */

void analyzeSkillGaps(const Student students[], const int team[],
                      int teamCount, const Role roles[], int roleCount) {
    int r, s, i, j, found, missing = 0;

    if (teamCount == 0) {
        printf("Build a team first.\n");
        return;
    }

    printf("\n--- SKILL GAP REPORT ---\n");

    for (r = 0; r < roleCount; r++) {
        for (s = 0; s < roles[r].skillCount; s++) {
            found = 0;

            for (i = 0; i < teamCount; i++) {
                const Student *member = &students[team[i]];

                for (j = 0; j < member->skillCount; j++)
                    if (strcasecmp(roles[r].skills[s],
                                   member->skills[j]) == 0)
                        found = 1;
            }

            if (!found) {
                printf("Missing skill: %s (for %s)\n",
                       roles[r].skills[s], roles[r].name);

                missing++;
            }
        }
    }

    if (missing == 0)
        printf("All required role skills are represented in the team.\n");

    printf("Total missing skill requirements: %d\n", missing);
}
