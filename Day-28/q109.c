//wap to check library management system//
// Features: Add, Display, Search, Issue, Return, Delete books

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_LEN   100

// ──────────────────────────────────────────
// Data Structure
// ──────────────────────────────────────────

typedef struct {
    int    id;
    char   title[MAX_LEN];
    char   author[MAX_LEN];
    int    year;
    int    quantity;
    int    issued;        // number of copies currently issued
} Book;

Book library[MAX_BOOKS];
int  totalBooks = 0;

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
    printf("         📚  LIBRARY MANAGEMENT SYSTEM  📚\n");
    printLine();
}

// Find a book index by ID; returns -1 if not found
int findBookById(int id) {
    for (int i = 0; i < totalBooks; i++)
        if (library[i].id == id) return i;
    return -1;
}

// Check whether an ID already exists
int idExists(int id) {
    return findBookById(id) != -1;
}

// ──────────────────────────────────────────
// 1. Add a Book
// ──────────────────────────────────────────

void addBook() {
    if (totalBooks >= MAX_BOOKS) {
        printf("\n⚠  Library is full! Cannot add more books.\n");
        return;
    }

    Book b;
    printf("\n── Add New Book ──\n");

    printf("Enter Book ID       : ");
    scanf("%d", &b.id);
    clearInputBuffer();

    if (idExists(b.id)) {
        printf("⚠  A book with ID %d already exists.\n", b.id);
        return;
    }

    printf("Enter Title         : ");
    fgets(b.title, MAX_LEN, stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Author        : ");
    fgets(b.author, MAX_LEN, stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("Enter Year          : ");
    scanf("%d", &b.year);

    printf("Enter Quantity      : ");
    scanf("%d", &b.quantity);
    clearInputBuffer();

    b.issued = 0;

    library[totalBooks++] = b;
    printf("✔  Book \"%s\" added successfully!\n", b.title);
}

// ──────────────────────────────────────────
// 2. Display All Books
// ──────────────────────────────────────────

void displayBooks() {
    if (totalBooks == 0) {
        printf("\n⚠  No books in the library.\n");
        return;
    }

    printf("\n── All Books ──\n");
    printf("%-6s %-30s %-20s %-6s %-5s %-7s %-9s\n",
           "ID", "Title", "Author", "Year", "Qty", "Issued", "Available");
    printLine();

    for (int i = 0; i < totalBooks; i++) {
        Book *b = &library[i];
        printf("%-6d %-30s %-20s %-6d %-5d %-7d %-9d\n",
               b->id, b->title, b->author,
               b->year, b->quantity, b->issued,
               b->quantity - b->issued);
    }
    printLine();
}

// ──────────────────────────────────────────
// 3. Search a Book
// ──────────────────────────────────────────

void searchBook() {
    printf("\n── Search Book ──\n");
    printf("1. Search by ID\n");
    printf("2. Search by Title\n");
    printf("Choice: ");

    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice == 1) {
        int id;
        printf("Enter Book ID: ");
        scanf("%d", &id);
        clearInputBuffer();

        int idx = findBookById(id);
        if (idx == -1) {
            printf("⚠  Book with ID %d not found.\n", id);
            return;
        }

        Book *b = &library[idx];
        printf("\nID        : %d\n",   b->id);
        printf("Title     : %s\n",     b->title);
        printf("Author    : %s\n",     b->author);
        printf("Year      : %d\n",     b->year);
        printf("Quantity  : %d\n",     b->quantity);
        printf("Issued    : %d\n",     b->issued);
        printf("Available : %d\n",     b->quantity - b->issued);

    } else if (choice == 2) {
        char keyword[MAX_LEN];
        printf("Enter Title (or part): ");
        fgets(keyword, MAX_LEN, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';

        int found = 0;
        printf("\n%-6s %-30s %-20s %-6s %-9s\n",
               "ID", "Title", "Author", "Year", "Available");
        printLine();

        for (int i = 0; i < totalBooks; i++) {
            if (strstr(library[i].title, keyword) != NULL) {
                Book *b = &library[i];
                printf("%-6d %-30s %-20s %-6d %-9d\n",
                       b->id, b->title, b->author,
                       b->year, b->quantity - b->issued);
                found++;
            }
        }

        if (!found)
            printf("⚠  No books found matching \"%s\".\n", keyword);
        else
            printLine();

    } else {
        printf("⚠  Invalid choice.\n");
    }
}

// ──────────────────────────────────────────
// 4. Issue a Book
// ──────────────────────────────────────────

void issueBook() {
    printf("\n── Issue Book ──\n");
    printf("Enter Book ID: ");

    int id;
    scanf("%id", &id);
    clearInputBuffer();

    int idx = findBookById(id);
    if (idx == -1) {
        printf("⚠  Book with ID %d not found.\n", id);
        return;
    }

    Book *b = &library[idx];
    int available = b->quantity - b->issued;

    if (available <= 0) {
        printf("⚠  No copies of \"%s\" are available right now.\n", b->title);
        return;
    }

    b->issued++;
    printf("✔  \"%s\" issued successfully. Copies remaining: %d\n",
           b->title, b->quantity - b->issued);
}

// ──────────────────────────────────────────
// 5. Return a Book
// ──────────────────────────────────────────

void returnBook() {
    printf("\n── Return Book ──\n");
    printf("Enter Book ID: ");

    int id;
    scanf("%d", &id);
    clearInputBuffer();

    int idx = findBookById(id);
    if (idx == -1) {
        printf("⚠  Book with ID %d not found.\n", id);
        return;
    }

    Book *b = &library[idx];

    if (b->issued == 0) {
        printf("⚠  No copies of \"%s\" are currently issued.\n", b->title);
        return;
    }

    b->issued--;
    printf("✔  \"%s\" returned successfully. Copies now available: %d\n",
           b->title, b->quantity - b->issued);
}

// ──────────────────────────────────────────
// 6. Delete a Book
// ──────────────────────────────────────────

void deleteBook() {
    printf("\n── Delete Book ──\n");
    printf("Enter Book ID to delete: ");

    int id;
    scanf("%d", &id);
    clearInputBuffer();

    int idx = findBookById(id);
    if (idx == -1) {
        printf("⚠  Book with ID %d not found.\n", id);
        return;
    }

    if (library[idx].issued > 0) {
        printf("⚠  Cannot delete \"%s\" — %d copy/copies still issued.\n",
               library[idx].title, library[idx].issued);
        return;
    }

    char title[MAX_LEN];
    strcpy(title, library[idx].title);

    // Shift remaining books left
    for (int i = idx; i < totalBooks - 1; i++)
        library[i] = library[i + 1];

    totalBooks--;
    printf("✔  Book \"%s\" deleted successfully.\n", title);
}

// ──────────────────────────────────────────
// Main Menu
// ──────────────────────────────────────────

int main() {
    int choice;

    do {
        printHeader();
        printf("  1. Add Book\n");
        printf("  2. Display All Books\n");
        printf("  3. Search Book\n");
        printf("  4. Issue Book\n");
        printf("  5. Return Book\n");
        printf("  6. Delete Book\n");
        printf("  0. Exit\n");
        printLine();
        printf("  Enter your choice: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: addBook();     break;
            case 2: displayBooks();break;
            case 3: searchBook();  break;
            case 4: issueBook();   break;
            case 5: returnBook();  break;
            case 6: deleteBook();  break;
            case 0: printf("\n  Goodbye! 👋\n\n"); break;
            default: printf("\n⚠  Invalid option. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}