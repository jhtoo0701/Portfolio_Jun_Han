#ifndef CART_H
#define CART_H
#include <iostream>
#include <string>
#include<iomanip>
#include "Inventory.h"
#include "Basic_Admin.h"
using namespace std;

struct CartNode {
    int productId;
    string productName;
    int quantity;
    double price;
    CartNode* next;
};

void addToCart(CartNode* &cartTop, Product inventory[], int inventoryCount, ProductNode* inventoryHead) {

    int id, qty;
    cout << "Enter Product ID: ";
    cin >> id;
    cout << "Enter Quantity: ";
    cin >> qty;

    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].id == id) {

            if (qty <= 0 || qty > inventory[i].quantity) {
                cout << "Invalid or insufficient stock\n";
                return;
            }

            inventory[i].quantity -= qty;

            ProductNode* cur = inventoryHead;
            while (cur != nullptr) {
                if (cur->data.id == id) {
                    cur->data.quantity -= qty;
                    break;
                }
                cur = cur->next;
            }

            CartNode* newNode = new CartNode;
            newNode->productId = inventory[i].id;
            newNode->productName = inventory[i].name;
            newNode->quantity = qty;
            newNode->price = inventory[i].price;

            newNode->next = cartTop;
            cartTop = newNode;

            cout << "Product added to cart\n";
            return;
        }
    }

    cout << "Product not found\n";
}

void undoCartItem(CartNode* &cartTop, Product inventory[], int inventoryCount, ProductNode* inventoryHead) {

    if (cartTop == nullptr) {
        cout << "Cart is empty\n";
        return;
    }

    CartNode* temp = cartTop;

    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].id == temp->productId) {
            inventory[i].quantity += temp->quantity;
            break;
        }
    }

    ProductNode* cur = inventoryHead;
    while (cur != nullptr) {
        if (cur->data.id == temp->productId) {
            cur->data.quantity += temp->quantity;
            break;
        }
        cur = cur->next;
    }

    cartTop = cartTop->next;
    delete temp;

    cout << "Last cart item undone (LIFO)\n";
}

void viewCart(CartNode* cartTop) {

    if (cartTop == nullptr) {
        cout << "Cart is Empty\n";
        return;
    }

    cout << "\n===== CART ITEMS =====\n";
    CartNode* cur = cartTop;

    while (cur != nullptr) {
        cout << cur->productName
             << " | Qty: " << cur->quantity
             << " | RM " << cur->price << endl;
        cur = cur->next;
    }
}

double cartTotal(CartNode* cartTop) {
    double total = 0;
    while (cartTop != nullptr) {
        total += cartTop->quantity * cartTop->price;
        cartTop = cartTop->next;
    }
    return total;
}

void clearCart(CartNode* &cartTop, Product inventory[], int inventoryCount, ProductNode* inventoryHead){
    while (cartTop != nullptr) {
        undoCartItem(cartTop, inventory, inventoryCount, inventoryHead);
    }
    cout << "Cart cleared\n";
}

void checkoutCart(CartNode* &cartTop, Transaction transactions[], int &transactionCount, TransactionNode* &undoTop) {

    if (cartTop == nullptr) {
        cout << "Cart is empty\n";
        return;
    }

    double total = 0.0;

    cout << "\n================ CHECKOUT SUMMARY =================\n";

    while (cartTop != nullptr) {

        CartNode* temp = cartTop;

        double subtotal = temp->quantity * temp->price;
        total += subtotal;

        cout << "| Name: " << temp->productName
             << " | Qty: " << temp->quantity
             << " | Subtotal: RM " << fixed << setprecision(2)
             << subtotal << endl;

        Transaction t;
        t.productId    = temp->productId;
        t.productName  = temp->productName;
        t.quantitySold = temp->quantity;
        t.totalPrice   = subtotal;

        transactions[transactionCount++] = t;
        pushUndo(undoTop, t);

        cartTop = cartTop->next;
        delete temp;
    }

    cout << "--------------------------------------------------\n";
    cout << "TOTAL: RM " << fixed << setprecision(2) << total << endl;
    cout << "Checkout completed\n";
}

#endif
