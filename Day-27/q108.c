//wap to create marksheet generation system//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS  100
#define MAX_SUBJECTS  6
#define MAX_NAME_LEN  50
#define PASS_MARKS    33.0f

// ─── Structure ────────────────────────────────────────────────────────────────

typedef struct {
    int    roll_no;
    char   name[MAX_NAME_LEN];
    int    age;
    char   class[20];
    char   school[60];
    int    year;

    char   subject[MAX_SUBJECTS][30];
    float  marks[MAX_SUBJECTS];
    float  max_marks[MAX_SUBJECTS];   // max marks per subject
    int    num_subjects;

    float  total_marks;
    float  total_max;
    float  percentage;
    float  grade_points;   // GPA out of 10
    char   grade[3];       // A+, A, B+, B, C, D, F
    char   result[5];      // PASS / FAIL
    char   rank_label[20]; // Distinction / First / Second / Third / Fail
} Student;

// ─── Global Data ──────────────────────────────────────────────────────────────

Student students[MAX_STUDENTS];
int total_students = 0;

// ─── Grade & Result Logic ─────────────────────────────────────────────────────

void assign_grade(Student *s) {
    float p = s->percentage;

    if (p >= 90)      { strcpy(s->grade, "A+"); s->grade_points = 10.0f; strcpy(s->rank_label, "Distinction"); }
    else if (p >= 75) { strcpy(s->grade, "A");  s->grade_points = 9.0f;  strcpy(s->rank_label, "First Class"); }
    else if (p >= 60) { strcpy(s->grade, "B+"); s->grade_points = 8.0f;  strcpy(s->rank_label, "First Class"); }
    else if (p >= 50) { strcpy(s->grade, "B");  s->grade_points = 7.0f;  strcpy(s->rank_label, "Second Class"); }
    else if (p >= 40) { strcpy(s->grade, "C");  s->grade_points = 6.0f;  strcpy(s->rank_label, "Third Class"); }
    else if (p >= 33) { strcpy(s->grade, "D");  s->grade_points = 5.0f;  strcpy(s->rank_label, "Third Class"); }
    else              { strcpy(s->grade, "F");  s->grade_points = 0.0f;  strcpy(s->rank_label, "Fail"); }
}

void calculate_result(Student *s) {
    s->total_marks = 0;
    s->total_max   = 0;

    int failed_sub = 0;
    for (int i = 0; i < s->num_subjects; i++) {
        s->total_marks += s->marks[i];
        s->total_max   += s->max_marks[i];
        float sub_percent = (s->marks[i] / s->max_marks[i]) * 100.0f;
        if (sub_percent < PASS_MARKS) failed_sub++;
    }

    s->percentage = (s->total_marks / s->total_max) * 100.0f;

    if (failed_sub > 0)
        strcpy(s->result, "FAIL");
    else
        strcpy(s->result, "PASS");

    assign_grade(s);
}

// ─── Helpers ──────────────────────────────────────────────────────────────────

int find_by_roll(int roll_no) {
    for (int i = 0; i < total_students; i++)
        if (students[i].roll_no == roll_no) return i;
    return -1;
}

void clear_buf() { while (getchar() != '\n'); }

void print_line()  { printf("═══════════════════════════════════════════════════════════════════\n"); }
void print_thin()  { printf("───────────────────────────────────────────────────────────────────\n"); }
void print_dline() { printf("*******************************************************************\n"); }

// ─── Marksheet Printer ────────────────────────────────────────────────────────

