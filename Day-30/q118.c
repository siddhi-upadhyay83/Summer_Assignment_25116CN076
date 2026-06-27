//wap to create mini library system//
/*
 * Features: Add, Display, Search, Issue, Return, Delete books
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS    100
#define MAX_MEMBERS   50
#define TITLE_LEN     60
#define AUTHOR_LEN    40
#define NAME_LEN      40
#define GENRE_LEN     20

/* ─── Data Structures ────────────────────────────────────────────────── */

struct Book {
    int  book_id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    char genre[GENRE_LEN];
    int  year;
    int  total_copies;
    int  available_copies;
};

struct Member {
    int  member_id;
    char name[NAME_LEN];
    int  issued_book_id;   /* 0 = no book issued */
    char issued_title[TITLE_LEN];
};

/* ─── Global Storage ─────────────────────────────────────────────────── */

struct Book   books[MAX_BOOKS];
struct Member members[MAX_MEMBERS];
int book_count   = 0;
int member_count = 0;

/* ─── Helper Functions ───────────────────────────────────────────────── */

void printLine(void) {
    printf("--------------------------------------------------------------------------------\n");
}

int findBook(int id) {
    for (int i = 0; i < book_count; i++)
        if (books[i].book_id == id) return i;
    return -1;
}

int findMember(int id) {
    for (int i = 0; i < member_count; i++)
        if (members[i].member_id == id) return i;
    return -1;
}

/* ─── Book Operations ────────────────────────────────────────────────── */

void addBook(void) {
    if (book_count >= MAX_BOOKS) {
        printf("\n  [!] Library is full. Cannot add more books.\n");
        return;
    }

    struct Book b;
    printf("\n  Enter Book ID     : ");
    scanf("%d", &b.book_id);

    if (findBook(b.book_id) != -1) {
        printf("  [!] Book ID %d already exists.\n", b.book_id);
        return;
    }

    printf("  Enter Title       : ");
    scanf(" %[^\n]", b.title);

    printf("  Enter Author      : ");
    scanf(" %[^\n]", b.author);

    printf("  Enter Genre       : ");
    scanf(" %[^\n]", b.genre);

    printf("  Publication Year  : ");
    scanf("%d", &b.year);

    printf("  Total Copies      : ");
    scanf("%d", &b.total_copies);

    b.available_copies = b.total_copies;

    books[book_count++] = b;
    printf("\n  [✓] Book added successfully!\n");
}

void displayAllBooks(void) {
    if (book_count == 0) {
        printf("\n  No books in library.\n");
        return;
    }

    printf("\n  ╔══════════════════════════════ LIBRARY CATALOG ═══════════════════════════════╗\n");
    printf("  %-6s %-30s %-20s %-12s %-6s %-5s %-5s\n",
           "ID", "Title", "Author", "Genre", "Year", "Total", "Avail");
    printLine();
    for (int i = 0; i < book_count; i++) {
        struct Book *b = &books[i];
        printf("  %-6d %-30s %-20s %-12s %-6d %-5d %-5d\n",
               b->book_id, b->title, b->author,
               b->genre, b->year,
               b->total_copies, b->available_copies);
    }
    printLine();
    printf("  Total books in catalog: %d\n", book_count);
}

