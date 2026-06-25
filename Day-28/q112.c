//wap to create contact management system //
// Features: Add, Display, Search, Edit, Delete, Favourite, Export

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTACTS  200
#define MAX_NAME       80
#define MAX_PHONE      15
#define MAX_EMAIL      80
#define MAX_ADDRESS   120
#define MAX_GROUP      30

// ──────────────────────────────────────────
// Data Structure
// ──────────────────────────────────────────

typedef struct {
    int  id;
    char firstName[MAX_NAME];
    char lastName[MAX_NAME];
    char phone[MAX_PHONE];
    char altPhone[MAX_PHONE];
    char email[MAX_EMAIL];
    char address[MAX_ADDRESS];
    char group[MAX_GROUP];      // Family / Friend / Work / Other
    int  favourite;             // 1 = yes, 0 = no
} Contact;

Contact contacts[MAX_CONTACTS];
int     totalContacts = 0;
int     nextId        = 1;

// ──────────────────────────────────────────
// Utility Helpers
// ──────────────────────────────────────────

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printLine() {
    printf("─────────────────────────────────────────────────────────────\n");
}

void printHeader() {
    printf("\n");
    printLine();
    printf("          📒  CONTACT MANAGEMENT SYSTEM  📒\n");
    printLine();
}

// Convert string to lowercase for case-insensitive search
void toLowerStr(char *dest, const char *src) {
    int i;
    for (i = 0; src[i]; i++)
        dest[i] = tolower((unsigned char)src[i]);
    dest[i] = '\0';
}

// Find contact index by ID; returns -1 if not found
int findById(int id) {
    for (int i = 0; i < totalContacts; i++)
        if (contacts[i].id == id) return i;
    return -1;
}

// Print a single contact card
void printContact(Contact *c) {
    printLine();
    printf("  ID          : %d  %s\n", c->id, c->favourite ? "⭐ Favourite" : "");
    printf("  Name        : %s %s\n",  c->firstName, c->lastName);
    printf("  Phone       : %s\n",     c->phone);
    if (strlen(c->altPhone) > 0)
        printf("  Alt Phone   : %s\n", c->altPhone);
    if (strlen(c->email) > 0)
        printf("  Email       : %s\n", c->email);
    if (strlen(c->address) > 0)
        printf("  Address     : %s\n", c->address);
    printf("  Group       : %s\n",     c->group);
    printLine();
}

// ──────────────────────────────────────────
// 1. Add Contact
// ──────────────────────────────────────────

void addContact() {
    if (totalContacts >= MAX_CONTACTS) {
        printf("\n⚠  Contact list is full.\n");
        return;
    }

    Contact c;
    memset(&c, 0, sizeof(c));
    c.id        = nextId++;
    c.favourite = 0;

    printf("\n── Add New Contact ──\n");
    printf("First Name       : ");
    fgets(c.firstName, MAX_NAME, stdin);
    c.firstName[strcspn(c.firstName, "\n")] = '\0';

    printf("Last Name        : ");
    fgets(c.lastName, MAX_NAME, stdin);
    c.lastName[strcspn(c.lastName, "\n")] = '\0';

    printf("Phone Number     : ");
    scanf("%14s", c.phone);
    clearInputBuffer();

    printf("Alt Phone (Enter to skip): ");
    fgets(c.altPhone, MAX_PHONE, stdin);
    c.altPhone[strcspn(c.altPhone, "\n")] = '\0';

    printf("Email (Enter to skip): ");
    fgets(c.email, MAX_EMAIL, stdin);
    c.email[strcspn(c.email, "\n")] = '\0';

    printf("Address (Enter to skip): ");
    fgets(c.address, MAX_ADDRESS, stdin);
    c.address[strcspn(c.address, "\n")] = '\0';

    printf("Group\n  1. Family  2. Friend  3. Work  4. Other\n  Choice: ");
    int grp;
    scanf("%d", &grp);
    clearInputBuffer();
    switch (grp) {
        case 1:  strcpy(c.group, "Family"); break;
        case 2:  strcpy(c.group, "Friend"); break;
        case 3:  strcpy(c.group, "Work");   break;
        default: strcpy(c.group, "Other");
    }

    printf("Mark as Favourite? (y/n): ");
    char ch;
    scanf("%c", &ch);
    clearInputBuffer();
    c.favourite = (ch == 'y' || ch == 'Y') ? 1 : 0;

    contacts[totalContacts++] = c;
    printf("\n✔  Contact \"%s %s\" saved! (ID: %d)\n", c.firstName, c.lastName, c.id);
}