void print_marksheet(const Student *s) {
    print_dline();
    printf("*%63s*\n", "");
    printf("*%20s%-23s%20s*\n", "", s->school, "");
    printf("*%63s*\n", "");
    printf("*%17s OFFICIAL MARK SHEET - %d %17s*\n", "", s->year, "");
    printf("*%63s*\n", "");
    print_dline();

    printf("  Roll No   : %-10d   Class : %-20s\n", s->roll_no, s->class);
    printf("  Name      : %-30s   Age   : %d\n", s->name, s->age);
    print_thin();

    // Subject-wise table
    printf("  %-4s  %-22s  %-8s  %-8s  %-8s  %-6s\n",
           "No.", "Subject", "Max Mrk", "Obt Mrk", "Percent", "Status");
    print_thin();

    for (int i = 0; i < s->num_subjects; i++) {
        float sub_pct = (s->marks[i] / s->max_marks[i]) * 100.0f;
        const char *status = (sub_pct >= PASS_MARKS) ? "PASS" : "FAIL";
        printf("  %-4d  %-22s  %-8.0f  %-8.1f  %-8.2f  %-6s\n",
               i + 1, s->subject[i], s->max_marks[i],
               s->marks[i], sub_pct, status);
    }

    print_thin();
    printf("  %-27s  %-8.0f  %-8.1f\n",
           "TOTAL", s->total_max, s->total_marks);
    print_line();

    printf("  Percentage  : %.2f%%\n",    s->percentage);
    printf("  Grade       : %-5s  (GPA: %.1f / 10.0)\n", s->grade, s->grade_points);
    printf("  Division    : %s\n",        s->rank_label);
    printf("  Result      : *** %s ***\n", s->result);

    print_dline();
    printf("  Remarks: ");
    if      (strcmp(s->result, "FAIL") == 0)    printf("Better luck next time. Keep working hard!\n");
    else if (s->percentage >= 90)               printf("Outstanding performance! Excellent work.\n");
    else if (s->percentage >= 75)               printf("Very good performance. Keep it up!\n");
    else if (s->percentage >= 60)               printf("Good performance. Room for improvement.\n");
    else                                        printf("Average performance. Work harder next time.\n");
    print_dline();
}

// ─── Operations ───────────────────────────────────────────────────────────────

void add_student() {
    if (total_students >= MAX_STUDENTS) {
        printf("\nError: Maximum capacity reached!\n");
        return;
    }

    Student s;
    memset(&s, 0, sizeof(Student));

    printf("\n─── Add Student Marksheet ───\n");

    printf("Roll No           : "); scanf("%d", &s.roll_no);
    if (find_by_roll(s.roll_no) != -1) {
        printf("Error: Roll No %d already exists!\n", s.roll_no);
        return;
    }

    clear_buf();
    printf("Student Name      : "); fgets(s.name, MAX_NAME_LEN, stdin); s.name[strcspn(s.name,"\n")]='\0';
    printf("Age               : "); scanf("%d", &s.age);
    clear_buf();
    printf("Class             : "); fgets(s.class, 20, stdin);  s.class[strcspn(s.class,"\n")]='\0';
    printf("School Name       : "); fgets(s.school, 60, stdin); s.school[strcspn(s.school,"\n")]='\0';
    printf("Exam Year         : "); scanf("%d", &s.year);

    printf("Number of Subjects (max %d): ", MAX_SUBJECTS);
    scanf("%d", &s.num_subjects);
    if (s.num_subjects < 1 || s.num_subjects > MAX_SUBJECTS) {
        printf("Invalid number. Setting to 1.\n");
        s.num_subjects = 1;
    }

    printf("\nEnter Subject Details:\n");
    for (int i = 0; i < s.num_subjects; i++) {
        clear_buf();
        printf("  Subject %d Name       : ", i + 1);
        fgets(s.subject[i], 30, stdin);
        s.subject[i][strcspn(s.subject[i], "\n")] = '\0';

        printf("  Max Marks            : ");
        scanf("%f", &s.max_marks[i]);

        printf("  Marks Obtained       : ");
        scanf("%f", &s.marks[i]);

        if (s.marks[i] < 0 || s.marks[i] > s.max_marks[i]) {
            printf("  Invalid! Setting to 0.\n");
            s.marks[i] = 0;
        }
    }

    calculate_result(&s);
    students[total_students++] = s;

    printf("\nMarksheet generated!\n");
    print_marksheet(&s);
}

