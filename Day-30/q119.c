//wap to create mini employee management system//
/*
 * Features: Add, Display, Search, Update, Delete, Salary Report, Department Summary
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EMP      100
#define NAME_LEN      50
#define DEPT_LEN      30
#define DESIGN_LEN    40
#define EMAIL_LEN     50
#define PHONE_LEN     15

/* ─── Data Structure ─────────────────────────────────────────────────── */

struct Employee {
    int    emp_id;
    char   name[NAME_LEN];
    char   department[DEPT_LEN];
    char   designation[DESIGN_LEN];
    char   email[EMAIL_LEN];
    char   phone[PHONE_LEN];
    int    join_year;
    float  basic_salary;
    float  hra;          /* 20% of basic */
    float  da;           /* 10% of basic */
    float  tax;          /* 10% of gross */
    float  net_salary;
};

/* ─── Global Storage ─────────────────────────────────────────────────── */

struct Employee emp[MAX_EMP];
int emp_count = 0;

/* ─── Helper Functions ───────────────────────────────────────────────── */

void printLine(void) {
    printf("--------------------------------------------------------------------------------\n");
}

int findEmp(int id) {
    for (int i = 0; i < emp_count; i++)
        if (emp[i].emp_id == id) return i;
    return -1;
}

void calcSalary(struct Employee *e) {
    e->hra        = 0.20f * e->basic_salary;
    e->da         = 0.10f * e->basic_salary;
    float gross   = e->basic_salary + e->hra + e->da;
    e->tax        = 0.10f * gross;
    e->net_salary = gross - e->tax;
}

void printEmpRow(struct Employee *e) {
    printf("  %-6d %-20s %-15s %-18s %10.2f\n",
           e->emp_id, e->name, e->department,
           e->designation, e->net_salary);
}

/* ─── Core Operations ────────────────────────────────────────────────── */

void addEmployee(void) {
    if (emp_count >= MAX_EMP) {
        printf("\n  [!] Employee list is full.\n");
        return;
    }

    struct Employee e;

    printf("\n  Enter Employee ID    : ");
    scanf("%d", &e.emp_id);
    if (findEmp(e.emp_id) != -1) {
        printf("  [!] Employee ID %d already exists.\n", e.emp_id);
        return;
    }

    printf("  Enter Full Name      : ");
    scanf(" %[^\n]", e.name);

    printf("  Enter Department     : ");
    scanf(" %[^\n]", e.department);

    printf("  Enter Designation    : ");
    scanf(" %[^\n]", e.designation);

    printf("  Enter Email          : ");
    scanf(" %[^\n]", e.email);

    printf("  Enter Phone          : ");
    scanf(" %[^\n]", e.phone);

    printf("  Joining Year         : ");
    scanf("%d", &e.join_year);

    printf("  Basic Salary (INR)   : ");
    scanf("%f", &e.basic_salary);

    calcSalary(&e);

    emp[emp_count++] = e;

    printf("\n  [✓] Employee added successfully!\n");
    printf("      Net Salary: INR %.2f / month\n", e.net_salary);
}

void displayAll(void) {
    if (emp_count == 0) {
        printf("\n  No employee records found.\n");
        return;
    }

    printf("\n  ╔══════════════════════════ EMPLOYEE DIRECTORY ════════════════════════════╗\n");
    printf("  %-6s %-20s %-15s %-18s %10s\n",
           "ID", "Name", "Department", "Designation", "Net Sal.");
    printLine();
    for (int i = 0; i < emp_count; i++)
        printEmpRow(&emp[i]);
    printLine();
    printf("  Total employees: %d\n", emp_count);
}

