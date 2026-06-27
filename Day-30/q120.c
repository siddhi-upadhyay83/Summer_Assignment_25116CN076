//wap to develop complete mini project using arrays ,strings,and functions//
/*
 ******************************************************************************
 *                    GRAND VISTA HOTEL MANAGEMENT SYSTEM                     *
 *          A Complete Mini Project using Arrays, Strings & Functions         *
 ******************************************************************************
 *  Modules:                                                                  *
 *   1. Room Management    – Add / view / update room details                 *
 *   2. Guest Management   – Check-in / Check-out / View guests               *
 *   3. Food & Services    – Order food items billed to room                  *
 *   4. Billing            – Auto-generate itemised bill on checkout          *
 *   5. Reports            – Occupancy, revenue, room status                  *
 ******************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ══════════════════════════════════════════════════════════════════════════
   CONSTANTS
   ══════════════════════════════════════════════════════════════════════════ */
#define MAX_ROOMS     20
#define MAX_GUESTS    20
#define MAX_ORDERS    50
#define MAX_MENU      10
#define STR_SM        20
#define STR_MD        40
#define STR_LG        60

/* ══════════════════════════════════════════════════════════════════════════
   DATA STRUCTURES
   ══════════════════════════════════════════════════════════════════════════ */

/* Room types */
#define SINGLE   1
#define DOUBLE   2
#define SUITE    3

/* Room status */
#define VACANT    0
#define OCCUPIED  1

struct Room {
    int   room_no;
    int   type;           /* SINGLE / DOUBLE / SUITE */
    float rate_per_night; /* base tariff             */
    int   status;         /* VACANT / OCCUPIED       */
    int   floor;
    char  amenities[STR_LG]; /* e.g. "AC, TV, WiFi"  */
};

struct FoodOrder {
    int   room_no;
    char  item_name[STR_MD];
    int   quantity;
    float unit_price;
    float total_price;
};

struct Guest {
    int   guest_id;
    char  name[STR_MD];
    char  phone[STR_SM];
    char  id_proof[STR_MD];  /* Aadhar / Passport no */
    int   room_no;
    int   check_in_day;      /* simplified: day number */
    int   nights;
    float room_charges;
    float food_charges;
    float total_bill;
    int   is_checked_out;    /* 0 = active, 1 = checked out */
};

struct MenuItem {
    char  name[STR_MD];
    float price;
};

/* ══════════════════════════════════════════════════════════════════════════
   GLOBAL STORAGE
   ══════════════════════════════════════════════════════════════════════════ */

struct Room      rooms[MAX_ROOMS];
struct Guest     guests[MAX_GUESTS];
struct FoodOrder orders[MAX_ORDERS];
struct MenuItem  menu[MAX_MENU];

int room_count   = 0;
int guest_count  = 0;
int order_count  = 0;
int menu_count   = 0;
int next_guest_id = 1001;

/* ══════════════════════════════════════════════════════════════════════════
   UTILITY FUNCTIONS
   ══════════════════════════════════════════════════════════════════════════ */

void printLine(void) {
    printf("  ────────────────────────────────────────────────────────────────────\n");
}

void printDoubleLine(void) {
    printf("  ════════════════════════════════════════════════════════════════════\n");
}

void printHeader(const char *title) {
    printDoubleLine();
    printf("  ║  %-64s║\n", title);
    printDoubleLine();
}

/* Room type to string */
const char *roomTypeStr(int type) {
    if (type == SINGLE) return "Single";
    if (type == DOUBLE) return "Double";
    if (type == SUITE)  return "Suite ";
    return "Unknown";
}

/* Find room index by room number, returns -1 if not found */
int findRoom(int room_no) {
    for (int i = 0; i < room_count; i++)
        if (rooms[i].room_no == room_no) return i;
    return -1;
}

/* Find active guest by room number */
int findGuestByRoom(int room_no) {
    for (int i = 0; i < guest_count; i++)
        if (guests[i].room_no == room_no && !guests[i].is_checked_out)
            return i;
    return -1;
}

/* Find active guest by guest ID */
int findGuestById(int id) {
    for (int i = 0; i < guest_count; i++)
        if (guests[i].guest_id == id) return i;
    return -1;
}

/* Calculate total food charges for a room */
float calcFoodCharges(int room_no) {
    float total = 0;
    for (int i = 0; i < order_count; i++)
        if (orders[i].room_no == room_no)
            total += orders[i].total_price;
    return total;
}