void searchBook(void) {
    int choice;
    printf("\n  Search by:\n");
    printf("  1. Book ID\n");
    printf("  2. Title (keyword)\n");
    printf("  3. Author (keyword)\n");
    printf("  Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("  Enter Book ID: ");
        scanf("%d", &id);
        int idx = findBook(id);
        if (idx == -1) { printf("  [!] Book not found.\n"); return; }
        struct Book *b = &books[idx];
        printf("\n  ── Book Details ──────────────────────────────\n");
        printf("  ID          : %d\n",   b->book_id);
        printf("  Title       : %s\n",   b->title);
        printf("  Author      : %s\n",   b->author);
        printf("  Genre       : %s\n",   b->genre);
        printf("  Year        : %d\n",   b->year);
        printf("  Total Copies: %d\n",   b->total_copies);
        printf("  Available   : %d\n",   b->available_copies);
        printf("  Status      : %s\n",   b->available_copies > 0 ? "Available" : "All Issued");
        printf("  ─────────────────────────────────────────────\n");
    }
    else if (choice == 2 || choice == 3) {
        char keyword[TITLE_LEN];
        printf("  Enter keyword: ");
        scanf(" %[^\n]", keyword);

        int found = 0;
        printf("\n  %-6s %-30s %-20s %-5s\n", "ID", "Title", "Author", "Avail");
        printLine();
        for (int i = 0; i < book_count; i++) {
            char *field = (choice == 2) ? books[i].title : books[i].author;
            /* simple case-insensitive substring search */
            char lf[TITLE_LEN], lk[TITLE_LEN];
            for (int j = 0; (lf[j] = (field[j] >= 'A' && field[j] <= 'Z')
                              ? field[j] + 32 : field[j]); j++);
            for (int j = 0; (lk[j] = (keyword[j] >= 'A' && keyword[j] <= 'Z')
                              ? keyword[j] + 32 : keyword[j]); j++);
            if (strstr(lf, lk)) {
                printf("  %-6d %-30s %-20s %-5d\n",
                       books[i].book_id, books[i].title,
                       books[i].author, books[i].available_copies);
                found++;
            }
        }
        if (!found) printf("  No matching books found.\n");
        else printf("  %d result(s) found.\n", found);
    }
    else {
        printf("  [!] Invalid choice.\n");
    }
}

void deleteBook(void) {
    int id;
    printf("\n  Enter Book ID to delete: ");
    scanf("%d", &id);

    int idx = findBook(id);
    if (idx == -1) { printf("  [!] Book not found.\n"); return; }

    if (books[idx].available_copies < books[idx].total_copies) {
        printf("  [!] Cannot delete — some copies are currently issued.\n");
        return;
    }

    for (int i = idx; i < book_count - 1; i++)
        books[i] = books[i + 1];
    book_count--;
    printf("  [✓] Book deleted from catalog.\n");
}

/* ─── Member Operations ──────────────────────────────────────────────── */

void addMember(void) {
    if (member_count >= MAX_MEMBERS) {
        printf("\n  [!] Member list full.\n");
        return;
    }

    struct Member m;
    printf("\n  Enter Member ID   : ");
    scanf("%d", &m.member_id);

    if (findMember(m.member_id) != -1) {
        printf("  [!] Member ID %d already exists.\n", m.member_id);
        return;
    }

    printf("  Enter Name        : ");
    scanf(" %[^\n]", m.name);

    m.issued_book_id = 0;
    strcpy(m.issued_title, "None");

    members[member_count++] = m;
    printf("\n  [✓] Member registered successfully!\n");
}

void displayAllMembers(void) {
    if (member_count == 0) {
        printf("\n  No members registered.\n");
        return;
    }

    printf("\n  ╔══════════════════════════════ MEMBER LIST ══════════════════════════════════╗\n");
    printf("  %-8s %-25s %-10s %-30s\n",
           "Mem ID", "Name", "Book ID", "Issued Book");
    printLine();
    for (int i = 0; i < member_count; i++) {
        struct Member *m = &members[i];
        printf("  %-8d %-25s %-10s %-30s\n",
               m->member_id, m->name,
               m->issued_book_id ? "" : "—",
               m->issued_title);
        /* print book id only if issued */
        if (m->issued_book_id) {
            /* reprint with book id */
            printf("\033[1A");   /* move up one line */
            printf("  %-8d %-25s %-10d %-30s\n",
                   m->member_id, m->name,
                   m->issued_book_id, m->issued_title);
        }
    }
    printLine();
    printf("  Total members: %d\n", member_count);
}

/* ─── Issue / Return ─────────────────────────────────────────────────── */

