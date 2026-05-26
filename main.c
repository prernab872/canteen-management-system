#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- STRUCT ----------
struct Item {
    int id;
    char name[50];
    float price;
};

// ---------- ADMIN LOGIN ----------
int adminLogin() {
    char username[20], password[20];

    printf("\n--- ADMIN LOGIN ---\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("\nLogin Successful!\n");
        return 1;
    } else {
        printf("\nInvalid Credentials!\n");
        return 0;
    }
}

// ---------- ADD ITEM ----------
void addItem() {
    FILE *fp = fopen("menu.txt", "a");
    struct Item i;

    printf("\nEnter Item ID: ");
    scanf("%d", &i.id);
    printf("Enter Item Name: ");
    scanf(" %[^\n]", i.name);
    printf("Enter Price: ");
    scanf("%f", &i.price);

    fprintf(fp, "%d %s %.2f\n", i.id, i.name, i.price);
    fclose(fp);

    printf("Item Added Successfully!\n");
}
//-----------VIEW MENU----------------
void viewMenu() {
    FILE *fp = fopen("menu.txt", "r");
    struct Item i;

    if (fp == NULL) {
        printf("Menu file not found!\n");
        return;
    }

    printf("\n------ MENU ------\n");

    while (fscanf(fp, "%d %s %f", &i.id, i.name, &i.price) == 3) {
        printf("%d. %-20s Rs %.2f\n", i.id, i.name, i.price);
    }

    fclose(fp);
}


// ---------- DELETE ITEM ----------
void deleteItem() {
    FILE *fp = fopen("menu.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int id, found = 0;
    struct Item i;

    printf("Enter Item ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d %s %f", &i.id, i.name, &i.price) != EOF) {
        if (i.id != id) {
            fprintf(temp, "%d %s %.2f\n", i.id, i.name, i.price);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("menu.txt");
    rename("temp.txt", "menu.txt");

    if (found)
        printf("Item Deleted!\n");
    else
        printf("Item Not Found!\n");
}

// ---------- ADMIN PANEL ----------
void adminPanel() {
    int choice;

    if (!adminLogin()) return;

    do {
        printf("\n--- ADMIN PANEL ---\n");
        printf("1. Add Item\n");
        printf("2. View Menu\n");
        printf("3. Delete Item\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addItem(); break;
            case 2: viewMenu(); break;
            case 3: deleteItem(); break;
        }

    } while (choice != 4);
}

// ---------- PLACE ORDER ----------
void placeOrder() {
    FILE *fp = fopen("menu.txt", "r");
    struct Item menu[50];
    int count = 0;

    
    while (fscanf(fp, "%d %s %f", &menu[count].id, menu[count].name, &menu[count].price) != EOF) {
        count++;
    }
    fclose(fp);

    int choice, qty;
    float total = 0;
    char cont;

    FILE *bill = fopen("bill.txt", "w");

    fprintf(bill, "------ BILL ------\n");

    do {
        viewMenu();

        printf("\nEnter Item ID: ");
        scanf("%d", &choice);
        printf("Enter Quantity: ");
        scanf("%d", &qty);

        int found = 0;

        for (int i = 0; i < count; i++) {
            if (menu[i].id == choice) {
                float cost = menu[i].price * qty;
                total += cost;

                printf("Added: %s x%d = Rs %.2f\n", menu[i].name, qty, cost);
                fprintf(bill, "%s x%d = Rs %.2f\n", menu[i].name, qty, cost);

                found = 1;
                break;
            }
        }

        if (!found)
            printf("Invalid Item ID!\n");

        printf("\nDo you want to continue ordering? (y/n): ");
        scanf(" %c", &cont);

    } while (cont == 'y' || cont == 'Y');

    fprintf(bill, "-------------------\n");
    fprintf(bill, "Total = Rs %.2f\n", total);
    fclose(bill);

    printf("\n===== FINAL BILL =====\n");
    printf("Total Amount: Rs %.2f\n", total);
    printf("Bill saved in file (bill.txt)\n");
}

// ---------- MAIN ----------
int main() {
    int choice;

    do {
        printf("\n===== CANTEEN MANAGEMENT SYSTEM =====\n");
        printf("1. Admin Login\n");
        printf("2. Order Food\n");
        printf("3. View Menu\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: adminPanel(); break;
            case 2: placeOrder(); break;
            case 3: viewMenu(); break;
            case 4: printf("Thank you!\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