/* ══════════════════════════════════════════════════════════════════════════
   MODULE 1 — ROOM MANAGEMENT
   ══════════════════════════════════════════════════════════════════════════ */

void initDefaultRooms(void) {
    /* Pre-load 10 rooms so the demo works immediately */
    int room_nos[]   = {101, 102, 201, 202, 203, 301, 302, 401, 402, 501};
    int types[]      = {SINGLE, SINGLE, DOUBLE, DOUBLE, DOUBLE, SUITE, SUITE, SINGLE, DOUBLE, SUITE};
    float rates[]    = {1500, 1500, 2500, 2500, 2500, 5000, 5000, 1500, 2500, 7000};
    int floors[]     = {1, 1, 2, 2, 2, 3, 3, 4, 4, 5};
    const char *am[] = {
        "AC, TV", "AC, TV", "AC, TV, Mini-Bar", "AC, TV, Mini-Bar", "AC, TV, Mini-Bar",
        "AC, TV, Jacuzzi, Mini-Bar", "AC, TV, Jacuzzi, Mini-Bar",
        "AC, TV", "AC, TV, Mini-Bar", "AC, TV, Jacuzzi, Pool Access, Mini-Bar"
    };

    for (int i = 0; i < 10; i++) {
        rooms[i].room_no        = room_nos[i];
        rooms[i].type           = types[i];
        rooms[i].rate_per_night = rates[i];
        rooms[i].status         = VACANT;
        rooms[i].floor          = floors[i];
        strcpy(rooms[i].amenities, am[i]);
    }
    room_count = 10;

    /* Pre-load menu */
    const char *items[] = {"Masala Chai", "Veg Thali", "Non-Veg Thali",
                           "Club Sandwich", "Cold Coffee", "Paneer Butter Masala",
                           "Biryani", "Fresh Juice", "Ice Cream", "Mineral Water"};
    float prices[] = {40, 180, 250, 120, 100, 220, 280, 80, 90, 30};

    for (int i = 0; i < 10; i++) {
        strcpy(menu[i].name, items[i]);
        menu[i].price = prices[i];
    }
    menu_count = 10;
}

void addRoom(void) {
    if (room_count >= MAX_ROOMS) {
        printf("\n  [!] Room capacity full.\n");
        return;
    }

    struct Room r;
    printf("\n  Enter Room Number   : "); scanf("%d", &r.room_no);
    if (findRoom(r.room_no) != -1) {
        printf("  [!] Room %d already exists.\n", r.room_no); return;
    }

    printf("  Floor               : "); scanf("%d", &r.floor);
    printf("  Type (1=Single 2=Double 3=Suite): "); scanf("%d", &r.type);

    switch (r.type) {
        case SINGLE: r.rate_per_night = 1500; break;
        case DOUBLE: r.rate_per_night = 2500; break;
        case SUITE:  r.rate_per_night = 5000; break;
        default:     r.rate_per_night = 1500;
    }

    printf("  Custom Rate/Night (0 = use default %.0f): ", r.rate_per_night);
    float custom; scanf("%f", &custom);
    if (custom > 0) r.rate_per_night = custom;

    printf("  Amenities           : "); scanf(" %[^\n]", r.amenities);
    r.status = VACANT;

    rooms[room_count++] = r;
    printf("  [✓] Room %d added. Rate: INR %.0f/night\n", r.room_no, r.rate_per_night);
}

void displayRooms(void) {
    printHeader("ROOM STATUS BOARD");
    printf("  %-6s %-7s %-8s %-10s %-5s %-10s %-28s\n",
           "Room", "Floor", "Type", "Rate/Ngt", "Floor", "Status", "Amenities");
    printLine();

    int vacant = 0, occupied = 0;
    for (int i = 0; i < room_count; i++) {
        struct Room *r = &rooms[i];
        const char *status = r->status == VACANT ? "[ VACANT ]" : "[OCCUPIED]";
        printf("  %-6d %-7d %-8s INR%-7.0f %-5d %s  %s\n",
               r->room_no, r->floor, roomTypeStr(r->type),
               r->rate_per_night, r->floor, status, r->amenities);
        if (r->status == VACANT) vacant++; else occupied++;
    }
    printLine();
    printf("  Total: %d rooms  |  Vacant: %d  |  Occupied: %d\n",
           room_count, vacant, occupied);
}