void view_all() {
    if (total_students == 0) { printf("\nNo records found.\n"); return; }

    printf("\n─── All Student Records (%d total) ───\n\n", total_students);
    printf("%-6s %-22s %-10s %-8s %-6s %-12s %-6s\n",
           "Roll", "Name", "Class", "Percent", "Grade", "Division", "Result");
    print_thin();
    for (int i = 0; i < total_students; i++) {
        printf("%-6d %-22s %-10s %-8.2f %-6s %-12s %-6s\n",
               students[i].roll_no, students[i].name,
               students[i].class,   students[i].percentage,
               students[i].grade,   students[i].rank_label,
               students[i].result);
    }
    print_thin();
}

void generate_marksheet() {
    int roll;
    printf("\n─── Generate Marksheet ───\n");
    printf("Enter Roll No: ");
    scanf("%d", &roll);

    int idx = find_by_roll(roll);
    if (idx == -1) { printf("Roll No %d not found.\n", roll); return; }
    print_marksheet(&students[idx]);
}

void search_student() {
    int roll;
    printf("\n─── Search Student ───\n");
    printf("Enter Roll No: ");
    scanf("%d", &roll);

    int idx = find_by_roll(roll);
    if (idx == -1) { printf("Roll No %d not found.\n", roll); return; }

    Student *s = &students[idx];
    printf("\nRoll No    : %d\n", s->roll_no);
    printf("Name       : %s\n",  s->name);
    printf("Class      : %s\n",  s->class);
    printf("Percentage : %.2f%%\n", s->percentage);
    printf("Grade      : %s  (GPA: %.1f)\n", s->grade, s->grade_points);
    printf("Division   : %s\n",  s->rank_label);
    printf("Result     : %s\n",  s->result);
}

void update_marks() {
    int roll;
    printf("\n─── Update Marks ───\n");
    printf("Enter Roll No: ");
    scanf("%d", &roll);

    int idx = find_by_roll(roll);
    if (idx == -1) { printf("Roll No %d not found.\n", roll); return; }

    Student *s = &students[idx];
    printf("Updating marks for: %s\n\n", s->name);

    for (int i = 0; i < s->num_subjects; i++) {
        printf("  %s (Max: %.0f) - Current: %.1f  New: ",
               s->subject[i], s->max_marks[i], s->marks[i]);
        scanf("%f", &s->marks[i]);
        if (s->marks[i] < 0 || s->marks[i] > s->max_marks[i]) {
            printf("  Invalid! Keeping previous.\n");
            s->marks[i] = s->marks[i];
        }
    }

    calculate_result(s);
    printf("\nMarks updated! Regenerating marksheet...\n");
    print_marksheet(s);
}

void delete_record() {
    int roll;
    printf("\n─── Delete Record ───\n");
    printf("Enter Roll No: ");
    scanf("%d", &roll);

    int idx = find_by_roll(roll);
    if (idx == -1) { printf("Roll No %d not found.\n", roll); return; }

    printf("Confirm delete '%s' (Roll %d)? (y/n): ",
           students[idx].name, roll);
    char c; scanf(" %c", &c);

    if (c == 'y' || c == 'Y') {
        for (int i = idx; i < total_students - 1; i++)
            students[i] = students[i + 1];
        total_students--;
        printf("Record deleted.\n");
    } else {
        printf("Cancelled.\n");
    }
}