// ──────────────────────────────────────────
// 2. Display All Contacts (sorted by first name)
// ──────────────────────────────────────────

// Simple bubble sort by first name
void sortByName() {
    for (int i = 0; i < totalContacts - 1; i++)
        for (int j = 0; j < totalContacts - i - 1; j++)
            if (strcmp(contacts[j].firstName, contacts[j + 1].firstName) > 0) {
                Contact tmp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = tmp;
            }
}

void displayAll() {
    if (totalContacts == 0) {
        printf("\n⚠  No contacts found.\n");
        return;
    }

    sortByName();

    printf("\n── All Contacts (%d) ──\n", totalContacts);
    printf("%-4s  %-20s  %-14s  %-22s  %-8s  %s\n",
           "ID", "Name", "Phone", "Email", "Group", "Fav");
    printLine();

    for (int i = 0; i < totalContacts; i++) {
        Contact *c = &contacts[i];
        char fullName[MAX_NAME * 2];
        snprintf(fullName, sizeof(fullName), "%s %s", c->firstName, c->lastName);
        printf("%-4d  %-20s  %-14s  %-22s  %-8s  %s\n",
               c->id, fullName, c->phone, c->email, c->group,
               c->favourite ? "⭐" : "");
    }
    printLine();
}

// ──────────────────────────────────────────
// 3. Search Contact
// ──────────────────────────────────────────

