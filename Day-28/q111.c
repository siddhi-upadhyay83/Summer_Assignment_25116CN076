//wap to create ticket booking system//
// Features: Add Event, Book Ticket, Cancel Ticket, View Bookings, View Events

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTS    20
#define MAX_BOOKINGS  200
#define MAX_NAME      80
#define MAX_VENUE     80

// ──────────────────────────────────────────
// Data Structures
// ──────────────────────────────────────────

typedef struct {
    int    eventId;
    char   name[MAX_NAME];
    char   venue[MAX_VENUE];
    char   date[20];        // DD-MM-YYYY
    char   time[10];        // HH:MM
    char   category[20];    // Movie / Concert / Sport / Drama
    int    totalSeats;
    int    availableSeats;
    double price;
} Event;

typedef struct {
    int    bookingId;
    int    eventId;
    char   passengerName[MAX_NAME];
    char   contact[15];
    int    seats;
    double totalAmount;
    char   bookingDate[20];
    int    status;          // 1 = Confirmed, 0 = Cancelled
} Booking;

Event   events[MAX_EVENTS];
Booking bookings[MAX_BOOKINGS];
int     totalEvents   = 0;
int     totalBookings = 0;

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
    printf("            🎟  TICKET BOOKING SYSTEM  🎟\n");
    printLine();
}

void getToday(char *buf) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buf, 20, "%d-%m-%Y", tm);
}

int findEvent(int id) {
    for (int i = 0; i < totalEvents; i++)
        if (events[i].eventId == id) return i;
    return -1;
}

int findBooking(int id) {
    for (int i = 0; i < totalBookings; i++)
        if (bookings[i].bookingId == id) return i;
    return -1;
}

// ──────────────────────────────────────────
// 1. Add Event  (Admin)
// ──────────────────────────────────────────