void class_report() {
    if (total_students == 0) { printf("\nNo records available.\n"); return; }

    float total_pct = 0, max_pct = students[0].percentage, min_pct = students[0].percentage;
    int   pass = 0, fail = 0, dist = 0, first = 0, second = 0, third = 0;
    int   top_idx = 0;

    for (int i = 0; i < total_students; i++) {
        total_pct += students[i].percentage;
        if (students[i].percentage > max_pct) { max_pct = students[i].percentage; top_idx = i; }
        if (students[i].percentage < min_pct)   min_pct = students[i].percentage;

        if (strcmp(students[i].result, "PASS") == 0) pass++; else fail++;
        if (students[i].percentage >= 75)  { dist++;   }
        if (students[i].percentage >= 60 && students[i].percentage < 75) first++;
        if (students[i].percentage >= 50 && students[i].percentage < 60) second++;
        if (students[i].percentage >= 33 && students[i].percentage < 50) third++;
    }

    print_line();
    printf("                   CLASS RESULT REPORT\n");
    print_thin();
    printf("  Total Students      : %d\n",       total_students);
    printf("  Passed              : %d\n",        pass);
    printf("  Failed              : %d\n",        fail);
    printf("  Pass Percentage     : %.2f%%\n",    (float)pass / total_students * 100);
    print_thin();
    printf("  Distinction (>=75%%) : %d\n",  dist);
    printf("  First Class (60-74%%): %d\n",  first);
    printf("  Second Class(50-59%%): %d\n",  second);
    printf("  Third Class (33-49%%): %d\n",  third);
    print_thin();
    printf("  Class Average       : %.2f%%\n",    total_pct / total_students);
    printf("  Highest Marks       : %.2f%% (%s)\n", max_pct, students[top_idx].name);
    printf("  Lowest  Marks       : %.2f%%\n",    min_pct);
    print_line();
}

void class_topper() {
    if (total_students == 0) { printf("\nNo records available.\n"); return; }

    int top_idx = 0;
    for (int i = 1; i < total_students; i++)
        if (students[i].percentage > students[top_idx].percentage)
            top_idx = i;

    printf("\n─── Class Topper ───\n");
    print_marksheet(&students[top_idx]);
}

void grade_filter() {
    char grade[3];
    printf("\n─── Filter by Grade ───\n");
    printf("Enter Grade (A+/A/B+/B/C/D/F): ");
    scanf("%s", grade);

    int found = 0;
    printf("\nStudents with Grade '%s':\n", grade);
    print_thin();
    printf("%-6s %-22s %-10s %-8s\n", "Roll", "Name", "Class", "Percent");
    print_thin();

    for (int i = 0; i < total_students; i++) {
        if (strcmp(students[i].grade, grade) == 0) {
            printf("%-6d %-22s %-10s %.2f%%\n",
                   students[i].roll_no, students[i].name,
                   students[i].class,   students[i].percentage);
            found++;
        }
    }
    if (!found) printf("No students found with grade '%s'.\n", grade);
    else        printf("\nTotal: %d student(s)\n", found);
}

// ─── File I/O ─────────────────────────────────────────────────────────────────

void save_to_file() {
    FILE *fp = fopen("marksheet.dat", "wb");
    if (!fp) { printf("Error saving file.\n"); return; }
    fwrite(&total_students, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), total_students, fp);
    fclose(fp);
    printf("Records saved to 'marksheet.dat'.\n");
}

void load_from_file() {
    FILE *fp = fopen("marksheet.dat", "rb");
    if (!fp) { printf("No saved data. Starting fresh.\n"); return; }
    fread(&total_students, sizeof(int), 1, fp);
    fread(students, sizeof(Student), total_students, fp);
    fclose(fp);
    printf("Loaded %d record(s) from file.\n", total_students);
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    print_line();
    printf("           MARKSHEET GENERATION SYSTEM\n");
    print_line();
    load_from_file();

    int choice;
    do {
        printf("\n  MENU\n");
        printf("  1.  Add Student & Generate Marksheet\n");
        printf("  2.  View All Students (Summary)\n");
        printf("  3.  Generate Marksheet by Roll No\n");
        printf("  4.  Search Student\n");
        printf("  5.  Update Marks\n");
        printf("  6.  Delete Record\n");
        printf("  7.  Class Result Report\n");
        printf("  8.  Class Topper\n");
        printf("  9.  Filter by Grade\n");
        printf("  10. Save Records\n");
        printf("  0.  Exit\n");
        printf("\n  Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  add_student();       break;
            case 2:  view_all();          break;
            case 3:  generate_marksheet(); break;
            case 4:  search_student();    break;
            case 5:  update_marks();      break;
            case 6:  delete_record();     break;
            case 7:  class_report();      break;
            case 8:  class_topper();      break;
            case 9:  grade_filter();      break;
            case 10: save_to_file();      break;
            case 0:
                save_to_file();
                printf("\nRecords saved. Goodbye!\n");
                break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
