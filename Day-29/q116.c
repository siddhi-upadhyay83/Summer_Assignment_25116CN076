//wap to create inventory managment system//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// ─── Data Structure ───────────────────────────────────────────────────────────
typedef struct {
    int    id;
    char   name[50];
    char   category[30];
    int    quantity;
    float  price;
} Product;

// ─── Global Data ──────────────────────────────────────────────────────────────
Product inventory[MAX];
int     totalProducts = 0;
int     nextId        = 1;

// ─── Function Prototypes ──────────────────────────────────────────────────────
void displayMenu();
void addProduct();
void displayAll();
void searchProduct();
void updateProduct();
void deleteProduct();
void displayLowStock();
void sortByPrice();
void sortByName();
void totalInventoryValue();
void displayByCategory();
void displaySummary();

// ─── Helper ───────────────────────────────────────────────────────────────────
int findById(int id) {
    for (int i = 0; i < totalProducts; i++)
        if (inventory[i].id == id) return i;
    return -1;
}

// ═════════════════════════════════════════════════════════════════════════════
int main() {
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:  addProduct();           break;
            case 2:  displayAll();           break;
            case 3:  searchProduct();        break;
            case 4:  updateProduct();        break;
            case 5:  deleteProduct();        break;
            case 6:  displayLowStock();      break;
            case 7:  sortByPrice();          break;
            case 8:  sortByName();           break;
            case 9:  totalInventoryValue();  break;
            case 10: displayByCategory();    break;
            case 11: displaySummary();       break;
            case 0:  printf("\nExiting Inventory System. Goodbye!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }
    } while (choice != 0);

    return 0;
}

// ─── Menu ─────────────────────────────────────────────────────────────────────
void displayMenu() {
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║     INVENTORY MANAGEMENT SYSTEM      ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  1.  Add Product                     ║\n");
    printf("║  2.  Display All Products            ║\n");
    printf("║  3.  Search Product                  ║\n");
    printf("║  4.  Update Product                  ║\n");
    printf("║  5.  Delete Product                  ║\n");
    printf("║  6.  Low Stock Alert  (qty < 5)      ║\n");
    printf("║  7.  Sort by Price                   ║\n");
    printf("║  8.  Sort by Name                    ║\n");
    printf("║  9.  Total Inventory Value           ║\n");
    printf("║  10. Filter by Category              ║\n");
    printf("║  11. Inventory Summary               ║\n");
    printf("║  0.  Exit                            ║\n");
    printf("╚══════════════════════════════════════╝\n");
}

// ─── Print Table Header ───────────────────────────────────────────────────────
void printHeader() {
    printf("\n%-5s %-20s %-15s %-8s %-10s\n",
           "ID", "Name", "Category", "Qty", "Price(Rs)");
    printf("%-5s %-20s %-15s %-8s %-10s\n",
           "----", "--------------------", "---------------", "--------", "----------");
}

void printProduct(Product p) {
    printf("%-5d %-20s %-15s %-8d %-10.2f\n",
           p.id, p.name, p.category, p.quantity, p.price);
}