void searchEmployee(void) {
    int choice;
    printf("\n  Search by:\n");
    printf("  1. Employee ID\n");
    printf("  2. Name (keyword)\n");
    printf("  3. Department\n");
    printf("  Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("  Enter Employee ID: ");
        scanf("%d", &id);
        int idx = findEmp(id);
        if (idx == -1) { printf("  [!] Employee not found.\n"); return; }

        struct Employee *e = &emp[idx];
        printf("\n  ── Employee Profile ────────────────────────────\n");
        printf("  Employee ID   : %d\n",      e->emp_id);
        printf("  Name          : %s\n",      e->name);
        printf("  Department    : %s\n",      e->department);
        printf("  Designation   : %s\n",      e->designation);
        printf("  Email         : %s\n",      e->email);
        printf("  Phone         : %s\n",      e->phone);
        printf("  Joining Year  : %d\n",      e->join_year);
        printf("  ── Salary Breakdown ────────────────────────────\n");
        printf("  Basic Salary  : INR %10.2f\n", e->basic_salary);
        printf("  HRA  (20%%)   : INR %10.2f\n", e->hra);
        printf("  DA   (10%%)   : INR %10.2f\n", e->da);
        printf("  Gross Salary  : INR %10.2f\n", e->basic_salary + e->hra + e->da);
        printf("  Tax  (10%%)   : INR %10.2f\n", e->tax);
        printf("  Net Salary    : INR %10.2f\n", e->net_salary);
        printf("  ────────────────────────────────────────────────\n");
    }
    else if (choice == 2 || choice == 3) {
        char keyword[NAME_LEN];
        printf("  Enter keyword: ");
        scanf(" %[^\n]", keyword);

        /* lowercase keyword */
        char lk[NAME_LEN];
        for (int j = 0; (lk[j] = (keyword[j] >= 'A' && keyword[j] <= 'Z')
                          ? keyword[j] + 32 : keyword[j]); j++);

        int found = 0;
        printf("\n  %-6s %-20s %-15s %-18s %10s\n",
               "ID", "Name", "Department", "Designation", "Net Sal.");
        printLine();
        for (int i = 0; i < emp_count; i++) {
            char *field = (choice == 2) ? emp[i].name : emp[i].department;
            char lf[NAME_LEN];
            for (int j = 0; (lf[j] = (field[j] >= 'A' && field[j] <= 'Z')
                              ? field[j] + 32 : field[j]); j++);
            if (strstr(lf, lk)) {
                printEmpRow(&emp[i]);
                found++;
            }
        }
        if (!found) printf("  No matching employees found.\n");
        else printf("  %d result(s) found.\n", found);
    }
    else {
        printf("  [!] Invalid choice.\n");
    }
}

void updateEmployee(void) {
    int id;
    printf("\n  Enter Employee ID to update: ");
    scanf("%d", &id);
    int idx = findEmp(id);
    if (idx == -1) { printf("  [!] Employee not found.\n"); return; }

    struct Employee *e = &emp[idx];
    int field;

    printf("\n  What to update?\n");
    printf("  1. Name\n");
    printf("  2. Department\n");
    printf("  3. Designation\n");
    printf("  4. Email\n");
    printf("  5. Phone\n");
    printf("  6. Basic Salary\n");
    printf("  7. All Details\n");
    printf("  Choice: ");
    scanf("%d", &field);

    switch (field) {
        case 1:
            printf("  New Name        : ");
            scanf(" %[^\n]", e->name);
            break;
        case 2:
            printf("  New Department  : ");
            scanf(" %[^\n]", e->department);
            break;
        case 3:
            printf("  New Designation : ");
            scanf(" %[^\n]", e->designation);
            break;
        case 4:
            printf("  New Email       : ");
            scanf(" %[^\n]", e->email);
            break;
        case 5:
            printf("  New Phone       : ");
            scanf(" %[^\n]", e->phone);
            break;
        case 6:
            printf("  New Basic Salary: ");
            scanf("%f", &e->basic_salary);
            calcSalary(e);
            printf("  New Net Salary  : INR %.2f\n", e->net_salary);
            break;
        case 7:
            printf("  Name            : "); scanf(" %[^\n]", e->name);
            printf("  Department      : "); scanf(" %[^\n]", e->department);
            printf("  Designation     : "); scanf(" %[^\n]", e->designation);
            printf("  Email           : "); scanf(" %[^\n]", e->email);
            printf("  Phone           : "); scanf(" %[^\n]", e->phone);
            printf("  Basic Salary    : "); scanf("%f", &e->basic_salary);
            calcSalary(e);
            break;
        default:
            printf("  [!] Invalid choice.\n");
            return;
    }

    printf("  [✓] Record updated successfully!\n");
}

void deleteEmployee(void) {
    int id;
    printf("\n  Enter Employee ID to delete: ");
    scanf("%d", &id);
    int idx = findEmp(id);
    if (idx == -1) { printf("  [!] Employee not found.\n"); return; }

    printf("  Delete \"%s\"? (y/n): ", emp[idx].name);
    char ch;
    scanf(" %c", &ch);
    if (ch != 'y' && ch != 'Y') { printf("  Cancelled.\n"); return; }

    for (int i = idx; i < emp_count - 1; i++)
        emp[i] = emp[i + 1];
    emp_count--;

    printf("  [✓] Employee record deleted.\n");
}

/* ─── Reports ────────────────────────────────────────────────────────── */