void displayVacantRooms(void) {
    printHeader("AVAILABLE ROOMS");
    printf("  %-6s %-8s %-12s %-5s %-30s\n",
           "Room", "Type", "Rate/Night", "Floor", "Amenities");
    printLine();
    int found = 0;
    for (int i = 0; i < room_count; i++) {
        if (rooms[i].status == VACANT) {
            printf("  %-6d %-8s INR %-8.0f %-5d %s\n",
                   rooms[i].room_no, roomTypeStr(rooms[i].type),
                   rooms[i].rate_per_night, rooms[i].floor,
                   rooms[i].amenities);
            found++;
        }
    }
    if (!found) printf("  No vacant rooms available.\n");
    printLine();
}

/* ══════════════════════════════════════════════════════════════════════════
   MODULE 2 — GUEST MANAGEMENT (CHECK-IN / CHECK-OUT)
   ══════════════════════════════════════════════════════════════════════════ */

void checkIn(void) {
    if (guest_count >= MAX_GUESTS) {
        printf("\n  [!] Guest list full.\n"); return;
    }

    displayVacantRooms();

    struct Guest g;
    printf("\n  Enter Room Number   : ");
    scanf("%d", &g.room_no);

    int ri = findRoom(g.room_no);
    if (ri == -1) { printf("  [!] Room not found.\n"); return; }
    if (rooms[ri].status == OCCUPIED) {
        printf("  [!] Room %d is already occupied.\n", g.room_no); return;
    }

    g.guest_id = next_guest_id++;
    printf("  Guest Name          : "); scanf(" %[^\n]", g.name);
    printf("  Phone Number        : "); scanf(" %[^\n]", g.phone);
    printf("  ID Proof No (Aadhar/Passport): "); scanf(" %[^\n]", g.id_proof);
    printf("  Number of Nights    : "); scanf("%d", &g.nights);

    g.check_in_day     = 1;   /* simplified day counter */
    g.room_charges     = rooms[ri].rate_per_night * g.nights;
    g.food_charges     = 0;
    g.total_bill       = 0;
    g.is_checked_out   = 0;

    rooms[ri].status = OCCUPIED;
    guests[guest_count++] = g;

    printf("\n  ╔══════════════════════════════════════════╗\n");
    printf("  ║          CHECK-IN SUCCESSFUL             ║\n");
    printf("  ╠══════════════════════════════════════════╣\n");
    printf("  ║  Guest ID   : %-27d║\n", g.guest_id);
    printf("  ║  Name       : %-27s║\n", g.name);
    printf("  ║  Room       : %-27d║\n", g.room_no);
    printf("  ║  Type       : %-27s║\n", roomTypeStr(rooms[ri].type));
    printf("  ║  Nights     : %-27d║\n", g.nights);
    printf("  ║  Room Rate  : INR %-23.2f║\n", rooms[ri].rate_per_night);
    printf("  ║  Room Total : INR %-23.2f║\n", g.room_charges);
    printf("  ╚══════════════════════════════════════════╝\n");
}

void viewActiveGuests(void) {
    printHeader("ACTIVE GUESTS");
    printf("  %-6s %-20s %-12s %-6s %-7s %12s\n",
           "ID", "Name", "Phone", "Room", "Nights", "Room Charges");
    printLine();
    int found = 0;
    for (int i = 0; i < guest_count; i++) {
        if (!guests[i].is_checked_out) {
            printf("  %-6d %-20s %-12s %-6d %-7d INR %8.2f\n",
                   guests[i].guest_id, guests[i].name,
                   guests[i].phone, guests[i].room_no,
                   guests[i].nights, guests[i].room_charges);
            found++;
        }
    }
    if (!found) printf("  No active guests.\n");
    printLine();
}

