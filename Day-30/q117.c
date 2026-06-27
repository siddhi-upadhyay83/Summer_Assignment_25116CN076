//wap to create student record system using arrays and strings//
/*
 * Features: Add, Display, Search, Update, Delete, and Calculate Average
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 50
#define NAME_LEN     50
#define BRANCH_LEN   30

/* ─── Data Structure ─────────────────────────────────────────────────── */
struct Student {
    int    roll_no;
    char   name[NAME_LEN];
    char   branch[BRANCH_LEN];
    float  marks[5];   /* marks for 5 subjects */
    float  total;
    float  percentage;
    char   grade;
};

/* ─── Global Storage ─────────────────────────────────────────────────── */
struct Student students[MAX_STUDENTS];
int count = 0;

/* ─── Helper Functions ───────────────────────────────────────────────── */

char calcGrade(float percentage) {
    if (percentage >= 90) return 'A';
    if (percentage >= 75) return 'B';
    if (percentage >= 60) return 'C';
    if (percentage >= 50) return 'D';
    return 'F';
}

/* Returns index of student with given roll number, or -1 if not found */
int findStudent(int roll) {
    for (int i = 0; i < count; i++)
        if (students[i].roll_no == roll)
            return i;
    return -1;
}

void printLine(void) {
    printf("%-70s\n", "----------------------------------------------------------------------");
}

void printHeader(void) {
    printLine();
    printf("%-6s %-20s %-12s %6s %6s %6s %6s %6s %7s %6s %5s\n",
           "Roll", "Name", "Branch",
           "Sub1", "Sub2", "Sub3", "Sub4", "Sub5",
           "Total", "%", "Grade");
    printLine();
}

void printStudentRow(struct Student *s) {
    printf("%-6d %-20s %-12s %6.1f %6.1f %6.1f %6.1f %6.1f %7.1f %6.1f %5c\n",
           s->roll_no, s->name, s->branch,
           s->marks[0], s->marks[1], s->marks[2], s->marks[3], s->marks[4],
           s->total, s->percentage, s->grade);
}

/* ─── Core Operations ────────────────────────────────────────────────── */

void addStudent(void) {
    if (count >= MAX_STUDENTS) {
        printf("\n  [!] Record full. Cannot add more students.\n");
        return;
    }

    struct Student s;
    printf("\n  Enter Roll Number  : ");
    scanf("%d", &s.roll_no);

    if (findStudent(s.roll_no) != -1) {
        printf("  [!] Roll number %d already exists.\n", s.roll_no);
        return;
    }

    printf("  Enter Name         : ");
    scanf(" %[^\n]s", s.name);

    printf("  Enter Branch       : ");
    scanf(" %[^\n]s", s.branch);

    printf("  Enter marks for 5 subjects (out of 100):\n");
    s.total = 0;
    for (int i = 0; i < 5; i++) {
        printf("    Subject %d : ", i + 1);
        scanf("%f", &s.marks[i]);
        s.total += s.marks[i];
    }

    s.percentage = s.total / 5.0f;
    s.grade      = calcGrade(s.percentage);

    students[count++] = s;
    printf("\n  [✓] Student added successfully!\n");
}

void displayAll(void) {
    if (count == 0) {
        printf("\n  No records found.\n");
        return;
    }
    printf("\n  === All Student Records ===\n");
    printHeader();
    for (int i = 0; i < count; i++)
        printStudentRow(&students[i]);
    printLine();
    printf("  Total records: %d\n", count);
}

void searchStudent(void) {
    int roll;
    printf("\n  Enter Roll Number to search: ");
    scanf("%d", &roll);

    int idx = findStudent(roll);
    if (idx == -1) {
        printf("  [!] Student with roll %d not found.\n", roll);
        return;
    }

    struct Student *s = &students[idx];
    printf("\n  ── Student Details ──────────────────────────\n");
    printf("  Roll Number : %d\n",   s->roll_no);
    printf("  Name        : %s\n",   s->name);
    printf("  Branch      : %s\n",   s->branch);
    for (int i = 0; i < 5; i++)
        printf("  Subject %-2d  : %.1f\n", i + 1, s->marks[i]);
    printf("  Total       : %.1f\n", s->total);
    printf("  Percentage  : %.1f%%\n", s->percentage);
    printf("  Grade       : %c\n",   s->grade);
    printf("  ─────────────────────────────────────────────\n");
}

