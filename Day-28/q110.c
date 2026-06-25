//wap to check bank account system//
// Features: Create Account, Deposit, Withdraw, Transfer, Mini Statement, Delete

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ACCOUNTS   100
#define MAX_NAME       100
#define MAX_TRANS      50      // max transactions per account
#define MAX_DESC       60

// ──────────────────────────────────────────
// Data Structures
// ──────────────────────────────────────────

typedef struct {
    char   date[20];
    char   description[MAX_DESC];
    double amount;          // +ve = credit, -ve = debit
    double balance;
} Transaction;

typedef struct {
    long        accNo;
    char        name[MAX_NAME];
    char        type[20];       // "Savings" or "Current"
    char        pin[6];         // 4-digit PIN stored as string
    double      balance;
    int         transCount;
    Transaction trans[MAX_TRANS];
} Account;

Account bank[MAX_ACCOUNTS];
int     totalAccounts = 0;

// ──────────────────────────────────────────
// Utility helpers
// ──────────────────────────────────────────

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printLine() {
    printf("─────────────────────────────────────────────────────────\n");
}

void printHeader() {
    printf("\n");
    printLine();
    printf("          🏦  BANK ACCOUNT MANAGEMENT SYSTEM  🏦\n");
    printLine();
}

// Get today's date as a string
void getDate(char *buf) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buf, 20, "%d-%m-%Y", tm);
}

// Find account index by account number; returns -1 if not found
int findAccount(long accNo) {
    for (int i = 0; i < totalAccounts; i++)
        if (bank[i].accNo == accNo) return i;
    return -1;
}

// Record a transaction
void addTransaction(int idx, const char *desc, double amount, double balance) {
    Account *a = &bank[idx];
    if (a->transCount >= MAX_TRANS) {
        // Shift oldest out to make room
        for (int i = 0; i < MAX_TRANS - 1; i++)
            a->trans[i] = a->trans[i + 1];
        a->transCount = MAX_TRANS - 1;
    }
    Transaction *t = &a->trans[a->transCount++];
    getDate(t->date);
    strncpy(t->description, desc, MAX_DESC - 1);
    t->amount  = amount;
    t->balance = balance;
}

// Verify PIN
int verifyPin(int idx) {
    char entered[10];
    printf("Enter 4-digit PIN: ");
    scanf("%4s", entered);
    clearInputBuffer();
    if (strcmp(bank[idx].pin, entered) != 0) {
        printf("❌  Incorrect PIN. Access denied.\n");
        return 0;
    }
    return 1;
}

// ──────────────────────────────────────────
// 1. Create Account
// ──────────────────────────────────────────

void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        printf("\n⚠  Bank is full. Cannot create more accounts.\n");
        return;
    }

    Account a;
    memset(&a, 0, sizeof(a));

    printf("\n── Create New Account ──\n");

    // Auto-generate account number (10-digit starting from 1000000001)
    a.accNo = 1000000001 + totalAccounts;
    printf("Account Number (auto): %ld\n", a.accNo);

    printf("Enter Full Name      : ");
    fgets(a.name, MAX_NAME, stdin);
    a.name[strcspn(a.name, "\n")] = '\0';

    printf("Account Type (1=Savings / 2=Current): ");
    int typeChoice;
    scanf("%d", &typeChoice);
    clearInputBuffer();
    strcpy(a.type, (typeChoice == 2) ? "Current" : "Savings");

    printf("Set 4-digit PIN      : ");
    scanf("%4s", a.pin);
    clearInputBuffer();

    printf("Initial Deposit (min ₹500): ₹");
    double deposit;
    scanf("%lf", &deposit);
    clearInputBuffer();

    if (deposit < 500) {
        printf("⚠  Minimum initial deposit is ₹500. Account not created.\n");
        return;
    }

    a.balance    = deposit;
    a.transCount = 0;

    bank[totalAccounts] = a;
    addTransaction(totalAccounts, "Account opened / Initial deposit", deposit, deposit);
    totalAccounts++;

    printf("\n✔  Account created successfully!\n");
    printf("   Account No : %ld\n", a.accNo);
    printf("   Name       : %s\n",  a.name);
    printf("   Type       : %s\n",  a.type);
    printf("   Balance    : ₹%.2f\n", a.balance);
}