void searchContact() {
    printf("\n── Search Contact ──\n");
    printf("  1. By Name\n  2. By Phone\n  3. By Email\n  4. By Group\n");
    printf("  Choice: ");
    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    char keyword[MAX_NAME], kwLow[MAX_NAME];
    int  found = 0;

    if (choice == 1) {
        printf("Enter name (or part): ");
        fgets(keyword, MAX_NAME, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';
        toLowerStr(kwLow, keyword);

        for (int i = 0; i < totalContacts; i++) {
            char fullName[MAX_NAME * 2], fnLow[MAX_NAME * 2];
            snprintf(fullName, sizeof(fullName), "%s %s",
                     contacts[i].firstName, contacts[i].lastName);
            toLowerStr(fnLow, fullName);
            if (strstr(fnLow, kwLow)) {
                printContact(&contacts[i]);
                found++;
            }
        }

    } else if (choice == 2) {
        printf("Enter phone number: ");
        scanf("%14s", keyword);
        clearInputBuffer();
        for (int i = 0; i < totalContacts; i++)
            if (strstr(contacts[i].phone, keyword) ||
                strstr(contacts[i].altPhone, keyword)) {
                printContact(&contacts[i]);
                found++;
            }

    } else if (choice == 3) {
        printf("Enter email (or part): ");
        fgets(keyword, MAX_EMAIL, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';
        toLowerStr(kwLow, keyword);
        for (int i = 0; i < totalContacts; i++) {
            char emLow[MAX_EMAIL];
            toLowerStr(emLow, contacts[i].email);
            if (strstr(emLow, kwLow)) {
                printContact(&contacts[i]);
                found++;
            }
        }

    } else if (choice == 4) {
        printf("Group (Family/Friend/Work/Other): ");
        fgets(keyword, MAX_GROUP, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';
        toLowerStr(kwLow, keyword);
        for (int i = 0; i < totalContacts; i++) {
            char grpLow[MAX_GROUP];
            toLowerStr(grpLow, contacts[i].group);
            if (strstr(grpLow, kwLow)) {
                printContact(&contacts[i]);
                found++;
            }
        }

    } else {
        printf("⚠  Invalid choice.\n");
        return;
    }

    if (!found)
        printf("⚠  No contacts matched your search.\n");
    else
        printf("  %d contact(s) found.\n", found);
}

// ──────────────────────────────────────────
// 4. View Contact Detail by ID
// ──────────────────────────────────────────

void viewContact() {
    printf("\n── View Contact ──\n");
    printf("Enter Contact ID: ");
    int id;
    scanf("%d", &id);
    clearInputBuffer();

    int idx = findById(id);
    if (idx == -1) { printf("⚠  Contact not found.\n"); return; }

    printContact(&contacts[idx]);
}

// ──────────────────────────────────────────
// 5. Edit Contact
// ──────────────────────────────────────────

void editContact() {
    printf("\n── Edit Contact ──\n");
    printf("Enter Contact ID to edit: ");
    int id;
    scanf("%d", &id);
    clearInputBuffer();

    int idx = findById(id);
    if (idx == -1) { printf("⚠  Contact not found.\n"); return; }

    Contact *c = &contacts[idx];
    printf("Editing: %s %s\n", c->firstName, c->lastName);
    printf("(Press Enter to keep existing value)\n\n");

    char buf[MAX_ADDRESS];

    printf("First Name [%s]: ", c->firstName);
    fgets(buf, MAX_NAME, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(c->firstName, buf);

    printf("Last Name  [%s]: ", c->lastName);
    fgets(buf, MAX_NAME, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(c->lastName, buf);

    printf("Phone      [%s]: ", c->phone);
    fgets(buf, MAX_PHONE, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(c->phone, buf);

    printf("Alt Phone  [%s]: ", c->altPhone);
    fgets(buf, MAX_PHONE, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(c->altPhone, buf);

    printf("Email      [%s]: ", c->email);
    fgets(buf, MAX_EMAIL, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(c->email, buf);

    printf("Address    [%s]: ", c->address);
    fgets(buf, MAX_ADDRESS, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(c->address, buf);

    printf("Group (Family/Friend/Work/Other) [%s]: ", c->group);
    fgets(buf, MAX_GROUP, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(c->group, buf);

    printf("Favourite? (y/n) [%s]: ", c->favourite ? "y" : "n");
    fgets(buf, 4, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0)
        c->favourite = (buf[0] == 'y' || buf[0] == 'Y') ? 1 : 0;

    printf("\n✔  Contact updated successfully!\n");
    printContact(c);
}

// ──────────────────────────────────────────
// 6. Delete Contact
// ──────────────────────────────────────────

void deleteContact() {
    printf("\n── Delete Contact ──\n");
    printf("Enter Contact ID: ");
    int id;
    scanf("%d", &id);
    clearInputBuffer();

    int idx = findById(id);
    if (idx == -1) { printf("⚠  Contact not found.\n"); return; }

    printf("Delete \"%s %s\"? (y/n): ",
           contacts[idx].firstName, contacts[idx].lastName);
    char ch;
    scanf("%c", &ch);
    clearInputBuffer();

    if (ch != 'y' && ch != 'Y') {
        printf("  Deletion cancelled.\n");
        return;
    }

    char name[MAX_NAME * 2];
    snprintf(name, sizeof(name), "%s %s",
             contacts[idx].firstName, contacts[idx].lastName);

    for (int i = idx; i < totalContacts - 1; i++)
        contacts[i] = contacts[i + 1];
    totalContacts--;

    printf("✔  Contact \"%s\" deleted.\n", name);
}

// ──────────────────────────────────────────
// 7. View Favourites
// ──────────────────────────────────────────

void viewFavourites() {
    printf("\n── ⭐ Favourite Contacts ──\n");
    int found = 0;

    printf("%-4s  %-20s  %-14s  %-8s\n", "ID", "Name", "Phone", "Group");
    printLine();

    for (int i = 0; i < totalContacts; i++) {
        if (contacts[i].favourite) {
            Contact *c = &contacts[i];
            char fullName[MAX_NAME * 2];
            snprintf(fullName, sizeof(fullName), "%s %s",
                     c->firstName, c->lastName);
            printf("%-4d  %-20s  %-14s  %-8s\n",
                   c->id, fullName, c->phone, c->group);
            found++;
        }
    }

    if (!found)
        printf("  No favourite contacts yet.\n");
    printLine();
}

// ──────────────────────────────────────────
// 8. Contact Statistics
// ──────────────────────────────────────────

void statistics() {
    printf("\n── Contact Statistics ──\n");
    int family = 0, friend_ = 0, work = 0, other = 0, fav = 0;

    for (int i = 0; i < totalContacts; i++) {
        if (strcmp(contacts[i].group, "Family") == 0) family++;
        else if (strcmp(contacts[i].group, "Friend") == 0) friend_++;
        else if (strcmp(contacts[i].group, "Work")   == 0) work++;
        else other++;
        if (contacts[i].favourite) fav++;
    }

    printLine();
    printf("  Total Contacts  : %d\n", totalContacts);
    printf("  Favourites      : %d\n", fav);
    printf("  ─────────────────\n");
    printf("  Family          : %d\n", family);
    printf("  Friend          : %d\n", friend_);
    printf("  Work            : %d\n", work);
    printf("  Other           : %d\n", other);
    printLine();
}

// ──────────────────────────────────────────
// 9. Export Contacts to CSV
// ──────────────────────────────────────────

void exportCSV() {
    const char *filename = "contacts_export.csv";
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("⚠  Could not create file.\n");
        return;
    }

    fprintf(fp, "ID,FirstName,LastName,Phone,AltPhone,Email,Address,Group,Favourite\n");
    for (int i = 0; i < totalContacts; i++) {
        Contact *c = &contacts[i];
        fprintf(fp, "%d,%s,%s,%s,%s,%s,\"%s\",%s,%s\n",
                c->id, c->firstName, c->lastName,
                c->phone, c->altPhone, c->email,
                c->address, c->group,
                c->favourite ? "Yes" : "No");
    }

    fclose(fp);
    printf("✔  %d contact(s) exported to \"%s\".\n", totalContacts, filename);
}

// ──────────────────────────────────────────
// Main Menu
// ──────────────────────────────────────────

int main() {
    // Pre-load 3 sample contacts
    Contact s1 = {1, "Rahul",  "Kumar",  "9876543210", "",           "rahul@email.com",  "Patna, Bihar",   "Family", 1};
    Contact s2 = {2, "Priya",  "Sharma", "9123456780", "9012345678", "priya@gmail.com",  "Delhi",           "Friend", 1};
    Contact s3 = {3, "Amit",   "Singh",  "8001234567", "",           "amit@company.com", "Mumbai",          "Work",   0};
    contacts[0] = s1; contacts[1] = s2; contacts[2] = s3;
    totalContacts = 3; nextId = 4;

    int choice;

    do {
        printHeader();
        printf("  1. Add Contact\n");
        printf("  2. Display All Contacts\n");
        printf("  3. Search Contact\n");
        printf("  4. View Contact Detail\n");
        printf("  5. Edit Contact\n");
        printf("  6. Delete Contact\n");
        printf("  7. Favourite Contacts\n");
        printf("  8. Statistics\n");
        printf("  9. Export to CSV\n");
        printf("  0. Exit\n");
        printLine();
        printf("  Enter your choice: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addContact();    break;
            case 2: displayAll();    break;
            case 3: searchContact(); break;
            case 4: viewContact();   break;
            case 5: editContact();   break;
            case 6: deleteContact(); break;
            case 7: viewFavourites();break;
            case 8: statistics();    break;
            case 9: exportCSV();     break;
            case 0: printf("\n  Goodbye! 👋\n\n"); break;
            default: printf("\n⚠  Invalid option. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}