void updateStudent(void) {
    int roll;
    printf("\n  Enter Roll Number to update: ");
    scanf("%d", &roll);

    int idx = findStudent(roll);
    if (idx == -1) {
        printf("  [!] Student with roll %d not found.\n", roll);
        return;
    }

    struct Student *s = &students[idx];
    printf("  Update Name [current: %s] (press Enter to keep): ", s->name);
    char tmp[NAME_LEN];
    scanf(" %[^\n]s", tmp);
    if (strlen(tmp) > 0) strcpy(s->name, tmp);

    printf("  Update Branch [current: %s] (press Enter to keep): ", s->branch);
    char tmp2[BRANCH_LEN];
    scanf(" %[^\n]s", tmp2);
    if (strlen(tmp2) > 0) strcpy(s->branch, tmp2);

    printf("  Re-enter marks for 5 subjects? (y/n): ");
    char ch;
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y') {
        s->total = 0;
        for (int i = 0; i < 5; i++) {
            printf("    Subject %d : ", i + 1);
            scanf("%f", &s->marks[i]);
            s->total += s->marks[i];
        }
        s->percentage = s->total / 5.0f;
        s->grade      = calcGrade(s->percentage);
    }

    printf("  [✓] Record updated successfully!\n");
}

void deleteStudent(void) {
    int roll;
    printf("\n  Enter Roll Number to delete: ");
    scanf("%d", &roll);

    int idx = findStudent(roll);
    if (idx == -1) {
        printf("  [!] Student with roll %d not found.\n", roll);
        return;
    }

    /* Shift records left */
    for (int i = idx; i < count - 1; i++)
        students[i] = students[i + 1];
    count--;

    printf("  [✓] Student with roll %d deleted.\n", roll);
}

void classAverage(void) {
    if (count == 0) {
        printf("\n  No records to calculate average.\n");
        return;
    }

    float totalPct = 0;
    int   aCount = 0, bCount = 0, cCount = 0, dCount = 0, fCount = 0;

    for (int i = 0; i < count; i++) {
        totalPct += students[i].percentage;
        switch (students[i].grade) {
            case 'A': aCount++; break;
            case 'B': bCount++; break;
            case 'C': cCount++; break;
            case 'D': dCount++; break;
            default:  fCount++; break;
        }
    }

    printf("\n  ── Class Statistics ──────────────────────────\n");
    printf("  Total Students   : %d\n",    count);
    printf("  Class Average    : %.2f%%\n", totalPct / count);
    printf("  Grade A (>=90%%): %d students\n", aCount);
    printf("  Grade B (>=75%%): %d students\n", bCount);
    printf("  Grade C (>=60%%): %d students\n", cCount);
    printf("  Grade D (>=50%%): %d students\n", dCount);
    printf("  Grade F (<50%%) : %d students\n", fCount);
    printf("  ─────────────────────────────────────────────\n");
}

/* ─── Main Menu ──────────────────────────────────────────────────────── */

int main(void) {
    int choice;

    printf("\n  ╔══════════════════════════════════════╗");
    printf("\n  ║     STUDENT RECORD MANAGEMENT SYSTEM ║");
    printf("\n  ╚══════════════════════════════════════╝\n");

    do {
        printf("\n  ┌─ MENU ──────────────────────────────┐\n");
        printf("  │  1. Add Student                     │\n");
        printf("  │  2. Display All Students            │\n");
        printf("  │  3. Search Student by Roll No       │\n");
        printf("  │  4. Update Student Record           │\n");
        printf("  │  5. Delete Student Record           │\n");
        printf("  │  6. Class Statistics & Average      │\n");
        printf("  │  0. Exit                            │\n");
        printf("  └─────────────────────────────────────┘\n");
        printf("  Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent();    break;
            case 2: displayAll();    break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: classAverage();  break;
            case 0: printf("\n  Goodbye!\n\n"); break;
            default: printf("  [!] Invalid option. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}
