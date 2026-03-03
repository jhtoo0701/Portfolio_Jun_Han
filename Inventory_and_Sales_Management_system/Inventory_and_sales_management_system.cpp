#include <iostream>
#include <string>
#include <windows.h>
#include "Inventory.h"
#include "Basic_Admin.h"
#include "Cart.h"
#define MAX_PRODUCTS 100
#define MAX_TRANSACTIONS 100
using namespace std;

Product inventory[MAX_PRODUCTS];
Transaction transactions[MAX_TRANSACTIONS];
ProductNode* inventoryHead = nullptr;
TransactionNode* undoTop = nullptr;
CartNode* cartTop = nullptr;

int inventoryCount = 0;
int transactionCount = 0;

void setColor(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void resetColor() {
    setColor(7);
}

void pauseScreen() {
    setColor(8);
    cout << "\nPress Enter to continue...";
    resetColor();
    cin.ignore(1000, '\n');
    cin.get();
}

void printError(string message) {
    setColor(12);
    cout << "\n[ERROR] " << message << endl;
    resetColor();
}

void printSuccess(string message) {
    setColor(10);
    cout << "\n[SUCCESS] " << message << endl;
    resetColor();
}

bool isAdmin = false;

bool adminLogin() {
    string u, p;
    cout << "\n=== Admin Login ===\n";
    cout << "Username: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    if (u == "admin" && p == "admin") {
        cout << "Admin login successful";
        cout << endl <<endl;
        return true;
    }
    cout << "Invalid username or password!";
    cout << endl;
    return false;
}

bool loginRole() {
    string c;
    while (true) {
        setColor(2);
        cout << "\nLogin as:\n";
        cout << "1. Admin\n";
        cout << "2. User\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> c;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input";
            cout << endl;
            continue;
        }

        if(c == "ADMIN" || c == "admin" || c == "Admin" || c == "1") {
             if (adminLogin()) {
                isAdmin = true;
                return true;
            }
        }
        else if(c == "USER" || c == "user" || c == "User" || c == "2") {
            isAdmin = false;
            cout << "User login successful\n\n";
            return true;
        }
         else if(c == "EXIT" || c == "exit" || c == "Exit" || c == "3") {
            cout << endl;
            cout << "Exiting the program...\n";
            cout << "Bye! Hope to see you soon\n";
            cout << "Have a nice day ^_^\n";
            return false;
        }
        else {
            printError("Invalid choice");
        }
    }
}

void showMenu() {
    setColor(11);
    cout << "===========================================\n";
    cout << "   INVENTORY & SALES MANAGEMENT SYSTEM\n";
    cout << "===========================================\n";
    resetColor();

    if (isAdmin) {
        cout << "[ADMIN MODE]\n\n";
    } else {
        cout << "[USER MODE]\n\n";
    }

    setColor(3);
    cout << " 1. Add Product\n";
    cout << " 2. Update Product\n";
    cout << " 3. Delete Product\n";
    cout << " 4. Display Products\n";
    cout << " 5. Make Sale\n";
    cout << " 6. View Last Transaction\n";
    cout << " 7. Undo Last Transaction\n";
    cout << endl;

    setColor(6);
    cout << "-------------------------------------------\n";
    cout << "               INVENTORY\n";
    cout << "-------------------------------------------\n";
    cout << " 8. Search Product\n";
    cout << " 9. Filter by Price\n";
    cout << "10. Sort by ID\n";
    cout << "11. Extract the Inventory in txt file\n";
    cout << endl;

    setColor(15);
    cout << "+++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                 CART\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "12. Add to Cart\n";
    cout << "13. View Cart\n";
    cout << "14. Undo Cart Item\n";
    cout << "15. View Cart Total\n";
    cout << "16. Clear Cart\n";
    cout << "17. Checkout\n";
    cout << endl;

    setColor(11);
    cout << "###########################################\n";
    cout << "                 QUIT\n";
    cout << "###########################################\n";
    cout << " 0. Exit\n";
    cout << endl;

    setColor(2);
    cout << "Enter choice: ";
    resetColor();
}

int main() {

    while (true) {
        if (!loginRole()) {
            break;
        }

        int choice;

        do {
            showMenu();
            cin >> choice;

            if (choice >= 1 && choice <= 11) {
                if (!isAdmin) {
                    printError("Admin only access");
                } else {
                    if (choice == 1){
                            addProduct(inventory, inventoryCount, inventoryHead);
                    }
                    else if (choice == 2){
                            updateProduct(inventory, inventoryCount, inventoryHead);
                    }
                    else if (choice == 3){
                            deleteProduct(inventory, inventoryCount, inventoryHead);
                    }
                    else if (choice == 4){
                            displayProductsLL(inventoryHead);
                    }
                    else if (choice == 5){
                            makeSale(inventoryHead, inventory, inventoryCount,
                                     transactions, transactionCount, undoTop);
                    }
                    else if (choice == 6){
                        viewLastTransaction(transactions, transactionCount);
                    }
                    else if (choice == 7){
                        undoLastTransaction(inventoryHead, inventory, inventoryCount, undoTop);
                    }
                    else if (choice == 8){
                        searchProduct(inventoryHead);
                    }
                    else if (choice == 9){
                        filterByPriceRange(inventoryHead);
                    }
                    else if (choice == 10){
                        sortProductsById(inventory, inventoryCount);
                        rebuildLinkedListFromArray(inventoryHead, inventory, inventoryCount);
                        displayProductsLL(inventoryHead);
                    }
                    else if (choice == 11){
                        saveInventory(inventory, inventoryCount);
                        cout << "Inventory saved to file" << endl;
                    }
            }
        }
            else if (choice >= 12 && choice <= 17) {
                if (isAdmin) {
                   printError("User only access");

                } else {
                    if (choice == 12){
                        addToCart(cartTop, inventory, inventoryCount, inventoryHead);
                    }
                    else if (choice == 13){
                        viewCart(cartTop);
                    }
                    else if (choice == 14){
                        undoCartItem(cartTop, inventory, inventoryCount, inventoryHead);
                    }
                    else if (choice == 15){
                        cout << "Total: RM " << cartTotal(cartTop) << endl;
                    }
                    else if (choice == 16){
                        clearCart(cartTop, inventory, inventoryCount, inventoryHead);
                    }
                    else if (choice == 17){
                        checkoutCart(cartTop, transactions, transactionCount, undoTop);
                    }
                }
            }

            else if (choice == 0 || choice == 'o') {
                printSuccess("Logged out");
            }
            else {
                printError("Invalid choice");
            }

            if (choice != 0) pauseScreen();

        } while (choice != 0);
    }

    return 0;
}
