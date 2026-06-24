//wap to create student record management system//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
// ─── Structure ────────────────────────────────────────────────────────────────
typedef struct {
    int    roll_no;
    char   name[MAX_NAME_LEN];
    int    age;
    float  marks[5];   // marks for 5 subjects
    float  percentage;
    char   grade;
} Student;
// ─── Global Data ──────────────────────────────────────────────────────────────
Student students[MAX_STUDENTS];
int total_students = 0;
// ─── Helpers ──────────────────────────────────────────────────────────────────
float calculate_percentage(float marks[], int n) {
    float total = 0;
    for (int i = 0; i < n; i++) total += marks[i];
    return total / n;
}
char calculate_grade(float percentage) {
    if (percentage >= 90) return 'A';
    if (percentage >= 75) return 'B';
    if (percentage >= 60) return 'C';
    if (percentage >= 45) return 'D';
    return 'F';
}
int find_student_by_roll(int roll_no) {
    for (int i = 0; i < total_students; i++)
        if (students[i].roll_no == roll_no)
            return i;
    return -1;
}
void clear_input_buffer() {
    while (getchar() != '\n');
}
void print_separator() {
    printf("\n────────────────────────────────────────────────────────\n");
}
void print_header() {
    print_separator();
    printf("  STUDENT RECORD MANAGEMENT SYSTEM\n");
    print_separator();
}
// ─── Core Operations ──────────────────────────────────────────────────────────
void add_student() {
    if (total_students >= MAX_STUDENTS) {
        printf("\nError: Maximum student capacity reached!\n");
        return;
    }
    Student s;
    printf("\n--- Add New Student ---\n");

    printf("Enter Roll No     : ");
    scanf("%d", &s.roll_no);

    if (find_student_by_roll(s.roll_no) != -1) {
        printf("Error: Student with Roll No %d already exists!\n", s.roll_no);
        return;
    }
    clear_input_buffer();
    printf("Enter Name        : ");
    fgets(s.name, MAX_NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';  // strip trailing newline

    printf("Enter Age         : ");
    scanf("%d", &s.age);

    printf("Enter Marks for 5 Subjects (out of 100):\n");
    const char *subjects[] = {"Subject 1", "Subject 2", "Subject 3", "Subject 4", "Subject 5"};
    for (int i = 0; i < 5; i++) {
        printf("  %-10s : ", subjects[i]);
        scanf("%f", &s.marks[i]);
        if (s.marks[i] < 0 || s.marks[i] > 100) {
            printf("  Invalid marks! Setting to 0.\n");
            s.marks[i] = 0;
        }
    }
    s.percentage = calculate_percentage(s.marks, 5);
    s.grade      = calculate_grade(s.percentage);

    students[total_students++] = s;
    printf("\nStudent added successfully! Grade: %c (%.2f%%)\n", s.grade, s.percentage);
}
void display_student(const Student *s) {
    printf("\nRoll No     : %d\n", s->roll_no);
    printf("Name        : %s\n",  s->name);
    printf("Age         : %d\n",  s->age);
    printf("Marks       : ");
    for (int i = 0; i < 5; i++)
        printf("%.1f  ", s->marks[i]);
    printf("\nPercentage  : %.2f%%\n", s->percentage);
    printf("Grade       : %c\n",   s->grade);
}
void view_all_students() {
    if (total_students == 0) {
        printf("\nNo student records found.\n");
        return;
    }
    printf("\n--- All Student Records (%d total) ---\n", total_students);
    printf("%-8s %-25s %-5s %-12s %-6s\n", "Roll No", "Name", "Age", "Percentage", "Grade");
    printf("%-8s %-25s %-5s %-12s %-6s\n",
           "-------", "------------------------", "---", "----------", "-----");

    for (int i = 0; i < total_students; i++) {
        printf("%-8d %-25s %-5d %-12.2f %-6c\n",
               students[i].roll_no,
               students[i].name,
               students[i].age,
               students[i].percentage,
               students[i].grade);
    }
}
void search_student() {
    int roll_no;
    printf("\n--- Search Student ---\n");
    printf("Enter Roll No to search: ");
    scanf("%d", &roll_no);

    int idx = find_student_by_roll(roll_no);
    if (idx == -1) {
        printf("Student with Roll No %d not found.\n", roll_no);
        return;
    }
    display_student(&students[idx]);
}
void update_student() {
    int roll_no;
    printf("\n--- Update Student Record ---\n");
    printf("Enter Roll No to update: ");
    scanf("%d", &roll_no);

    int idx = find_student_by_roll(roll_no);
    if (idx == -1) {
        printf("Student with Roll No %d not found.\n", roll_no);
        return;
    }
    Student *s = &students[idx];
    printf("Current record:\n");
    display_student(s);

    int choice;
    printf("\nWhat to update?\n");
    printf("1. Name\n2. Age\n3. Marks\n4. All\n");
    printf("Choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 4) {
        clear_input_buffer();
        printf("New Name: ");
        fgets(s->name, MAX_NAME_LEN, stdin);
        s->name[strcspn(s->name, "\n")] = '\0';
    }
    if (choice == 2 || choice == 4) {
        printf("New Age: ");
        scanf("%d", &s->age);
    }
    if (choice == 3 || choice == 4) {
        printf("Enter new marks for 5 subjects:\n");
        for (int i = 0; i < 5; i++) {
            printf("  Subject %d: ", i + 1);
            scanf("%f", &s->marks[i]);
        }
        s->percentage = calculate_percentage(s->marks, 5);
        s->grade      = calculate_grade(s->percentage);
    }
    printf("\nRecord updated successfully!\n");
}
void delete_student() {
    int roll_no;
    printf("\n--- Delete Student Record ---\n");
    printf("Enter Roll No to delete: ");
    scanf("%d", &roll_no);

    int idx = find_student_by_roll(roll_no);
    if (idx == -1) {
        printf("Student with Roll No %d not found.\n", roll_no);
        return;
    }
    printf("Confirm delete of '%s' (Roll No %d)? (y/n): ",
           students[idx].name, roll_no);
    char confirm;
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        // Shift remaining records left
        for (int i = idx; i < total_students - 1; i++)
            students[i] = students[i + 1];
        total_students--;
        printf("Record deleted successfully.\n");
    } else {
        printf("Delete cancelled.\n");
    }
}
void display_topper() {
    if (total_students == 0) {
        printf("\nNo records available.\n");
        return;
    }
    int top_idx = 0;
    for (int i = 1; i < total_students; i++)
        if (students[i].percentage > students[top_idx].percentage)
            top_idx = i;

    printf("\n--- Class Topper ---");
    display_student(&students[top_idx]);
}
void save_to_file() {
    FILE *fp = fopen("students.dat", "wb");
    if (!fp) {
        printf("Error: Unable to open file for saving.\n");
        return;
    }
    fwrite(&total_students, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), total_students, fp);
    fclose(fp);
    printf("Records saved to 'students.dat' successfully.\n");
}
void load_from_file() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("No saved data found. Starting fresh.\n");
        return;
    }
    fread(&total_students, sizeof(int), 1, fp);
    fread(students, sizeof(Student), total_students, fp);
    fclose(fp);
    printf("Loaded %d record(s) from 'students.dat'.\n", total_students);
}
// ─── Main Menu ────────────────────────────────────────────────────────────────
int main() {
    print_header();
    load_from_file();

    int choice;
    do {
        printf("\n\n  MENU\n");
        printf("  1. Add Student\n");
        printf("  2. View All Students\n");
        printf("  3. Search Student\n");
        printf("  4. Update Student\n");
        printf("  5. Delete Student\n");
        printf("  6. Display Class Topper\n");
        printf("  7. Save Records to File\n");
        printf("  0. Exit\n");
        printf("\n  Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_student();      break;
            case 2: view_all_students(); break;
            case 3: search_student();   break;
            case 4: update_student();   break;
            case 5: delete_student();   break;
            case 6: display_topper();   break;
            case 7: save_to_file();     break;
            case 0:
                save_to_file();
                printf("\nRecords saved. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
    return 0;
}