void generateBill(int gi) {
    struct Guest *g = &guests[gi];
    int ri = findRoom(g->room_no);

    g->food_charges = calcFoodCharges(g->room_no);
    float service_tax = 0.05f * (g->room_charges + g->food_charges);
    g->total_bill  = g->room_charges + g->food_charges + service_tax;

    printDoubleLine();
    printf("  ║%34s║\n", "");
    printf("  ║     *** GRAND VISTA HOTEL ***          ║\n");
    printf("  ║       Final Bill / Invoice             ║\n");
    printf("  ║%34s║\n", "");
    printDoubleLine();
    printf("  Guest ID      : %d\n",       g->guest_id);
    printf("  Name          : %s\n",       g->name);
    printf("  Phone         : %s\n",       g->phone);
    printf("  ID Proof      : %s\n",       g->id_proof);
    printf("  Room No       : %d  (%s)\n", g->room_no,
           ri != -1 ? roomTypeStr(rooms[ri].type) : "—");
    printf("  Nights Stayed : %d\n",       g->nights);
    printLine();

    /* Room charges */
    if (ri != -1)
        printf("  Room Charges  : %d nights x INR %.2f = INR %.2f\n",
               g->nights, rooms[ri].rate_per_night, g->room_charges);

    /* Food orders */
    printf("\n  Food & Service Orders:\n");
    int food_found = 0;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].room_no == g->room_no) {
            printf("    %-25s x%d  @ INR %.2f  =  INR %.2f\n",
                   orders[i].item_name, orders[i].quantity,
                   orders[i].unit_price, orders[i].total_price);
            food_found++;
        }
    }
    if (!food_found) printf("    (No food orders)\n");

    printLine();
    printf("  Room Charges  :           INR %10.2f\n", g->room_charges);
    printf("  Food Charges  :           INR %10.2f\n", g->food_charges);
    printf("  Service Tax 5%%:           INR %10.2f\n", service_tax);
    printLine();
    printf("  TOTAL AMOUNT  :           INR %10.2f\n", g->total_bill);
    printDoubleLine();
    printf("  Thank you for staying at Grand Vista Hotel!\n");
    printf("  We hope to see you again.\n");
    printDoubleLine();
}

void checkOut(void) {
    int id;
    printf("\n  Enter Guest ID : ");
    scanf("%d", &id);
    int gi = findGuestById(id);
    if (gi == -1 || guests[gi].is_checked_out) {
        printf("  [!] Active guest not found.\n"); return;
    }

    generateBill(gi);

    int ri = findRoom(guests[gi].room_no);
    if (ri != -1) rooms[ri].status = VACANT;

    guests[gi].is_checked_out = 1;
    printf("\n  [✓] Guest checked out. Room %d is now vacant.\n", guests[gi].room_no);
}

/* ══════════════════════════════════════════════════════════════════════════
   MODULE 3 — FOOD & SERVICES
   ══════════════════════════════════════════════════════════════════════════ */

void showMenu(void) {
    printHeader("RESTAURANT MENU");
    printf("  %-4s %-28s %10s\n", "No.", "Item", "Price");
    printLine();
    for (int i = 0; i < menu_count; i++)
        printf("  %-4d %-28s INR %6.2f\n",
               i + 1, menu[i].name, menu[i].price);
    printLine();
}

void orderFood(void) {
    if (order_count >= MAX_ORDERS) {
        printf("\n  [!] Order log full.\n"); return;
    }

    int room_no;
    printf("\n  Enter Room Number : ");
    scanf("%d", &room_no);

    if (findRoom(room_no) == -1) {
        printf("  [!] Room not found.\n"); return;
    }
    if (findGuestByRoom(room_no) == -1) {
        printf("  [!] No active guest in room %d.\n", room_no); return;
    }

    showMenu();

    int choice, qty;
    printf("  Select Item (1-%d) : ", menu_count);
    scanf("%d", &choice);
    if (choice < 1 || choice > menu_count) {
        printf("  [!] Invalid selection.\n"); return;
    }

    printf("  Quantity          : ");
    scanf("%d", &qty);
    if (qty <= 0) { printf("  [!] Invalid quantity.\n"); return; }

    struct FoodOrder fo;
    fo.room_no    = room_no;
    strcpy(fo.item_name, menu[choice - 1].name);
    fo.quantity   = qty;
    fo.unit_price = menu[choice - 1].price;
    fo.total_price = fo.unit_price * qty;

    orders[order_count++] = fo;

    printf("  [✓] Order placed: %dx %s = INR %.2f (billed to Room %d)\n",
           qty, fo.item_name, fo.total_price, room_no);
}

void viewRoomOrders(void) {
    int room_no;
    printf("\n  Enter Room Number : ");
    scanf("%d", &room_no);

    printf("\n  Orders for Room %d:\n", room_no);
    printLine();
    printf("  %-25s %6s %10s %12s\n",
           "Item", "Qty", "Unit Price", "Total");
    printLine();

    float grand = 0;
    int found = 0;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].room_no == room_no) {
            printf("  %-25s %6d INR %7.2f  INR %8.2f\n",
                   orders[i].item_name, orders[i].quantity,
                   orders[i].unit_price, orders[i].total_price);
            grand += orders[i].total_price;
            found++;
        }
    }

    if (!found) printf("  No orders for this room.\n");
    else {
        printLine();
        printf("  Total Food Bill   : INR %.2f\n", grand);
    }
}

