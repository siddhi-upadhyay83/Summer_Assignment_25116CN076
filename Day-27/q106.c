//wap to create employee management system//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LEN  50
#define MAX_DEPT_LEN  30
#define MAX_POS_LEN   30

// ─── Structure ────────────────────────────────────────────────────────────────

typedef struct {
    int    emp_id;
    char   name[MAX_NAME_LEN];
    int    age;
    char   department[MAX_DEPT_LEN];
    char   position[MAX_POS_LEN];
    float  basic_salary;
    float  hra;          // House Rent Allowance (20% of basic)
    float  da;           // Dearness Allowance   (10% of basic)
    float  tax;          // Tax deduction        (10% of basic)
    float  net_salary;
    int    years_exp;
} Employee;

// ─── Global Data ──────────────────────────────────────────────────────────────

Employee employees[MAX_EMPLOYEES];
int total_employees = 0;

// ─── Helpers ──────────────────────────────────────────────────────────────────

void calculate_salary(Employee *e) {
    e->hra        = 0.20f * e->basic_salary;
    e->da         = 0.10f * e->basic_salary;
    e->tax        = 0.10f * e->basic_salary;
    e->net_salary = e->basic_salary + e->hra + e->da - e->tax;
}

int find_employee_by_id(int emp_id) {
    for (int i = 0; i < total_employees; i++)
        if (employees[i].emp_id == emp_id)
            return i;
    return -1;
}

void clear_input_buffer() {
    while (getchar() != '\n');
}

void print_line() {
    printf("────────────────────────────────────────────────────────────\n");
}

void print_header() {
    printf("\n");
    print_line();
    printf("       EMPLOYEE MANAGEMENT SYSTEM\n");
    print_line();
}

// ─── Display ──────────────────────────────────────────────────────────────────

void display_employee(const Employee *e) {
    print_line();
    printf("  Employee ID   : %d\n",    e->emp_id);
    printf("  Name          : %s\n",    e->name);
    printf("  Age           : %d\n",    e->age);
    printf("  Department    : %s\n",    e->department);
    printf("  Position      : %s\n",    e->position);
    printf("  Experience    : %d year(s)\n", e->years_exp);
    printf("  Basic Salary  : Rs. %.2f\n",   e->basic_salary);
    printf("  HRA  (+20%%)   : Rs. %.2f\n",   e->hra);
    printf("  DA   (+10%%)   : Rs. %.2f\n",   e->da);
    printf("  Tax  (-10%%)   : Rs. %.2f\n",   e->tax);
    printf("  Net Salary    : Rs. %.2f\n",   e->net_salary);
    print_line();
}

// ─── Operations ───────────────────────────────────────────────────────────────