// ──────────────────────────────────────────
// 2. Deposit Money
// ──────────────────────────────────────────

void deposit() {
    printf("\n── Deposit Money ──\n");
    printf("Enter Account Number: ");
    long accNo;
    scanf("%ld", &accNo);
    clearInputBuffer();

    int idx = findAccount(accNo);
    if (idx == -1) { printf("⚠  Account not found.\n"); return; }

    if (!verifyPin(idx)) return;

    printf("Enter Deposit Amount : ₹");
    double amount;
    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) { printf("⚠  Invalid amount.\n"); return; }

    bank[idx].balance += amount;
    addTransaction(idx, "Cash deposit", amount, bank[idx].balance);

    printf("✔  ₹%.2f deposited. New balance: ₹%.2f\n", amount, bank[idx].balance);
}

// ──────────────────────────────────────────
// 3. Withdraw Money
// ──────────────────────────────────────────

void withdraw() {
    printf("\n── Withdraw Money ──\n");
    printf("Enter Account Number: ");
    long accNo;
    scanf("%ld", &accNo);
    clearInputBuffer();

    int idx = findAccount(accNo);
    if (idx == -1) { printf("⚠  Account not found.\n"); return; }

    if (!verifyPin(idx)) return;

    printf("Enter Withdrawal Amount: ₹");
    double amount;
    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) { printf("⚠  Invalid amount.\n"); return; }

    double minBalance = (strcmp(bank[idx].type, "Savings") == 0) ? 500.0 : 1000.0;

    if (bank[idx].balance - amount < minBalance) {
        printf("⚠  Insufficient funds. Minimum balance ₹%.0f must be maintained.\n", minBalance);
        return;
    }

    bank[idx].balance -= amount;
    addTransaction(idx, "Cash withdrawal", -amount, bank[idx].balance);

    printf("✔  ₹%.2f withdrawn. Remaining balance: ₹%.2f\n", amount, bank[idx].balance);
}

// ──────────────────────────────────────────
// 4. Transfer Money
// ──────────────────────────────────────────

void transfer() {
    printf("\n── Fund Transfer ──\n");
    printf("Your Account Number     : ");
    long fromAcc;
    scanf("%ld", &fromAcc);
    clearInputBuffer();

    int fromIdx = findAccount(fromAcc);
    if (fromIdx == -1) { printf("⚠  Source account not found.\n"); return; }

    if (!verifyPin(fromIdx)) return;

    printf("Recipient Account Number: ");
    long toAcc;
    scanf("%ld", &toAcc);
    clearInputBuffer();

    if (fromAcc == toAcc) { printf("⚠  Cannot transfer to the same account.\n"); return; }

    int toIdx = findAccount(toAcc);
    if (toIdx == -1) { printf("⚠  Recipient account not found.\n"); return; }

    printf("Transfer Amount         : ₹");
    double amount;
    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) { printf("⚠  Invalid amount.\n"); return; }

    double minBalance = (strcmp(bank[fromIdx].type, "Savings") == 0) ? 500.0 : 1000.0;

    if (bank[fromIdx].balance - amount < minBalance) {
        printf("⚠  Insufficient funds for transfer.\n");
        return;
    }

    bank[fromIdx].balance -= amount;
    bank[toIdx].balance   += amount;

    char desc[MAX_DESC];
    snprintf(desc, MAX_DESC, "Transfer to Acc %ld", toAcc);
    addTransaction(fromIdx, desc, -amount, bank[fromIdx].balance);

    snprintf(desc, MAX_DESC, "Transfer from Acc %ld", fromAcc);
    addTransaction(toIdx, desc, amount, bank[toIdx].balance);

    printf("✔  ₹%.2f transferred to Account %ld successfully.\n", amount, toAcc);
    printf("   Your new balance: ₹%.2f\n", bank[fromIdx].balance);
}

// ──────────────────────────────────────────
// 5. Check Balance
// ──────────────────────────────────────────

void checkBalance() {
    printf("\n── Balance Enquiry ──\n");
    printf("Enter Account Number: ");
    long accNo;
    scanf("%ld", &accNo);
    clearInputBuffer();

    int idx = findAccount(accNo);
    if (idx == -1) { printf("⚠  Account not found.\n"); return; }

    if (!verifyPin(idx)) return;

    Account *a = &bank[idx];
    printf("\n   Account No : %ld\n",    a->accNo);
    printf("   Name       : %s\n",       a->name);
    printf("   Type       : %s\n",       a->type);
    printf("   Balance    : ₹%.2f\n",    a->balance);
}