/* ══════════════════════════════════════════════════════════════════════════
   MODULE 5 — REPORTS
   ══════════════════════════════════════════════════════════════════════════ */

void occupancyReport(void) {
    int single_t = 0, single_o = 0;
    int double_t = 0, double_o = 0;
    int suite_t  = 0, suite_o  = 0;

    for (int i = 0; i < room_count; i++) {
        switch (rooms[i].type) {
            case SINGLE:
                single_t++;
                if (rooms[i].status == OCCUPIED) single_o++;
                break;
            case DOUBLE:
                double_t++;
                if (rooms[i].status == OCCUPIED) double_o++;
                break;
            case SUITE:
                suite_t++;
                if (rooms[i].status == OCCUPIED) suite_o++;
                break;
        }
    }

    int total_occupied = single_o + double_o + suite_o;
    float occ_rate = room_count ? (total_occupied * 100.0f / room_count) : 0;

    printHeader("OCCUPANCY REPORT");
    printf("  %-12s %8s %10s %8s\n", "Type", "Total", "Occupied", "Vacant");
    printLine();
    printf("  %-12s %8d %10d %8d\n", "Single", single_t, single_o, single_t - single_o);
    printf("  %-12s %8d %10d %8d\n", "Double", double_t, double_o, double_t - double_o);
    printf("  %-12s %8d %10d %8d\n", "Suite",  suite_t,  suite_o,  suite_t  - suite_o);
    printLine();
    printf("  %-12s %8d %10d %8d\n", "TOTAL", room_count, total_occupied, room_count - total_occupied);
    printf("  Occupancy Rate : %.1f%%\n", occ_rate);
}

void revenueReport(void) {
    float room_rev = 0, food_rev = 0;

    /* Revenue from checked-out guests only */
    for (int i = 0; i < guest_count; i++) {
        if (guests[i].is_checked_out) {
            room_rev += guests[i].room_charges;
            food_rev += guests[i].food_charges;
        }
    }

    /* Pending revenue from active guests */
    float pending_room = 0, pending_food = 0;
    for (int i = 0; i < guest_count; i++) {
        if (!guests[i].is_checked_out) {
            pending_room += guests[i].room_charges;
            pending_food += calcFoodCharges(guests[i].room_no);
        }
    }

    float total_collected = room_rev + food_rev;

    printHeader("REVENUE REPORT");
    printf("  ── Collected (Checked-out Guests) ──\n");
    printf("  Room Revenue       : INR %10.2f\n", room_rev);
    printf("  Food Revenue       : INR %10.2f\n", food_rev);
    printf("  Service Tax (5%%)  : INR %10.2f\n", 0.05f * total_collected);
    printLine();
    printf("  Total Collected    : INR %10.2f\n",
           total_collected + 0.05f * total_collected);
    printf("\n  ── Pending (Active Guests) ──\n");
    printf("  Pending Rooms      : INR %10.2f\n", pending_room);
    printf("  Pending Food       : INR %10.2f\n", pending_food);
    printLine();
    printf("  Total Pending      : INR %10.2f\n", pending_room + pending_food);
}

void guestHistoryReport(void) {
    printHeader("GUEST HISTORY");
    printf("  %-6s %-20s %-6s %-7s %12s %12s %12s %8s\n",
           "ID", "Name", "Room", "Nights",
           "Room Chg", "Food Chg", "Total Bill", "Status");
    printLine();
    for (int i = 0; i < guest_count; i++) {
        struct Guest *g = &guests[i];
        float fc = g->is_checked_out ? g->food_charges : calcFoodCharges(g->room_no);
        float tb = g->is_checked_out ? g->total_bill
                                     : (g->room_charges + fc + 0.05f * (g->room_charges + fc));
        printf("  %-6d %-20s %-6d %-7d %12.2f %12.2f %12.2f %8s\n",
               g->guest_id, g->name, g->room_no, g->nights,
               g->room_charges, fc, tb,
               g->is_checked_out ? "Out" : "Active");
    }
    if (!guest_count) printf("  No guest records yet.\n");
    printLine();
}