void add_employee() {
    if (total_employees >= MAX_EMPLOYEES) {
        printf("\nError: Maximum employee limit reached!\n");
        return;
    }

    Employee e;
    printf("\n--- Add New Employee ---\n");

    printf("Employee ID     : ");
    scanf("%d", &e.emp_id);

    if (find_employee_by_id(e.emp_id) != -1) {
        printf("Error: Employee ID %d already exists!\n", e.emp_id);
        return;
    }

    clear_input_buffer();

    printf("Name            : ");
    fgets(e.name, MAX_NAME_LEN, stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("Age             : ");
    scanf("%d", &e.age);

    clear_input_buffer();

    printf("Department      : ");
    fgets(e.department, MAX_DEPT_LEN, stdin);
    e.department[strcspn(e.department, "\n")] = '\0';

    printf("Position        : ");
    fgets(e.position, MAX_POS_LEN, stdin);
    e.position[strcspn(e.position, "\n")] = '\0';

    printf("Years of Exp    : ");
    scanf("%d", &e.years_exp);

    printf("Basic Salary(Rs): ");
    scanf("%f", &e.basic_salary);

    calculate_salary(&e);
    employees[total_employees++] = e;

    printf("\nEmployee added successfully!\n");
    printf("Net Salary: Rs. %.2f\n", e.net_salary);
}

void view_all_employees() {
    if (total_employees == 0) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\n--- All Employees (%d total) ---\n\n", total_employees);
    printf("%-6s %-22s %-5s %-15s %-18s %-12s\n",
           "ID", "Name", "Age", "Department", "Position", "Net Salary");
    print_line();

    for (int i = 0; i < total_employees; i++) {
        printf("%-6d %-22s %-5d %-15s %-18s Rs.%-9.2f\n",
               employees[i].emp_id,
               employees[i].name,
               employees[i].age,
               employees[i].department,
               employees[i].position,
               employees[i].net_salary);
    }
    print_line();
}
void search_employee() {
    int emp_id;
    printf("\n--- Search Employee ---\n");
    printf("Enter Employee ID: ");
    scanf("%d", &emp_id);

    int idx = find_employee_by_id(emp_id);
    if (idx == -1) {
        printf("Employee ID %d not found.\n", emp_id);
        return;
    }
    display_employee(&employees[idx]);
}
void update_employee() {
    int emp_id;
    printf("\n--- Update Employee Record ---\n");
    printf("Enter Employee ID to update: ");
    scanf("%d", &emp_id);

    int idx = find_employee_by_id(emp_id);
    if (idx == -1) {
        printf("Employee ID %d not found.\n", emp_id);
        return;
    }
    Employee *e = &employees[idx];
    printf("Current record:\n");
    display_employee(e);

    printf("What to update?\n");
    printf("1. Name\n2. Age\n3. Department\n4. Position\n");
    printf("5. Basic Salary\n6. Years of Experience\n7. All\n");
    printf("Choice: ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1 || choice == 7) {
        clear_input_buffer();
        printf("New Name: ");
        fgets(e->name, MAX_NAME_LEN, stdin);
        e->name[strcspn(e->name, "\n")] = '\0';
    }
    if (choice == 2 || choice == 7) {
        printf("New Age: ");
        scanf("%d", &e->age);
    }
    if (choice == 3 || choice == 7) {
        clear_input_buffer();
        printf("New Department: ");
        fgets(e->department, MAX_DEPT_LEN, stdin);
        e->department[strcspn(e->department, "\n")] = '\0';
    }
    if (choice == 4 || choice == 7) {
        if (choice != 7) clear_input_buffer();
        printf("New Position: ");
        fgets(e->position, MAX_POS_LEN, stdin);
        e->position[strcspn(e->position, "\n")] = '\0';
    }
    if (choice == 5 || choice == 7) {
        printf("New Basic Salary: ");
        scanf("%f", &e->basic_salary);
        calculate_salary(e);
    }
    if (choice == 6 || choice == 7) {
        printf("New Years of Experience: ");
        scanf("%d", &e->years_exp);
    }
    printf("\nRecord updated successfully!\n");
}
void delete_employee() {
    int emp_id;
    printf("\n--- Delete Employee Record ---\n");
    printf("Enter Employee ID to delete: ");
    scanf("%d", &emp_id);

    int idx = find_employee_by_id(emp_id);
    if (idx == -1) {
        printf("Employee ID %d not found.\n", emp_id);
        return;
    }
    printf("Confirm delete '%s' (ID: %d)? (y/n): ",
           employees[idx].name, emp_id);
    char confirm;
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = idx; i < total_employees - 1; i++)
            employees[i] = employees[i + 1];
        total_employees--;
        printf("Employee record deleted successfully.\n");
    } else {
        printf("Delete cancelled.\n");
    }
}
void search_by_department() {
    char dept[MAX_DEPT_LEN];
    printf("\n--- Search by Department ---\n");
    clear_input_buffer();
    printf("Enter Department Name: ");
    fgets(dept, MAX_DEPT_LEN, stdin);
    dept[strcspn(dept, "\n")] = '\0';

    int found = 0;
    printf("\nEmployees in '%s' department:\n\n", dept);
    printf("%-6s %-22s %-18s %-12s\n", "ID", "Name", "Position", "Net Salary");
    print_line();
    for (int i = 0; i < total_employees; i++) {
        if (strcasecmp(employees[i].department, dept) == 0) {
            printf("%-6d %-22s %-18s Rs.%.2f\n",
                   employees[i].emp_id,
                   employees[i].name,
                   employees[i].position,
                   employees[i].net_salary);
            found++;
        }
    }
    if (!found)
        printf("No employees found in '%s'.\n", dept);
    else
        printf("\nTotal: %d employee(s) found.\n", found);
}
void display_highest_paid() {
    if (total_employees == 0) {
        printf("\nNo employee records available.\n");
        return;
    }
    int top_idx = 0;
    for (int i = 1; i < total_employees; i++)
        if (employees[i].net_salary > employees[top_idx].net_salary)
            top_idx = i;

    printf("\n--- Highest Paid Employee ---");
    display_employee(&employees[top_idx]);
}
void display_salary_report() {
    if (total_employees == 0) {
        printf("\nNo records available.\n");
        return;
    }

    float total_salary = 0, min_sal = employees[0].net_salary,
          max_sal = employees[0].net_salary;

    for (int i = 0; i < total_employees; i++) {
        total_salary += employees[i].net_salary;
        if (employees[i].net_salary < min_sal) min_sal = employees[i].net_salary;
        if (employees[i].net_salary > max_sal) max_sal = employees[i].net_salary;
    }
    printf("\n--- Salary Report ---\n");
    print_line();
    printf("  Total Employees   : %d\n",       total_employees);
    printf("  Total Salary Bill : Rs. %.2f\n",  total_salary);
    printf("  Average Salary    : Rs. %.2f\n",  total_salary / total_employees);
    printf("  Highest Salary    : Rs. %.2f\n",  max_sal);
    printf("  Lowest Salary     : Rs. %.2f\n",  min_sal);
    print_line();
}
// ─── File I/O ─────────────────────────────────────────────────────────────────
void save_to_file() {
    FILE *fp = fopen("employees.dat", "wb");
    if (!fp) {
        printf("Error: Unable to save records.\n");
        return;
    }
    fwrite(&total_employees, sizeof(int), 1, fp);
    fwrite(employees, sizeof(Employee), total_employees, fp);
    fclose(fp);
    printf("Records saved to 'employees.dat' successfully.\n");
}
void load_from_file() {
    FILE *fp = fopen("employees.dat", "rb");
    if (!fp) {
        printf("No saved data found. Starting fresh.\n");
        return;
    }
    fread(&total_employees, sizeof(int), 1, fp);
    fread(employees, sizeof(Employee), total_employees, fp);
    fclose(fp);
    printf("Loaded %d record(s) from file.\n", total_employees);
}
// ─── Main ─────────────────────────────────────────────────────────────────────
int main() {
    print_header();
    load_from_file();

    int choice;
    do {
        printf("\n  MENU\n");
        printf("  1.  Add Employee\n");
        printf("  2.  View All Employees\n");
        printf("  3.  Search Employee by ID\n");
        printf("  4.  Search by Department\n");
        printf("  5.  Update Employee\n");
        printf("  6.  Delete Employee\n");
        printf("  7.  Highest Paid Employee\n");
        printf("  8.  Salary Report\n");
        printf("  9.  Save Records\n");
        printf("  0.  Exit\n");
        printf("\n  Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_employee();          break;
            case 2: view_all_employees();    break;
            case 3: search_employee();       break;
            case 4: search_by_department();  break;
            case 5: update_employee();       break;
            case 6: delete_employee();       break;
            case 7: display_highest_paid();  break;
            case 8: display_salary_report(); break;
            case 9: save_to_file();          break;
            case 0:
                save_to_file();
                printf("\nRecords saved. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
    return 0;
}