void salaryReport(void) {
    if (emp_count == 0) { printf("\n  No records.\n"); return; }

    float total_gross = 0, total_net = 0, total_tax = 0;
    float max_sal = emp[0].net_salary, min_sal = emp[0].net_salary;
    int   max_idx = 0, min_idx = 0;

    printf("\n  ╔══════════════════════════ SALARY REPORT ═════════════════════════════════╗\n");
    printf("  %-6s %-20s %10s %8s %8s %8s %10s\n",
           "ID", "Name", "Basic", "HRA", "DA", "Tax", "Net");
    printLine();

    for (int i = 0; i < emp_count; i++) {
        struct Employee *e = &emp[i];
        printf("  %-6d %-20s %10.2f %8.2f %8.2f %8.2f %10.2f\n",
               e->emp_id, e->name,
               e->basic_salary, e->hra, e->da, e->tax, e->net_salary);

        total_gross += e->basic_salary + e->hra + e->da;
        total_net   += e->net_salary;
        total_tax   += e->tax;

        if (e->net_salary > max_sal) { max_sal = e->net_salary; max_idx = i; }
        if (e->net_salary < min_sal) { min_sal = e->net_salary; min_idx = i; }
    }

    printLine();
    printf("  %-27s %10.2f %8.2f %8.2f %8.2f %10.2f\n",
           "TOTALS", total_gross - total_net - total_tax + total_gross,
           0.0f, 0.0f, total_tax, total_net);
    printf("\n  Highest Paid : %s  (INR %.2f)\n", emp[max_idx].name, max_sal);
    printf("  Lowest  Paid : %s  (INR %.2f)\n", emp[min_idx].name, min_sal);
    printf("  Avg Net Sal  : INR %.2f\n", total_net / emp_count);
}

void departmentSummary(void) {
    if (emp_count == 0) { printf("\n  No records.\n"); return; }

    /* collect unique departments */
    char depts[MAX_EMP][DEPT_LEN];
    int  dept_count = 0;

    for (int i = 0; i < emp_count; i++) {
        int found = 0;
        for (int d = 0; d < dept_count; d++)
            if (strcmp(depts[d], emp[i].department) == 0) { found = 1; break; }
        if (!found) strcpy(depts[dept_count++], emp[i].department);
    }

    printf("\n  ╔══════════════════════ DEPARTMENT SUMMARY ════════════════════════════════╗\n");
    printf("  %-20s %8s %14s %14s\n",
           "Department", "Members", "Avg Net Sal", "Total Payroll");
    printLine();

    for (int d = 0; d < dept_count; d++) {
        int   cnt = 0;
        float total = 0;
        for (int i = 0; i < emp_count; i++) {
            if (strcmp(emp[i].department, depts[d]) == 0) {
                cnt++;
                total += emp[i].net_salary;
            }
        }
        printf("  %-20s %8d %14.2f %14.2f\n",
               depts[d], cnt, total / cnt, total);
    }
    printLine();
}

void companySummary(void) {
    if (emp_count == 0) { printf("\n  No records.\n"); return; }

    float total_payroll = 0;
    for (int i = 0; i < emp_count; i++)
        total_payroll += emp[i].net_salary;

    /* count unique departments */
    char depts[MAX_EMP][DEPT_LEN];
    int  dept_count = 0;
    for (int i = 0; i < emp_count; i++) {
        int found = 0;
        for (int d = 0; d < dept_count; d++)
            if (strcmp(depts[d], emp[i].department) == 0) { found = 1; break; }
        if (!found) strcpy(depts[dept_count++], emp[i].department);
    }

    printf("\n  ╔════════════════════ COMPANY OVERVIEW ════════════════════╗\n");
    printf("  ║  Total Employees     : %-6d                           ║\n", emp_count);
    printf("  ║  Total Departments   : %-6d                           ║\n", dept_count);
    printf("  ║  Monthly Payroll     : INR %-12.2f               ║\n", total_payroll);
    printf("  ║  Annual  Payroll     : INR %-12.2f               ║\n", total_payroll * 12);
    printf("  ║  Avg Employee Salary : INR %-12.2f               ║\n", total_payroll / emp_count);
    printf("  ╚══════════════════════════════════════════════════════════╝\n");
}

/* ─── Main Menu ──────────────────────────────────────────────────────── */

int main(void) {
    int choice;

    printf("\n  ╔══════════════════════════════════════════════╗");
    printf("\n  ║     MINI EMPLOYEE MANAGEMENT SYSTEM          ║");
    printf("\n  ╚══════════════════════════════════════════════╝\n");

    do {
        printf("\n  ┌─ MAIN MENU ────────────────────────────────────┐\n");
        printf("  │  ── Employee Records ──                        │\n");
        printf("  │  1. Add Employee                              │\n");
        printf("  │  2. Display All Employees                     │\n");
        printf("  │  3. Search Employee                           │\n");
        printf("  │  4. Update Employee Details                   │\n");
        printf("  │  5. Delete Employee                           │\n");
        printf("  │  ── Reports ──                                 │\n");
        printf("  │  6. Salary Report                             │\n");
        printf("  │  7. Department Summary                        │\n");
        printf("  │  8. Company Overview                          │\n");
        printf("  │  0. Exit                                      │\n");
        printf("  └────────────────────────────────────────────────┘\n");
        printf("  Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee();       break;
            case 2: displayAll();        break;
            case 3: searchEmployee();    break;
            case 4: updateEmployee();    break;
            case 5: deleteEmployee();    break;
            case 6: salaryReport();      break;
            case 7: departmentSummary(); break;
            case 8: companySummary();    break;
            case 0: printf("\n  Goodbye!\n\n"); break;
            default: printf("  [!] Invalid option. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}