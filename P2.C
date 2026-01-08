/*SuperMarket Smart Manager */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 50
#define MAX_CART 50
#define STAFF_PASSWORD "Admin@25"

struct Product {
    int id;
    char name[50];
    float price;
    int stock;
};

struct CartItem {
    int id;
    char name[50];
    float price;
    int qty;
};

/* functions */
void productList(struct Product *p, int count);/* Displays all products in formatted table*/

void staffMenu(struct Product *p, int *count);
void addNewProduct(struct Product *p, int *count);/*Adds new products with validation*/
void updateProduct(struct Product *p, int count);/*Updates price or stock information*/

void customerMenu(struct Product *p, int count, struct CartItem *cart, int *cartCount);
void cartMenu(struct Product *p, int count, struct CartItem *cart, int *cartCount);

void addToCart(struct Product *p, int count, struct CartItem *cart, int *cartCount);
void viewCart(struct CartItem *cart, int cartCount);
void removeFromCart(struct CartItem *cart, int *cartCount);

void billingMenu(struct CartItem *cart, int *cartCount);
void generateBill(struct CartItem *cart, int *cartCount);/*Calculates totals and applies GST*/
float calculateGST(float total);/*- Computes 18% tax on subtotal
*/

int main() {
    struct Product inventory[MAX_PRODUCTS] = {
        {1, "Apple", 50, 40},
        {2, "Milk", 30, 20},
        {3, "Bread", 25, 15},
        {4, "Rice", 60, 50}
    };

    int productCount = 4;

    struct CartItem cart[MAX_CART];
    int cartCount = 0;

    int choice;

    while (1) {
        printf("\n================ MAIN MENU ================\n");
        printf("1. Customer Section\n");
        printf("2. Staff Section\n");
        printf("3. Billing Section\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customerMenu(inventory, productCount, cart, &cartCount);
                break;

            case 2:
                staffMenu(inventory, &productCount);
                break;

            case 3:
                billingMenu(cart, &cartCount);
                break;

            case 4:
                printf("\nThank you! System Closed.\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

/* productList FUNCTION - ADDED */
void productList(struct Product *p, int count) {
    printf("\n============= PRODUCTS LIST =============\n");
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Price", "Stock");
    for(int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10.2f %-10d\n", p[i].id, p[i].name, p[i].price, p[i].stock);
    }
}

/* STAFF SECTION  */
void staffMenu(struct Product *p, int *count) {
  char pass[20];
int ch;

while(1) {
    printf("\nEnter Staff Password: ");
    scanf("%s", pass);
    if (strcmp(pass, "Admin@25") == 0) break;
    printf("WRONG PASSWORD! Re-enter:\n");
}


    while (1) {
        printf("\n------------ STAFF SECTION ------------\n");
        printf("1. Show Inventory\n");
        printf("2. Add New Product\n");
        printf("3. Update Existing Product\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice(only integers ): ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                productList(p, *count);
                break;

            case 2:
                addNewProduct(p, count);
                break;

            case 3:
                updateProduct(p, *count);
                break;

            case 4:
                return;

            default:
                printf("Invalid choice!\n");
        }
    }
}

/* Add new product*/
void addNewProduct(struct Product *p, int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("Inventory FULL! Cannot add more products.\n");
        return;
    }

    printf("\nEnter Product ID: ");
    scanf("%d", &p[*count].id);

    printf("Enter Product Name: ");
    getchar();
    scanf("%49[^\n]", p[*count].name);

    printf("Enter Price: ");
    scanf("%f", &p[*count].price);

    printf("Enter Stock: ");
    scanf("%d", &p[*count].stock);

    (*count)++;

    printf("New product added successfully!\n");
}

// Update an existing product
void updateProduct(struct Product *p, int count) {
    int id, pos = -1, choice;
    float newPrice;
    int newQty;

    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (p[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Product not found!\n");
        return;
    }

    printf("\nWhat do you want to update?\n");
    printf("1. Price\n");
    printf("2. Stock\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new price: ");
            scanf("%f", &newPrice);
            p[pos].price = newPrice;
            printf("Price updated!\n");
            break;

        case 2:
            printf("Enter new stock: ");
            scanf("%d", &newQty);
            p[pos].stock = newQty;
            printf("Stock updated!\n");
            break;

        default:
            printf("Invalid choice!\n");
    }
}

// CUSTOMER SECTION (SEARCH REMOVED)
void customerMenu(struct Product *p, int count, struct CartItem *cart, int *cartCount) {
    int ch;

    while (1) {
        printf("\n------------ CUSTOMER SECTION ------------\n");
        printf("1. View Product List\n");
        printf("2. Cart\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                productList(p, count);
                break;

            case 2:
                cartMenu(p, count, cart, cartCount);
                break;

            case 3:
                return;

            default:
                printf("Invalid choice!\n");
        }
    }
}

/* cartMenu FUNCTION - ADDED */
void cartMenu(struct Product *p, int count, struct CartItem *cart, int *cartCount) {
    int ch;
    while(1) {
        printf("\n--- CART MENU ---\n");
        printf("1. Add to Cart\n");
        printf("2. View Cart\n");
        printf("3. Remove from Cart\n");
        printf("4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        
        switch(ch) {
            case 1: addToCart(p, count, cart, cartCount); break;
            case 2: viewCart(cart, *cartCount); break;
            case 3: removeFromCart(cart, cartCount); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    }
}

//Add item to cart
void addToCart(struct Product *p, int count, struct CartItem *cart, int *cartCount) {
    int id, qty, pos = -1;

    printf("Enter Product ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (p[i].id == id)
            pos = i;
    }

    if (pos == -1) {
        printf("Product not found!\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &qty);

    if (qty > p[pos].stock) {
        printf("Not enough stock!\n");
        return;
    }

    if (*cartCount >= MAX_CART) {
        printf("Cart is FULL!\n");
        return;
    }

    cart[*cartCount].id = p[pos].id;
    strcpy(cart[*cartCount].name, p[pos].name);
    cart[*cartCount].price = p[pos].price;
    cart[*cartCount].qty = qty;

    (*cartCount)++;

    printf("Item added to cart!\n");
}

//View cart
void viewCart(struct CartItem *cart, int cartCount) {
    if (cartCount == 0) {
        printf("Cart is empty!\n");
        return;
    }

    printf("\n============= CART ITEMS =============\n");
    printf("%-5s %-15s %-10s %-10s\n", "ID", "Name", "Qty", "Price");

    for (int i = 0; i < cartCount; i++) {
        printf("%-5d %-15s %-10d %-10.2f\n",
               cart[i].id, cart[i].name, cart[i].qty, cart[i].price);
    }
}

//Remove item from cart
void removeFromCart(struct CartItem *cart, int *cartCount) {
    int id, pos = -1;

    if (*cartCount == 0) {
        printf("Cart empty!\n");
        return;
    }

    printf("Enter Product ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < *cartCount; i++) {
        if (cart[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Item not in cart!\n");
        return;
    }

    for (int i = pos; i < *cartCount - 1; i++) {
        cart[i] = cart[i + 1];
    }

    (*cartCount)--;

    printf("Item removed!\n");
}

//BILLING
void billingMenu(struct CartItem *cart, int *cartCount) {
    int ch;

    while (1) {
        printf("\n------------ BILLING SECTION ------------\n");
        printf("1. Generate Bill\n");
        printf("2. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                generateBill(cart, cartCount);
                break;
            case 2:
                return;

            default:
                printf("Invalid choice!\n");
        }
    }
}

void generateBill(struct CartItem *cart, int *cartCount) {
    if (*cartCount == 0) {
        printf("Cart empty! Cannot generate bill.\n");
        return;
    }

    float total = 0;

    printf("\n============= FINAL BILL =============\n");
    printf("%-5s %-15s %-10s %-10s\n", "ID", "Name", "Qty", "Amount");

    for (int i = 0; i < *cartCount; i++) {
        float amt = cart[i].qty * cart[i].price;
        total += amt;

        printf("%-5d %-15s %-10d %-10.2f\n",
               cart[i].id, cart[i].name, cart[i].qty, amt);
    }

    float gst = calculateGST(total);
    float grand = total + gst;

    printf("\nSubtotal: %.2f\n", total);
    printf("GST (18%%): %.2f\n", gst);
    printf("Grand Total: %.2f\n", grand);
    printf("=====================================\n");

    *cartCount = 0;  // empty cart after bill
}

float calculateGST(float total) {
    return total * 0.18;
}
