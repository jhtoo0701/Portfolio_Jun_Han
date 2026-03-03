#ifndef BASIC_ADMIN_H
#define BASIC_ADMIN_H
#include <iostream>
#include <string>
#include "Inventory.h"
#define MAX_PRODUCTS 100
#define MAX_TRANSACTIONS 100
using namespace std;

void addProduct(Product inventory[], int &inventoryCount, ProductNode* &inventoryHead) {
    if (inventoryCount >= MAX_PRODUCTS) {
        cout << "Inventory full\n";
        return;
    }

    Product p;
    cout << "Enter Product ID: ";
    cin >> p.id;

    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].id == p.id) {
            cout << "Product ID already exists. Please use a unique ID.\n";
            return;
        }
    }

    cin.ignore();
    cout << "Enter Product Name: ";
    getline(cin, p.name);

    cout << "Enter Quantity: ";
    cin >> p.quantity;

    cout << "Enter Price: ";
    cin >> p.price;

    if (p.price < 0 || p.quantity < 0) {
        cout << "Invalid price or quantity!\n";
        return;
    }

    inventory[inventoryCount++] = p;
    insertProductNode(inventoryHead, p);
    cout << "Product added successfully\n";
}

void updateProduct(Product inventory[], int inventoryCount, ProductNode* inventoryHead) {
    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;

    bool found = false;
    Product updatedProduct;

    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].id == id) {

            cin.ignore();
            cout << "New Name: ";
            getline(cin, inventory[i].name);

            cout << "New Quantity: ";
            cin >> inventory[i].quantity;

            cout << "New Price: ";
            cin >> inventory[i].price;

            if (inventory[i].price < 0 || inventory[i].quantity < 0) {
                cout << "Invalid price or quantity!\n";
                return;
            }

            updatedProduct = inventory[i];
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Product not found\n";
        return;
    }

    ProductNode* cur = inventoryHead;
    while (cur != nullptr) {
        if (cur->data.id == id) {
            cur->data = updatedProduct;
            break;
        }
        cur = cur->next;
    }

    cout << "Product updated successfully\n";
}

void deleteProduct(Product inventory[], int &inventoryCount, ProductNode* &inventoryHead) {
    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].id == id) {
            for (int j = i; j < inventoryCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            inventoryCount--;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Product not found\n";
        return;
    }

    deleteProductNode(inventoryHead, id);

    cout << "Product deleted successfully\n";
}

void displayProducts(Product inventory[], int inventoryCount) {
    if (inventoryCount == 0) {
        cout << "No products available\n";
        return;
    }

    cout << "\n===== PRODUCT LIST =====\n";
    for (int i = 0; i < inventoryCount; i++) {
        cout << inventory[i].id << " | "
             << inventory[i].name << " | "
             << inventory[i].quantity << " | RM "
             << inventory[i].price << endl;
    }
}

void makeSale(ProductNode* inventoryHead, Product inventory[], int inventoryCount, Transaction transactions[], int &transactionCount, TransactionNode* &undoTop) {

    int id, qty;
    cout << "Enter Product ID: ";
    cin >> id;
    cout << "Enter Quantity Sold: ";
    cin >> qty;

    ProductNode* cur = inventoryHead;

    while (cur != nullptr) {
        if (cur->data.id == id) {

            if (qty <= 0 || qty > cur->data.quantity) {
                cout << "Invalid or insufficient stock\n";
                return;
            }

            cur->data.quantity -= qty;

            for (int i = 0; i < inventoryCount; i++) {
                if (inventory[i].id == id) {
                    inventory[i].quantity -= qty;
                    break;
                }
            }

            Transaction t;
            t.productId = cur->data.id;
            t.productName = cur->data.name;
            t.quantitySold = qty;
            t.totalPrice = qty * cur->data.price;

            transactions[transactionCount++] = t;
            pushUndo(undoTop, t);

            cout << "Sale completed\n";
            return;
        }
        cur = cur->next;
    }

    cout << "Product not found\n";
}

void viewLastTransaction(Transaction transactions[], int transactionCount) {
    if (transactionCount == 0) {
        cout << "No transactions yet\n";
        return;
    }

    Transaction t = transactions[transactionCount - 1];

    cout << "\n===== LAST TRANSACTION =====\n";
    cout << "Product ID: " << t.productId
         << " | Name: " << t.productName
         << " | Quantity: " << t.quantitySold
         << " | Total: RM " << t.totalPrice << endl;
}

#endif