// ──────────────────────────────────────────
// 6. Mini Statement (last 5 transactions)
// ──────────────────────────────────────────

void miniStatement() {
    printf("\n── Mini Statement ──\n");
    printf("Enter Account Number: ");
    long accNo;
    scanf("%ld", &accNo);
    clearInputBuffer();

    int idx = findAccount(accNo);
    if (idx == -1) { printf("⚠  Account not found.\n"); return; }

    if (!verifyPin(idx)) return;

    Account *a = &bank[idx];
    int show = (a->transCount < 5) ? a->transCount : 5;
    int start = a->transCount - show;

    printf("\n  Account : %ld  |  %s  |  %s\n", a->accNo, a->name, a->type);
    printLine();
    printf("  %-12s  %-28s  %10s  %12s\n",
           "Date", "Description", "Amount(₹)", "Balance(₹)");
    printLine();

    for (int i = start; i < a->transCount; i++) {
        Transaction *t = &a->trans[i];
        char sign = (t->amount >= 0) ? '+' : ' ';
        printf("  %-12s  %-28s  %c%9.2f  %12.2f\n",
               t->date, t->description, sign, t->amount, t->balance);
    }

    printLine();
    printf("  Current Balance: ₹%.2f\n", a->balance);
}

// ──────────────────────────────────────────
// 7. Display All Accounts  (admin view)
// ──────────────────────────────────────────

void displayAllAccounts() {
    if (totalAccounts == 0) {
        printf("\n⚠  No accounts found.\n");
        return;
    }

    printf("\n── All Accounts ──\n");
    printf("%-14s  %-22s  %-10s  %12s\n",
           "Account No", "Name", "Type", "Balance(₹)");
    printLine();

    for (int i = 0; i < totalAccounts; i++) {
        Account *a = &bank[i];
        printf("%-14ld  %-22s  %-10s  %12.2f\n",
               a->accNo, a->name, a->type, a->balance);
    }
    printLine();
}

// ──────────────────────────────────────────
// 8. Delete / Close Account
// ──────────────────────────────────────────

void deleteAccount() {
    printf("\n── Close Account ──\n");
    printf("Enter Account Number: ");
    long accNo;
    scanf("%ld", &accNo);
    clearInputBuffer();

    int idx = findAccount(accNo);
    if (idx == -1) { printf("⚠  Account not found.\n"); return; }

    if (!verifyPin(idx)) return;

    printf("⚠  Closing account will forfeit remaining balance ₹%.2f.\n",
           bank[idx].balance);
    printf("   Confirm? (y/n): ");
    char ch;
    scanf("%c", &ch);
    clearInputBuffer();

    if (ch != 'y' && ch != 'Y') {
        printf("   Account closure cancelled.\n");
        return;
    }

    char name[MAX_NAME];
    strcpy(name, bank[idx].name);

    for (int i = idx; i < totalAccounts - 1; i++)
        bank[i] = bank[i + 1];
    totalAccounts--;

    printf("✔  Account of \"%s\" closed successfully.\n", name);
}

// ──────────────────────────────────────────
// Main Menu
// ──────────────────────────────────────────

int main() {
    int choice;

    do {
        printHeader();
        printf("  1. Create New Account\n");
        printf("  2. Deposit Money\n");
        printf("  3. Withdraw Money\n");
        printf("  4. Transfer Money\n");
        printf("  5. Check Balance\n");
        printf("  6. Mini Statement\n");
        printf("  7. Display All Accounts\n");
        printf("  8. Close Account\n");
        printf("  0. Exit\n");
        printLine();
        printf("  Enter your choice: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: createAccount();      break;
            case 2: deposit();            break;
            case 3: withdraw();           break;
            case 4: transfer();           break;
            case 5: checkBalance();       break;
            case 6: miniStatement();      break;
            case 7: displayAllAccounts(); break;
            case 8: deleteAccount();      break;
            case 0: printf("\n  Thank you for banking with us! 👋\n\n"); break;
            default: printf("\n⚠  Invalid option. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}