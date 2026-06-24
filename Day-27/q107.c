//wap to create salary management system//
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
    char   department[MAX_DEPT_LEN];
    char   position[MAX_POS_LEN];

    // Earnings
    float  basic_salary;
    float  hra;            // House Rent Allowance   (20% of basic)
    float  da;             // Dearness Allowance     (10% of basic)
    float  medical;        // Medical Allowance      (5%  of basic)
    float  travel;         // Travel Allowance       (5%  of basic)
    float  bonus;          // Performance Bonus      (manual entry)
    float  overtime_hours;
    float  overtime_pay;   // Overtime (basic/160 * 1.5 * hours)

    // Deductions
    float  pf;             // Provident Fund         (12% of basic)
    float  esi;            // ESI                    (1.75% of gross)
    float  income_tax;     // Income Tax             (10% of gross)
    float  loan_deduction; // Loan EMI               (manual entry)

    // Summary
    float  gross_salary;
    float  total_deductions;
    float  net_salary;

    int    month;          // 1-12
    int    year;
} Employee;

// ─── Global Data ──────────────────────────────────────────────────────────────

Employee employees[MAX_EMPLOYEES];
int total_employees = 0;

// ─── Salary Calculation ───────────────────────────────────────────────────────

void calculate_salary(Employee *e) {
    // Allowances
    e->hra          = 0.20f * e->basic_salary;
    e->da           = 0.10f * e->basic_salary;
    e->medical      = 0.05f * e->basic_salary;
    e->travel       = 0.05f * e->basic_salary;
    e->overtime_pay = (e->basic_salary / 160.0f) * 1.5f * e->overtime_hours;

    // Gross
    e->gross_salary = e->basic_salary + e->hra + e->da + e->medical
                    + e->travel + e->bonus + e->overtime_pay;

    // Deductions
    e->pf           = 0.12f   * e->basic_salary;
    e->esi          = 0.0175f * e->gross_salary;
    e->income_tax   = 0.10f   * e->gross_salary;

    // Total deductions & net
    e->total_deductions = e->pf + e->esi + e->income_tax + e->loan_deduction;
    e->net_salary       = e->gross_salary - e->total_deductions;
}

// ─── Helpers ──────────────────────────────────────────────────────────────────

int find_by_id(int emp_id) {
    for (int i = 0; i < total_employees; i++)
        if (employees[i].emp_id == emp_id)
            return i;
    return -1;
}

void clear_buf() { while (getchar() != '\n'); }