/* ══════════════════════════════════════════════════════════════════════════
   MENUS & MAIN
   ══════════════════════════════════════════════════════════════════════════ */

void roomMenu(void) {
    int ch;
    do {
        printf("\n  ┌─ ROOM MANAGEMENT ──────────────────┐\n");
        printf("  │  1. Add New Room                   │\n");
        printf("  │  2. View All Rooms (Status Board)  │\n");
        printf("  │  3. View Vacant Rooms Only         │\n");
        printf("  │  0. Back                           │\n");
        printf("  └────────────────────────────────────┘\n");
        printf("  Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: addRoom();           break;
            case 2: displayRooms();      break;
            case 3: displayVacantRooms(); break;
            case 0: break;
            default: printf("  [!] Invalid.\n");
        }
    } while (ch != 0);
}

void guestMenu(void) {
    int ch;
    do {
        printf("\n  ┌─ GUEST MANAGEMENT ─────────────────┐\n");
        printf("  │  1. Check-In Guest                 │\n");
        printf("  │  2. Check-Out Guest (+ Bill)       │\n");
        printf("  │  3. View Active Guests             │\n");
        printf("  │  4. View Guest History             │\n");
        printf("  │  0. Back                           │\n");
        printf("  └────────────────────────────────────┘\n");
        printf("  Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: checkIn();             break;
            case 2: checkOut();            break;
            case 3: viewActiveGuests();    break;
            case 4: guestHistoryReport();  break;
            case 0: break;
            default: printf("  [!] Invalid.\n");
        }
    } while (ch != 0);
}

void foodMenu(void) {
    int ch;
    do {
        printf("\n  ┌─ FOOD & SERVICES ──────────────────┐\n");
        printf("  │  1. Place Food Order               │\n");
        printf("  │  2. View Room's Orders             │\n");
        printf("  │  3. View Full Menu                 │\n");
        printf("  │  0. Back                           │\n");
        printf("  └────────────────────────────────────┘\n");
        printf("  Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: orderFood();      break;
            case 2: viewRoomOrders(); break;
            case 3: showMenu();       break;
            case 0: break;
            default: printf("  [!] Invalid.\n");
        }
    } while (ch != 0);
}

void reportsMenu(void) {
    int ch;
    do {
        printf("\n  ┌─ REPORTS ──────────────────────────┐\n");
        printf("  │  1. Occupancy Report               │\n");
        printf("  │  2. Revenue Report                 │\n");
        printf("  │  3. Guest History                  │\n");
        printf("  │  0. Back                           │\n");
        printf("  └────────────────────────────────────┘\n");
        printf("  Choice: "); scanf("%d", &ch);
        switch (ch) {
            case 1: occupancyReport();     break;
            case 2: revenueReport();       break;
            case 3: guestHistoryReport();  break;
            case 0: break;
            default: printf("  [!] Invalid.\n");
        }
    } while (ch != 0);
}

int main(void) {
    initDefaultRooms();

    printf("\n");
    printDoubleLine();
    printf("  ║                                                                  ║\n");
    printf("  ║          ★  GRAND VISTA HOTEL MANAGEMENT SYSTEM  ★              ║\n");
    printf("  ║          A Complete Mini Project in C                            ║\n");
    printf("  ║          Arrays · Strings · Functions · Structs                  ║\n");
    printf("  ║                                                                  ║\n");
    printDoubleLine();
    printf("  10 rooms and full restaurant menu pre-loaded. Ready to use!\n");

    int choice;
    do {
        printf("\n  ╔══════════════════════════════════════════╗\n");
        printf("  ║              MAIN MENU                   ║\n");
        printf("  ╠══════════════════════════════════════════╣\n");
        printf("  ║  1.  Room Management                     ║\n");
        printf("  ║  2.  Guest Management (Check-In/Out)     ║\n");
        printf("  ║  3.  Food & Room Services                ║\n");
        printf("  ║  4.  Reports & Analytics                 ║\n");
        printf("  ║  0.  Exit                                ║\n");
        printf("  ╚══════════════════════════════════════════╝\n");
        printf("  Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: roomMenu();    break;
            case 2: guestMenu();   break;
            case 3: foodMenu();    break;
            case 4: reportsMenu(); break;
            case 0:
                printf("\n  Thank you for using Grand Vista HMS. Goodbye!\n\n");
                break;
            default:
                printf("  [!] Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}