// ─── 1. Add Product ───────────────────────────────────────────────────────────
void addProduct() {
    if (totalProducts >= MAX) {
        printf("\nInventory full! Cannot add more products.\n");
        return;
    }
    Product p;
    p.id = nextId++;

    printf("\n--- Add New Product ---\n");
    printf("Name     : "); fgets(p.name, 50, stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Category : "); fgets(p.category, 30, stdin);
    p.category[strcspn(p.category, "\n")] = '\0';

    printf("Quantity : "); scanf("%d",  &p.quantity); getchar();
    printf("Price    : "); scanf("%f",  &p.price);    getchar();

    if (p.quantity < 0 || p.price < 0) {
        printf("Error: Quantity and Price cannot be negative!\n");
        nextId--;
        return;
    }

    inventory[totalProducts++] = p;
    printf("Product added successfully! ID: %d\n", p.id);
}

// ─── 2. Display All ───────────────────────────────────────────────────────────
void displayAll() {
    if (totalProducts == 0) { printf("\nNo products in inventory!\n"); return; }
    printf("\n========== ALL PRODUCTS ==========");
    printHeader();
    for (int i = 0; i < totalProducts; i++)
        printProduct(inventory[i]);
    printf("\nTotal products: %d\n", totalProducts);
}

// ─── 3. Search Product ────────────────────────────────────────────────────────
void searchProduct() {
    if (totalProducts == 0) { printf("\nInventory is empty!\n"); return; }
    int searchChoice;
    printf("\nSearch by:\n  1. ID\n  2. Name\nChoice: ");
    scanf("%d", &searchChoice); getchar();

    if (searchChoice == 1) {
        int id;
        printf("Enter Product ID: "); scanf("%d", &id); getchar();
        int idx = findById(id);
        if (idx == -1) { printf("Product with ID %d not found!\n", id); return; }
        printHeader();
        printProduct(inventory[idx]);

    } else if (searchChoice == 2) {
        char keyword[50];
        printf("Enter product name (or part of it): ");
        fgets(keyword, 50, stdin);
        keyword[strcspn(keyword, "\n")] = '\0';

        int found = 0;
        printHeader();
        for (int i = 0; i < totalProducts; i++) {
            if (strstr(inventory[i].name, keyword) != NULL) {
                printProduct(inventory[i]);
                found++;
            }
        }
        if (!found) printf("No product matching \"%s\" found!\n", keyword);
        else printf("\n%d result(s) found.\n", found);
    } else {
        printf("Invalid search option!\n");
    }
}

// ─── 4. Update Product ────────────────────────────────────────────────────────
void updateProduct() {
    if (totalProducts == 0) { printf("\nInventory is empty!\n"); return; }
    int id;
    printf("\nEnter Product ID to update: "); scanf("%d", &id); getchar();
    int idx = findById(id);
    if (idx == -1) { printf("Product ID %d not found!\n", id); return; }

    printf("\nCurrent details:\n");
    printHeader(); printProduct(inventory[idx]);

    int field;
    printf("\nWhat to update?\n");
    printf("  1. Name\n  2. Category\n  3. Quantity\n");
    printf("  4. Price\n  5. All fields\nChoice: ");
    scanf("%d", &field); getchar();

    switch (field) {
        case 1:
            printf("New Name     : ");
            fgets(inventory[idx].name, 50, stdin);
            inventory[idx].name[strcspn(inventory[idx].name, "\n")] = '\0';
            break;
        case 2:
            printf("New Category : ");
            fgets(inventory[idx].category, 30, stdin);
            inventory[idx].category[strcspn(inventory[idx].category, "\n")] = '\0';
            break;
        case 3:
            printf("New Quantity : ");
            scanf("%d", &inventory[idx].quantity); getchar();
            break;
        case 4:
            printf("New Price    : ");
            scanf("%f", &inventory[idx].price); getchar();
            break;
        case 5:
            printf("New Name     : "); fgets(inventory[idx].name,     50, stdin);
            inventory[idx].name[strcspn(inventory[idx].name, "\n")] = '\0';
            printf("New Category : "); fgets(inventory[idx].category, 30, stdin);
            inventory[idx].category[strcspn(inventory[idx].category, "\n")] = '\0';
            printf("New Quantity : "); scanf("%d", &inventory[idx].quantity); getchar();
            printf("New Price    : "); scanf("%f", &inventory[idx].price);    getchar();
            break;
        default:
            printf("Invalid option!\n"); return;
    }
    printf("Product updated successfully!\n");
}

// ─── 5. Delete Product ────────────────────────────────────────────────────────
void deleteProduct() {
    if (totalProducts == 0) { printf("\nInventory is empty!\n"); return; }
    int id;
    printf("\nEnter Product ID to delete: "); scanf("%d", &id); getchar();
    int idx = findById(id);
    if (idx == -1) { printf("Product ID %d not found!\n", id); return; }

    printf("Deleting: %s (ID: %d)\n", inventory[idx].name, inventory[idx].id);

    // Shift left
    for (int i = idx; i < totalProducts - 1; i++)
        inventory[i] = inventory[i + 1];
    totalProducts--;

    printf("Product deleted successfully!\n");
}

// ─── 6. Low Stock Alert ───────────────────────────────────────────────────────
void displayLowStock() {
    int threshold = 5, found = 0;
    printf("\n========== LOW STOCK ALERT (Qty < %d) ==========", threshold);
    printHeader();
    for (int i = 0; i < totalProducts; i++) {
        if (inventory[i].quantity < threshold) {
            printProduct(inventory[i]);
            found++;
        }
    }
    if (!found) printf("All products have sufficient stock!\n");
    else printf("\n%d product(s) need restocking.\n", found);
}

// ─── 7. Sort by Price (Bubble Sort) ──────────────────────────────────────────
void sortByPrice() {
    if (totalProducts == 0) { printf("\nInventory is empty!\n"); return; }
    Product temp;
    for (int i = 0; i < totalProducts - 1; i++)
        for (int j = 0; j < totalProducts - i - 1; j++)
            if (inventory[j].price > inventory[j+1].price) {
                temp           = inventory[j];
                inventory[j]   = inventory[j+1];
                inventory[j+1] = temp;
            }
    printf("Sorted by price (ascending).\n");
    displayAll();
}

// ─── 8. Sort by Name (Bubble Sort) ───────────────────────────────────────────
void sortByName() {
    if (totalProducts == 0) { printf("\nInventory is empty!\n"); return; }
    Product temp;
    for (int i = 0; i < totalProducts - 1; i++)
        for (int j = 0; j < totalProducts - i - 1; j++)
            if (strcmp(inventory[j].name, inventory[j+1].name) > 0) {
                temp           = inventory[j];
                inventory[j]   = inventory[j+1];
                inventory[j+1] = temp;
            }
    printf("Sorted by name (A-Z).\n");
    displayAll();
}

// ─── 9. Total Inventory Value ─────────────────────────────────────────────────
void totalInventoryValue() {
    if (totalProducts == 0) { printf("\nInventory is empty!\n"); return; }
    float total = 0;
    printf("\n%-20s %-8s %-10s %-12s\n",
           "Name", "Qty", "Price", "Value(Rs)");
    printf("%-20s %-8s %-10s %-12s\n",
           "--------------------", "--------", "----------", "------------");
    for (int i = 0; i < totalProducts; i++) {
        float val = inventory[i].quantity * inventory[i].price;
        printf("%-20s %-8d %-10.2f %-12.2f\n",
               inventory[i].name, inventory[i].quantity,
               inventory[i].price, val);
        total += val;
    }
    printf("----------------------------------------------\n");
    printf("TOTAL INVENTORY VALUE : Rs %.2f\n", total);
}

// ─── 10. Filter by Category ───────────────────────────────────────────────────
void displayByCategory() {
    if (totalProducts == 0) { printf("\nInventory is empty!\n"); return; }
    char cat[30];
    printf("\nEnter category to filter: ");
    fgets(cat, 30, stdin);
    cat[strcspn(cat, "\n")] = '\0';

    int found = 0;
    printf("\n========== CATEGORY: %s ==========", cat);
    printHeader();
    for (int i = 0; i < totalProducts; i++) {
        if (strcasecmp(inventory[i].category, cat) == 0) {
            printProduct(inventory[i]);
            found++;
        }
    }
    if (!found) printf("No products found in category \"%s\"!\n", cat);
    else printf("\n%d product(s) found.\n", found);
}

// ─── 11. Summary ──────────────────────────────────────────────────────────────
void displaySummary() {
    if (totalProducts == 0) { printf("\nInventory is empty!\n"); return; }

    float totalValue = 0, maxPrice = inventory[0].price,
          minPrice   = inventory[0].price;
    int   totalQty   = 0, lowStock = 0;

    for (int i = 0; i < totalProducts; i++) {
        totalValue += inventory[i].quantity * inventory[i].price;
        totalQty   += inventory[i].quantity;
        if (inventory[i].price > maxPrice) maxPrice = inventory[i].price;
        if (inventory[i].price < minPrice) minPrice = inventory[i].price;
        if (inventory[i].quantity < 5)     lowStock++;
    }

    printf("\n╔══════════════════════════════════════╗\n");
    printf("║         INVENTORY SUMMARY            ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  Total Products     : %-14d ║\n", totalProducts);
    printf("║  Total Quantity     : %-14d ║\n", totalQty);
    printf("║  Total Value (Rs)   : %-14.2f ║\n", totalValue);
    printf("║  Highest Price (Rs) : %-14.2f ║\n", maxPrice);
    printf("║  Lowest  Price (Rs) : %-14.2f ║\n", minPrice);
    printf("║  Low Stock Items    : %-14d ║\n", lowStock);
    printf("╚══════════════════════════════════════╝\n");
}