void addEvent() {
    if (totalEvents >= MAX_EVENTS) {
        printf("\n⚠  Event list is full.\n");
        return;
    }

    Event e;
    e.eventId = 1001 + totalEvents;

    printf("\n── Add New Event ──\n");
    printf("Event ID (auto) : %d\n", e.eventId);

    printf("Event Name      : ");
    fgets(e.name, MAX_NAME, stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("Venue           : ");
    fgets(e.venue, MAX_VENUE, stdin);
    e.venue[strcspn(e.venue, "\n")] = '\0';

    printf("Date (DD-MM-YYYY): ");
    scanf("%19s", e.date);
    clearInputBuffer();

    printf("Time (HH:MM)    : ");
    scanf("%9s", e.time);
    clearInputBuffer();

    printf("Category\n  1. Movie  2. Concert  3. Sport  4. Drama\n  Choice: ");
    int cat;
    scanf("%d", &cat);
    clearInputBuffer();
    switch (cat) {
        case 2:  strcpy(e.category, "Concert"); break;
        case 3:  strcpy(e.category, "Sport");   break;
        case 4:  strcpy(e.category, "Drama");   break;
        default: strcpy(e.category, "Movie");
    }

    printf("Total Seats     : ");
    scanf("%d", &e.totalSeats);
    clearInputBuffer();

    printf("Price per Seat  : ₹");
    scanf("%lf", &e.price);
    clearInputBuffer();

    e.availableSeats = e.totalSeats;
    events[totalEvents++] = e;

    printf("\n✔  Event \"%s\" added! (ID: %d)\n", e.name, e.eventId);
}

// ──────────────────────────────────────────
// 2. Display All Events
// ──────────────────────────────────────────

void displayEvents() {
    if (totalEvents == 0) {
        printf("\n⚠  No events available.\n");
        return;
    }

    printf("\n── Available Events ──\n");
    printf("%-6s  %-24s  %-18s  %-12s  %-8s  %-10s  %-6s  %8s\n",
           "ID", "Event", "Venue", "Date", "Time", "Category", "Seats", "Price(₹)");
    printLine();

    for (int i = 0; i < totalEvents; i++) {
        Event *e = &events[i];
        printf("%-6d  %-24s  %-18s  %-12s  %-8s  %-10s  %-6d  %8.2f\n",
               e->eventId, e->name, e->venue, e->date, e->time,
               e->category, e->availableSeats, e->price);
    }
    printLine();
}

// ──────────────────────────────────────────
// 3. Book Ticket
// ──────────────────────────────────────────

void bookTicket() {
    if (totalEvents == 0) {
        printf("\n⚠  No events available for booking.\n");
        return;
    }

    displayEvents();

    printf("\n── Book Ticket ──\n");
    printf("Enter Event ID   : ");
    int eventId;
    scanf("%d", &eventId);
    clearInputBuffer();

    int eIdx = findEvent(eventId);
    if (eIdx == -1) { printf("⚠  Event not found.\n"); return; }

    Event *e = &events[eIdx];
    if (e->availableSeats == 0) {
        printf("⚠  Sorry! No seats available for \"%s\".\n", e->name);
        return;
    }

    Booking b;
    b.bookingId = 5001 + totalBookings;
    b.eventId   = eventId;

    printf("Your Name        : ");
    fgets(b.passengerName, MAX_NAME, stdin);
    b.passengerName[strcspn(b.passengerName, "\n")] = '\0';

    printf("Contact Number   : ");
    scanf("%14s", b.contact);
    clearInputBuffer();

    printf("Number of Seats  : ");
    scanf("%d", &b.seats);
    clearInputBuffer();

    if (b.seats <= 0 || b.seats > e->availableSeats) {
        printf("⚠  Invalid seat count. Only %d seats available.\n", e->availableSeats);
        return;
    }

    b.totalAmount = b.seats * e->price;
    b.status      = 1;
    getToday(b.bookingDate);

    e->availableSeats -= b.seats;
    bookings[totalBookings++] = b;

    printf("\n");
    printLine();
    printf("         ✔  BOOKING CONFIRMED!\n");
    printLine();
    printf("  Booking ID   : %d\n",    b.bookingId);
    printf("  Event        : %s\n",    e->name);
    printf("  Venue        : %s\n",    e->venue);
    printf("  Date & Time  : %s at %s\n", e->date, e->time);
    printf("  Passenger    : %s\n",    b.passengerName);
    printf("  Contact      : %s\n",    b.contact);
    printf("  Seats        : %d\n",    b.seats);
    printf("  Total Amount : ₹%.2f\n", b.totalAmount);
    printf("  Booked On    : %s\n",    b.bookingDate);
    printLine();
}

// ──────────────────────────────────────────
// 4. Cancel Ticket
// ──────────────────────────────────────────

void cancelTicket() {
    printf("\n── Cancel Ticket ──\n");
    printf("Enter Booking ID: ");
    int bookingId;
    scanf("%d", &bookingId);
    clearInputBuffer();

    int bIdx = findBooking(bookingId);
    if (bIdx == -1) { printf("⚠  Booking not found.\n"); return; }

    Booking *b = &bookings[bIdx];
    if (b->status == 0) {
        printf("⚠  Booking %d is already cancelled.\n", bookingId);
        return;
    }

    int eIdx = findEvent(b->eventId);

    printf("\n  Booking ID : %d\n",      b->bookingId);
    printf("  Passenger  : %s\n",        b->passengerName);
    printf("  Seats      : %d\n",        b->seats);
    printf("  Amount Paid: ₹%.2f\n",     b->totalAmount);
    printf("\n  Confirm cancellation? (y/n): ");
    char ch;
    scanf("%c", &ch);
    clearInputBuffer();

    if (ch != 'y' && ch != 'Y') {
        printf("  Cancellation aborted.\n");
        return;
    }

    b->status = 0;
    if (eIdx != -1)
        events[eIdx].availableSeats += b->seats;   // release seats

    printf("✔  Booking %d cancelled. Refund of ₹%.2f will be processed.\n",
           bookingId, b->totalAmount);
}

// ──────────────────────────────────────────
// 5. View My Bookings (by name or contact)
// ──────────────────────────────────────────

void viewMyBookings() {
    printf("\n── View Bookings ──\n");
    printf("Enter your Contact Number: ");
    char contact[15];
    scanf("%14s", contact);
    clearInputBuffer();

    int found = 0;
    printf("\n%-10s  %-6s  %-20s  %-12s  %-5s  %10s  %-10s\n",
           "BookingID", "EvtID", "Event", "Date", "Seats", "Amount(₹)", "Status");
    printLine();

    for (int i = 0; i < totalBookings; i++) {
        Booking *b = &bookings[i];
        if (strcmp(b->contact, contact) == 0) {
            int eIdx = findEvent(b->eventId);
            char evName[24] = "N/A";
            char evDate[13] = "N/A";
            if (eIdx != -1) {
                strncpy(evName, events[eIdx].name, 23);
                strncpy(evDate, events[eIdx].date, 12);
            }
            printf("%-10d  %-6d  %-20s  %-12s  %-5d  %10.2f  %-10s\n",
                   b->bookingId, b->eventId, evName, evDate,
                   b->seats, b->totalAmount,
                   b->status ? "Confirmed" : "Cancelled");
            found++;
        }
    }

    if (!found)
        printf("⚠  No bookings found for contact %s.\n", contact);
    else
        printLine();
}

// ──────────────────────────────────────────
// 6. View All Bookings  (Admin)
// ──────────────────────────────────────────

void viewAllBookings() {
    if (totalBookings == 0) {
        printf("\n⚠  No bookings yet.\n");
        return;
    }

    printf("\n── All Bookings ──\n");
    printf("%-10s  %-6s  %-20s  %-16s  %-12s  %-5s  %10s  %-10s\n",
           "BookingID", "EvtID", "Event", "Passenger", "Contact",
           "Seats", "Amount(₹)", "Status");
    printLine();

    double totalRevenue = 0;
    for (int i = 0; i < totalBookings; i++) {
        Booking *b = &bookings[i];
        int eIdx = findEvent(b->eventId);
        char evName[21] = "N/A";
        if (eIdx != -1) strncpy(evName, events[eIdx].name, 20);

        printf("%-10d  %-6d  %-20s  %-16s  %-12s  %-5d  %10.2f  %-10s\n",
               b->bookingId, b->eventId, evName,
               b->passengerName, b->contact, b->seats,
               b->totalAmount, b->status ? "Confirmed" : "Cancelled");

        if (b->status) totalRevenue += b->totalAmount;
    }

    printLine();
    printf("  Total Revenue (Confirmed): ₹%.2f\n", totalRevenue);
}

// ──────────────────────────────────────────
// 7. Event Summary
// ──────────────────────────────────────────

void eventSummary() {
    if (totalEvents == 0) { printf("\n⚠  No events.\n"); return; }

    printf("\n── Event Summary ──\n");
    printf("%-6s  %-24s  %-6s  %-9s  %-9s  %12s\n",
           "ID", "Event", "Total", "Booked", "Available", "Revenue(₹)");
    printLine();

    for (int i = 0; i < totalEvents; i++) {
        Event *e = &events[i];
        int booked = e->totalSeats - e->availableSeats;
        double revenue = booked * e->price;
        printf("%-6d  %-24s  %-6d  %-9d  %-9d  %12.2f\n",
               e->eventId, e->name, e->totalSeats,
               booked, e->availableSeats, revenue);
    }
    printLine();
}

// ──────────────────────────────────────────
// Main Menu
// ──────────────────────────────────────────

int main() {
    int choice;

    // Preload two sample events for convenience
    strcpy(events[0].name,     "Arijit Singh Live");
    strcpy(events[0].venue,    "Patna Convention Hall");
    strcpy(events[0].date,     "15-07-2026");
    strcpy(events[0].time,     "19:00");
    strcpy(events[0].category, "Concert");
    events[0].eventId       = 1001;
    events[0].totalSeats    = 200;
    events[0].availableSeats= 200;
    events[0].price         = 1500.00;
    totalEvents++;

    strcpy(events[1].name,     "Bihar Premier League");
    strcpy(events[1].venue,    "Moin-ul-Haq Stadium");
    strcpy(events[1].date,     "20-07-2026");
    strcpy(events[1].time,     "15:30");
    strcpy(events[1].category, "Sport");
    events[1].eventId       = 1002;
    events[1].totalSeats    = 500;
    events[1].availableSeats= 500;
    events[1].price         = 300.00;
    totalEvents++;

    do {
        printHeader();
        printf("  1. View Events\n");
        printf("  2. Book Ticket\n");
        printf("  3. Cancel Ticket\n");
        printf("  4. My Bookings\n");
        printf("  5. All Bookings  [Admin]\n");
        printf("  6. Add Event     [Admin]\n");
        printf("  7. Event Summary [Admin]\n");
        printf("  0. Exit\n");
        printLine();
        printf("  Enter your choice: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1: displayEvents();    break;
            case 2: bookTicket();       break;
            case 3: cancelTicket();     break;
            case 4: viewMyBookings();   break;
            case 5: viewAllBookings();  break;
            case 6: addEvent();         break;
            case 7: eventSummary();     break;
            case 0: printf("\n  Thank you! See you at the event! 🎉\n\n"); break;
            default: printf("\n⚠  Invalid option. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}