const char *month_name(int m) {
    const char *months[] = {
        "", "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };
    return (m >= 1 && m <= 12) ? months[m] : "Unknown";
}

void print_line() {
    printf("═══════════════════════════════════════════════════════════════\n");
}

void print_thin() {
    printf("───────────────────────────────────────────────────────────────\n");
}

// ─── Payslip ──────────────────────────────────────────────────────────────────

void print_payslip(const Employee *e) {
    print_line();
    printf("                     SALARY SLIP\n");
    print_thin();
    printf("  Emp ID     : %-10d   Month : %s %d\n",
           e->emp_id, month_name(e->month), e->year);
    printf("  Name       : %-28s\n", e->name);
    printf("  Department : %-20s   Post  : %s\n", e->department, e->position);
    print_thin();

    // Earnings column
    printf("  %-30s  %-30s\n", "EARNINGS", "DEDUCTIONS");
    print_thin();
    printf("  %-28s %6.2f  %-22s %8.2f\n",
           "Basic Salary    :", e->basic_salary,
           "Provident Fund  :", e->pf);
    printf("  %-28s %6.2f  %-22s %8.2f\n",
           "HRA (20%)       :", e->hra,
           "ESI (1.75%)     :", e->esi);
    printf("  %-28s %6.2f  %-22s %8.2f\n",
           "DA  (10%)       :", e->da,
           "Income Tax(10%) :", e->income_tax);
    printf("  %-28s %6.2f  %-22s %8.2f\n",
           "Medical (5%)    :", e->medical,
           "Loan Deduction  :", e->loan_deduction);
    printf("  %-28s %6.2f\n",
           "Travel  (5%)    :", e->travel);
    printf("  %-28s %6.2f\n",
           "Bonus           :", e->bonus);
    printf("  %-28s %6.2f\n",
           "Overtime Pay    :", e->overtime_pay);
    print_thin();
    printf("  %-28s %6.2f  %-22s %8.2f\n",
           "GROSS SALARY    :", e->gross_salary,
           "TOTAL DEDUCTIONS:", e->total_deductions);
    print_line();
    printf("              NET SALARY (Take-Home): Rs. %.2f\n", e->net_salary);
    print_line();
}

// ─── Operations ───────────────────────────────────────────────────────────────

void add_employee() {
    if (total_employees >= MAX_EMPLOYEES) {
        printf("\nError: Maximum employee limit reached!\n");
        return;
    }

    Employee e;
    memset(&e, 0, sizeof(Employee));

    printf("\n─── Add Employee Salary Record ───\n");

    printf("Employee ID         : ");
    scanf("%d", &e.emp_id);
    if (find_by_id(e.emp_id) != -1) {
        printf("Error: Employee ID %d already exists!\n", e.emp_id);
        return;
    }

    clear_buf();
    printf("Name                : ");
    fgets(e.name, MAX_NAME_LEN, stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("Department          : ");
    fgets(e.department, MAX_DEPT_LEN, stdin);
    e.department[strcspn(e.department, "\n")] = '\0';

    printf("Position            : ");
    fgets(e.position, MAX_POS_LEN, stdin);
    e.position[strcspn(e.position, "\n")] = '\0';

    printf("Basic Salary (Rs.)  : ");
    scanf("%f", &e.basic_salary);

    printf("Bonus (Rs.)         : ");
    scanf("%f", &e.bonus);

    printf("Overtime Hours      : ");
    scanf("%f", &e.overtime_hours);

    printf("Loan Deduction (Rs.): ");
    scanf("%f", &e.loan_deduction);

    printf("Month (1-12)        : ");
    scanf("%d", &e.month);

    printf("Year                : ");
    scanf("%d", &e.year);

    calculate_salary(&e);
    employees[total_employees++] = e;

    printf("\nRecord added successfully!\n");
    print_payslip(&e);
}

void view_all() {
    if (total_employees == 0) {
        printf("\nNo records found.\n");
        return;
    }
    printf("\n─── All Employee Salary Records (%d total) ───\n\n", total_employees);
    printf("%-6s %-22s %-15s %-12s %-12s %-12s\n",
           "ID", "Name", "Department", "Gross", "Deductions", "Net Salary");
    print_thin();
    for (int i = 0; i < total_employees; i++) {
        printf("%-6d %-22s %-15s Rs.%-9.2f Rs.%-9.2f Rs.%-9.2f\n",
               employees[i].emp_id,
               employees[i].name,
               employees[i].department,
               employees[i].gross_salary,
               employees[i].total_deductions,
               employees[i].net_salary);
    }
    print_thin();
}

void generate_payslip() {
    int emp_id;
    printf("\n─── Generate Payslip ───\n");
    printf("Enter Employee ID: ");
    scanf("%d", &emp_id);

    int idx = find_by_id(emp_id);
    if (idx == -1) {
        printf("Employee ID %d not found.\n", emp_id);
        return;
    }
    print_payslip(&employees[idx]);
}

void update_salary() {
    int emp_id;
    printf("\n─── Update Salary Record ───\n");
    printf("Enter Employee ID: ");
    scanf("%d", &emp_id);

    int idx = find_by_id(emp_id);
    if (idx == -1) {
        printf("Employee ID %d not found.\n", emp_id);
        return;
    }

    Employee *e = &employees[idx];
    printf("\nCurrent record for: %s\n", e->name);

    printf("1. Basic Salary    2. Bonus\n");
    printf("3. Overtime Hours  4. Loan Deduction\n");
    printf("5. Month/Year      6. All\n");
    printf("Choice: ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1 || choice == 6) {
        printf("New Basic Salary: ");
        scanf("%f", &e->basic_salary);
    }
    if (choice == 2 || choice == 6) {
        printf("New Bonus: ");
        scanf("%f", &e->bonus);
    }
    if (choice == 3 || choice == 6) {
        printf("New Overtime Hours: ");
        scanf("%f", &e->overtime_hours);
    }
    if (choice == 4 || choice == 6) {
        printf("New Loan Deduction: ");
        scanf("%f", &e->loan_deduction);
    }
    if (choice == 5 || choice == 6) {
        printf("New Month (1-12): ");
        scanf("%d", &e->month);
        printf("New Year: ");
        scanf("%d", &e->year);
    }

    calculate_salary(e);
    printf("\nSalary updated successfully!\n");
    print_payslip(e);
}

void delete_record() {
    int emp_id;
    printf("\n─── Delete Salary Record ───\n");
    printf("Enter Employee ID: ");
    scanf("%d", &emp_id);

    int idx = find_by_id(emp_id);
    if (idx == -1) {
        printf("Employee ID %d not found.\n", emp_id);
        return;
    }

    printf("Confirm delete '%s' (ID: %d)? (y/n): ",
           employees[idx].name, emp_id);
    char c;
    scanf(" %c", &c);

    if (c == 'y' || c == 'Y') {
        for (int i = idx; i < total_employees - 1; i++)
            employees[i] = employees[i + 1];
        total_employees--;
        printf("Record deleted.\n");
    } else {
        printf("Cancelled.\n");
    }
}

void search_by_department() {
    char dept[MAX_DEPT_LEN];
    printf("\n─── Search by Department ───\n");
    clear_buf();
    printf("Enter Department: ");
    fgets(dept, MAX_DEPT_LEN, stdin);
    dept[strcspn(dept, "\n")] = '\0';

    int found = 0;
    printf("\nEmployees in '%s':\n", dept);
    print_thin();
    printf("%-6s %-22s %-12s %-12s\n", "ID", "Name", "Gross", "Net Salary");
    print_thin();

    for (int i = 0; i < total_employees; i++) {
        if (strcasecmp(employees[i].department, dept) == 0) {
            printf("%-6d %-22s Rs.%-9.2f Rs.%-9.2f\n",
                   employees[i].emp_id,
                   employees[i].name,
                   employees[i].gross_salary,
                   employees[i].net_salary);
            found++;
        }
    }
    if (!found) printf("No employees found in '%s'.\n", dept);
    else        printf("\nTotal: %d employee(s)\n", found);
}

void salary_report() {
    if (total_employees == 0) {
        printf("\nNo records available.\n");
        return;
    }

    float total_gross = 0, total_net = 0, total_ded = 0;
    float max_net = employees[0].net_salary;
    float min_net = employees[0].net_salary;
    int   max_idx = 0, min_idx = 0;

    for (int i = 0; i < total_employees; i++) {
        total_gross += employees[i].gross_salary;
        total_net   += employees[i].net_salary;
        total_ded   += employees[i].total_deductions;
        if (employees[i].net_salary > max_net) { max_net = employees[i].net_salary; max_idx = i; }
        if (employees[i].net_salary < min_net) { min_net = employees[i].net_salary; min_idx = i; }
    }

    print_line();
    printf("                   SALARY REPORT\n");
    print_thin();
    printf("  Total Employees        : %d\n",        total_employees);
    printf("  Total Gross Salary     : Rs. %.2f\n",  total_gross);
    printf("  Total Deductions       : Rs. %.2f\n",  total_ded);
    printf("  Total Net Salary Bill  : Rs. %.2f\n",  total_net);
    printf("  Average Net Salary     : Rs. %.2f\n",  total_net / total_employees);
    print_thin();
    printf("  Highest Paid : %s (Rs. %.2f)\n",
           employees[max_idx].name, max_net);
    printf("  Lowest  Paid : %s (Rs. %.2f)\n",
           employees[min_idx].name, min_net);
    print_line();
}

void increment_salary() {
    int emp_id;
    float percent;
    printf("\n─── Apply Salary Increment ───\n");
    printf("Enter Employee ID (0 = All): ");
    scanf("%d", &emp_id);
    printf("Increment Percentage      : ");
    scanf("%f", &percent);

    if (emp_id == 0) {
        for (int i = 0; i < total_employees; i++) {
            employees[i].basic_salary += employees[i].basic_salary * (percent / 100.0f);
            calculate_salary(&employees[i]);
        }
        printf("%.1f%% increment applied to all %d employees.\n",
               percent, total_employees);
    } else {
        int idx = find_by_id(emp_id);
        if (idx == -1) { printf("Employee not found.\n"); return; }
        employees[idx].basic_salary += employees[idx].basic_salary * (percent / 100.0f);
        calculate_salary(&employees[idx]);
        printf("%.1f%% increment applied to %s. New basic: Rs. %.2f\n",
               percent, employees[idx].name, employees[idx].basic_salary);
    }
}

// ─── File I/O ─────────────────────────────────────────────────────────────────

void save_to_file() {
    FILE *fp = fopen("salary.dat", "wb");
    if (!fp) { printf("Error saving file.\n"); return; }
    fwrite(&total_employees, sizeof(int), 1, fp);
    fwrite(employees, sizeof(Employee), total_employees, fp);
    fclose(fp);
    printf("Records saved to 'salary.dat'.\n");
}

void load_from_file() {
    FILE *fp = fopen("salary.dat", "rb");
    if (!fp) { printf("No saved data. Starting fresh.\n"); return; }
    fread(&total_employees, sizeof(int), 1, fp);
    fread(employees, sizeof(Employee), total_employees, fp);
    fclose(fp);
    printf("Loaded %d record(s) from file.\n", total_employees);
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    print_line();
    printf("            SALARY MANAGEMENT SYSTEM\n");
    print_line();
    load_from_file();

    int choice;
    do {
        printf("\n  MENU\n");
        printf("  1.  Add Employee Salary Record\n");
        printf("  2.  View All Records\n");
        printf("  3.  Generate Payslip\n");
        printf("  4.  Update Salary Record\n");
        printf("  5.  Delete Record\n");
        printf("  6.  Search by Department\n");
        printf("  7.  Salary Report\n");
        printf("  8.  Apply Salary Increment\n");
        printf("  9.  Save Records\n");
        printf("  0.  Exit\n");
        printf("\n  Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_employee();        break;
            case 2: view_all();            break;
            case 3: generate_payslip();    break;
            case 4: update_salary();       break;
            case 5: delete_record();       break;
            case 6: search_by_department(); break;
            case 7: salary_report();       break;
            case 8: increment_salary();    break;
            case 9: save_to_file();        break;
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