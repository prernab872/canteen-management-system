#include <stdio.h>

// Function to display menu
void displayMenu() {
    printf("\n------ MENU ------\n");
    printf("1. Burger - 50\n");
    printf("2. Pizza - 120\n");
    printf("3. Momos - 60\n");
    printf("4. Tea - 10\n");
    printf("------------------\n");
}

// Function to generate bill
void generateBill(int total) {
    printf("\n------ FINAL BILL ------\n");
    printf("Total Amount = %d\n", total);
    printf("------------------------\n");
}

int main() {
    int choice, item, qty;
    int total = 0;

    while (1) {
        printf("\n===== CANTEEN SYSTEM =====\n");
        printf("1. Order Food\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            total = 0;  // reset for new order

            while (1) {
                displayMenu();

                printf("Enter item number (0 to finish): ");
                scanf("%d", &item);

                if (item == 0) {
                    break;
                }

                if (item < 1 || item > 4) {
                    printf("Invalid item! Try again.\n");
                    continue;
                }

                printf("Enter quantity: ");
                scanf("%d", &qty);

                if (qty <= 0) {
                    printf("Invalid quantity!\n");
                    continue;
                }

                // Calculate total
                if (item == 1) total += 50 * qty;
                else if (item == 2) total += 120 * qty;
                else if (item == 3) total += 60 * qty;
                else if (item == 4) total += 10 * qty;
            }

            generateBill(total);
        }
        else if (choice == 2) {
            printf("Thank you! Visit again.\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
