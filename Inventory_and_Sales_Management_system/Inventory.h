#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Product {
    int id;
    std::string name;
    int quantity;
    double price;
};

struct Transaction {
    int productId;
    std::string productName;
    int quantitySold;
    double totalPrice;
};

struct ProductNode {
    Product data;
    ProductNode* next;
};

struct TransactionNode {
    Transaction data;
    TransactionNode* next;
};

void insertProductNode(ProductNode* &head, Product p) {
    ProductNode* newNode = new ProductNode;
    newNode->data = p;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        ProductNode* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
}

void deleteProductNode(ProductNode*& head, int id) {
    if (head == nullptr) {
        return;
    }

    if (head->data.id == id) {
        ProductNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    ProductNode* cur = head;

    while (cur->next != nullptr) {
        if (cur->next->data.id == id) {
            ProductNode* temp = cur->next;
            cur->next = temp->next;
            delete temp;
            return;
        }
        cur = cur->next;
    }
}

void searchProduct(ProductNode* head) {
    if (head == nullptr) {
        cout << "Inventory is empty.\n";
        return;
    }

    int choice;
    cout << "\nSearch by:\n";
    cout << "1. Product ID\n";
    cout << "2. Product Name\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int id;
        cout << "Enter Product ID: ";
        cin >> id;

        ProductNode* cur = head;
        while (cur != nullptr) {
            if (cur->data.id == id) {
                cout << "\nProduct Found:\n";
                cout << cur->data.id << " | "
                     << cur->data.name << " | "
                     << cur->data.quantity << " | RM "
                     << cur->data.price << endl;
                return;
            }
            cur = cur->next;
        }

        cout << "Product not found.\n";
    }
    else if (choice == 2) {
        string name;
        cin.ignore();
        cout << "Enter Product Name: ";
        getline(cin, name);

        bool found = false;
        ProductNode* cur = head;

        while (cur != nullptr) {
            if (cur->data.name == name) {
                cout << cur->data.id << " | "
                     << cur->data.name << " | "
                     << cur->data.quantity << " | RM "
                     << cur->data.price << endl;
                found = true;
            }
            cur = cur->next;
        }

        if (!found) {
            cout << "Product not found.\n";
        }
    }
    else {
        cout << "Invalid choice.\n";
    }
}

void filterByPriceRange(ProductNode* head) {
    if (head == nullptr) {
        cout << "Inventory is empty.\n";
        return;
    }

    double minP, maxP;
    cout << "Enter Minimum Price: RM ";
    cin >> minP;
    cout << "Enter Maximum Price: RM ";
    cin >> maxP;

    if (minP > maxP) {
        cout << "Invalid price range.\n";
        return;
    }

    bool found = false;
    ProductNode* cur = head;

    cout << "\n===== PRODUCTS IN PRICE RANGE =====\n";
    while (cur != nullptr) {
        if (cur->data.price >= minP &&
            cur->data.price <= maxP) {

            cout << cur->data.id << " | "
                 << cur->data.name << " | "
                 << cur->data.quantity << " | RM "
                 << cur->data.price << endl;

            found = true;
        }
        cur = cur->next;
    }

    if (!found) {
        cout << "No products found in this price range.\n";
    }
}

int partition(Product inventory[], int low, int high) {
    int pivot = inventory[high].id;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (inventory[j].id < pivot) {
            i++;

            Product temp = inventory[i];
            inventory[i] = inventory[j];
            inventory[j] = temp;
        }
    }

    Product temp = inventory[i + 1];
    inventory[i + 1] = inventory[high];
    inventory[high] = temp;

    return i + 1;
}

void quickSort(Product inventory[], int low, int high) {
    if (low < high) {
        int pi = partition(inventory, low, high);

        quickSort(inventory, low, pi - 1);
        quickSort(inventory, pi + 1, high);
    }
}

void sortProductsById(Product inventory[], int size) {
    if (size <= 1) {
        cout << "No products to sort.\n";
        return;
    }

    quickSort(inventory, 0, size - 1);
    cout << "Products sorted by Product ID!\n";
}

void pushUndo(TransactionNode* &undoTop, Transaction t) {
    TransactionNode* newNode = new TransactionNode;
    newNode->data = t;
    newNode->next = undoTop;
    undoTop = newNode;
}

void undoLastTransaction(ProductNode* inventoryHead, Product inventory[], int inventoryCount, TransactionNode* &undoTop) {
    if (undoTop == nullptr) {
        cout << "No transaction to undo.\n";
        return;
    }

    Transaction last = undoTop->data;
    TransactionNode* temp = undoTop;
    undoTop = undoTop->next;
    delete temp;

    bool found = false;

    ProductNode* cur = inventoryHead;
    while (cur != nullptr) {
        if (cur->data.id == last.productId) {
            cur->data.quantity += last.quantitySold;
            found = true;
            break;
        }
        cur = cur->next;
    }

    for (int i = 0; i < inventoryCount; i++) {
        if (inventory[i].id == last.productId) {
            inventory[i].quantity += last.quantitySold;
            break;
        }
    }

    if (found) {
        cout << "Last transaction undone successfully.\n";
    } else {
        cout << "Product not found in inventory during undo.\n";
    }
}

void displayProductsLL(ProductNode* head) {
    if (head == nullptr) {
        cout << "No products available\n";
        return;
    }

    cout << "\n===== PRODUCT LIST =====\n";
    ProductNode* cur = head;

    while (cur != nullptr) {
        cout << cur->data.id << " | "
             << cur->data.name << " | "
             << cur->data.quantity << " | RM "
             << cur->data.price << endl;
        cur = cur->next;
    }
}

void saveInventory(Product inventory[], int count) {
    ofstream file("inventory.txt");
    for (int i = 0; i < count; i++) {
        file << inventory[i].id << " " << inventory[i].name << " " << inventory[i].quantity << " " << inventory[i].price << endl;
    }
    file.close();
}

void rebuildLinkedListFromArray(ProductNode* &head, Product inventory[], int count) {

    while (head != nullptr) {
        ProductNode* temp = head;
        head = head->next;
        delete temp;
    }

    head = nullptr;

    for (int i = 0; i < count; i++) {
        insertProductNode(head, inventory[i]);
    }
}

#endif