void issueBook(void) {
    int mid, bid;
    printf("\n  Enter Member ID : ");
    scanf("%d", &mid);
    int mi = findMember(mid);
    if (mi == -1) { printf("  [!] Member not found.\n"); return; }

    if (members[mi].issued_book_id != 0) {
        printf("  [!] Member already has a book issued: \"%s\"\n",
               members[mi].issued_title);
        printf("      Please return it before issuing another.\n");
        return;
    }

    printf("  Enter Book ID   : ");
    scanf("%d", &bid);
    int bi = findBook(bid);
    if (bi == -1) { printf("  [!] Book not found.\n"); return; }

    if (books[bi].available_copies <= 0) {
        printf("  [!] No copies available for \"%s\".\n", books[bi].title);
        return;
    }

    books[bi].available_copies--;
    members[mi].issued_book_id = bid;
    strcpy(members[mi].issued_title, books[bi].title);

    printf("\n  [✓] Book Issued!\n");
    printf("      Member : %s (ID: %d)\n", members[mi].name, mid);
    printf("      Book   : \"%s\" (ID: %d)\n", books[bi].title, bid);
    printf("      Copies remaining: %d\n", books[bi].available_copies);
}

void returnBook(void) {
    int mid;
    printf("\n  Enter Member ID : ");
    scanf("%d", &mid);
    int mi = findMember(mid);
    if (mi == -1) { printf("  [!] Member not found.\n"); return; }

    if (members[mi].issued_book_id == 0) {
        printf("  [!] %s has no book issued.\n", members[mi].name);
        return;
    }

    int bi = findBook(members[mi].issued_book_id);
    if (bi != -1)
        books[bi].available_copies++;

    printf("\n  [✓] Book Returned!\n");
    printf("      Member : %s (ID: %d)\n", members[mi].name, mid);
    printf("      Book   : \"%s\"\n", members[mi].issued_title);

    members[mi].issued_book_id = 0;
    strcpy(members[mi].issued_title, "None");
}

/* ─── Library Summary ────────────────────────────────────────────────── */

void librarySummary(void) {
    int total = 0, available = 0, issued = 0;
    for (int i = 0; i < book_count; i++) {
        total     += books[i].total_copies;
        available += books[i].available_copies;
        issued    += (books[i].total_copies - books[i].available_copies);
    }

    int active_members = 0;
    for (int i = 0; i < member_count; i++)
        if (members[i].issued_book_id) active_members++;

    printf("\n  ╔══════════════ LIBRARY SUMMARY ══════════════╗\n");
    printf("  ║  Total Book Titles   : %-4d                 ║\n", book_count);
    printf("  ║  Total Copies        : %-4d                 ║\n", total);
    printf("  ║  Available Copies    : %-4d                 ║\n", available);
    printf("  ║  Issued Copies       : %-4d                 ║\n", issued);
    printf("  ║  Registered Members  : %-4d                 ║\n", member_count);
    printf("  ║  Members w/ Books    : %-4d                 ║\n", active_members);
    printf("  ╚═════════════════════════════════════════════╝\n");
}

/* ─── Main Menu ──────────────────────────────────────────────────────── */

int main(void) {
    int choice;

    printf("\n  ╔══════════════════════════════════════════╗");
    printf("\n  ║       MINI LIBRARY MANAGEMENT SYSTEM     ║");
    printf("\n  ╚══════════════════════════════════════════╝\n");

    do {
        printf("\n  ┌─ MAIN MENU ──────────────────────────────┐\n");
        printf("  │  ── Books ──                              │\n");
        printf("  │  1. Add Book                             │\n");
        printf("  │  2. Display All Books                    │\n");
        printf("  │  3. Search Book                         │\n");
        printf("  │  4. Delete Book                         │\n");
        printf("  │  ── Members ──                           │\n");
        printf("  │  5. Register Member                     │\n");
        printf("  │  6. Display All Members                 │\n");
        printf("  │  ── Transactions ──                      │\n");
        printf("  │  7. Issue Book                          │\n");
        printf("  │  8. Return Book                         │\n");
        printf("  │  ── Reports ──                           │\n");
        printf("  │  9. Library Summary                     │\n");
        printf("  │  0. Exit                                │\n");
        printf("  └──────────────────────────────────────────┘\n");
        printf("  Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook();          break;
            case 2: displayAllBooks();  break;
            case 3: searchBook();       break;
            case 4: deleteBook();       break;
            case 5: addMember();        break;
            case 6: displayAllMembers(); break;
            case 7: issueBook();        break;
            case 8: returnBook();       break;
            case 9: librarySummary();   break;
            case 0: printf("\n  Thank you! Goodbye.\n\n"); break;
            default: printf("  [!] Invalid option.\n");
        }

    } while (choice != 0);

    return 0;
}