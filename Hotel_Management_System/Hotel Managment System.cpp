#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>

using namespace std;

// ===============================
// Room Class
// ===============================
class Room {
public:
    int roomID;
    string type;
    double price;
    bool isAvailable;

    Room() : roomID(0), type(""), price(0.0), isAvailable(true) {}

    void addRoom() {
        cout << "\nEnter Room ID: ";
        while (!(cin >> roomID)) {
            cout << "Invalid input. Please enter a valid Room ID: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int roomTypeChoice;
        while (true) {
            cout << "\nSelect Room Type:\n";
            cout << "1. Single\n";
            cout << "2. Double\n";
            cout << "3. Suite\n";
            cout << "Enter choice (1-3): ";

            while (!(cin >> roomTypeChoice) || roomTypeChoice < 1 || roomTypeChoice > 3) {
                cout << "Invalid choice! Enter 1, 2, or 3: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (roomTypeChoice == 1) type = "Single";
            else if (roomTypeChoice == 2) type = "Double";
            else if (roomTypeChoice == 3) type = "Suite";

            break;
        }

        cout << "Enter Price per Night: ";
        while (!(cin >> price) || price <= 0) {
            cout << "Invalid price! Please enter again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        isAvailable = true;
        cout << "Room added successfully!\n";
    }

    void displayRoom() const {
        cout << "\nRoom ID: " << roomID
             << "\nType: " << type
             << "\nPrice: RM" << fixed << setprecision(2) << price
             << "\nAvailability: " << (isAvailable ? "Available" : "Occupied") << "\n";
    }
};

// ===============================
// Customer Class
// ===============================
class Customer {
public:
    int customerID;
    string name;
    string contact;

    Customer() : customerID(0), name(""), contact("") {}

    void addCustomer(const vector<Customer> &customers) {
        cout << "\nEnter Customer ID: ";

        // prevent duplicate customer ID
        while (true) {
            while (!(cin >> customerID)) {
                cout << "Invalid input. Please enter a valid Customer ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            bool idExists = false;
            for (const auto &c : customers) {
                if (c.customerID == customerID) {
                    idExists = true;
                    break;
                }
            }

            if (idExists) {
                cout << "Customer ID already exists! Enter another: ";
            } else break;
        }

        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Contact Number: ";

        // prevent duplicate contact
        while (true) {
            getline(cin, contact);

            bool contactExists = false;
            for (const auto &c : customers) {
                if (c.contact == contact) {
                    contactExists = true;
                    break;
                }
            }

            if (contactExists) {
                cout << "Contact number exists! Enter a different number: ";
            } else break;
        }

        cout << "Customer added successfully!\n";
    }

    void displayCustomer() const {
        cout << "\nCustomer ID: " << customerID
             << "\nName: " << name
             << "\nContact: " << contact << "\n";
    }
};

// ===============================
// Booking Class
// ===============================
class Booking {
public:
    int bookingID;
    int customerID;
    int roomID;
    int duration;
    double totalBill;

    Booking() : bookingID(0), customerID(0), roomID(0), duration(0), totalBill(0.0) {}

    void createBooking(vector<Room> &rooms, const vector<Booking> &bookings) {

        cout << "\nEnter Booking ID: ";

        // prevent duplicate booking ID
        while (true) {
            while (!(cin >> bookingID)) {
                cout << "Invalid input. Please enter valid Booking ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            bool idExists = false;
            for (const auto &b : bookings) {
                if (b.bookingID == bookingID) {
                    idExists = true;
                    break;
                }
            }

            if (idExists)
                cout << "Booking ID already exists! Enter another: ";
            else break;
        }

        cout << "Enter Customer ID: ";
        while (!(cin >> customerID)) {
            cout << "Invalid input. Enter valid Customer ID: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Room ID: ";
        while (!(cin >> roomID)) {
            cout << "Invalid input. Enter valid Room ID: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        bool roomFound = false;
        for (auto &room : rooms) {
            if (room.roomID == roomID && room.isAvailable) {
                roomFound = true;
                room.isAvailable = false;

                cout << "Enter Duration of Stay (days): ";
                while (!(cin >> duration) || duration <= 0) {
                    cout << "Invalid duration! Enter again: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                totalBill = room.price * duration;
                cout << "Booking created! Total Bill: RM" << fixed << setprecision(2) << totalBill << "\n";
                break;
            }
        }

        if (!roomFound) {
            cout << "Room not available or does not exist.\n";
        }
    }

    void displayBooking() const {
        cout << "\nBooking ID: " << bookingID
             << "\nCustomer ID: " << customerID
             << "\nRoom ID: " << roomID
             << "\nDuration: " << duration << " days"
             << "\nTotal Bill: RM" << fixed << setprecision(2) << totalBill << "\n";
    }
};

// ===============================
// File Handling
// ===============================
void saveData(const vector<Room> &rooms, const vector<Customer> &customers, const vector<Booking> &bookings) {
    ofstream roomFile("rooms.txt");
    for (const auto &room : rooms) {
        roomFile << room.roomID << " " << room.type << " " << room.price << " " << room.isAvailable << "\n";
    }
    roomFile.close();

    ofstream customerFile("customers.txt");
    for (const auto &customer : customers) {
        customerFile << customer.customerID << " " << customer.name << " " << customer.contact << "\n";
    }
    customerFile.close();

    ofstream bookingFile("bookings.txt");
    for (const auto &booking : bookings) {
        bookingFile << booking.bookingID << " " << booking.customerID << " "
                    << booking.roomID << " " << booking.duration << " " << booking.totalBill << "\n";
    }
    bookingFile.close();
}

void loadData(vector<Room> &rooms, vector<Customer> &customers, vector<Booking> &bookings) {
    ifstream roomFile("rooms.txt");
    if (roomFile.is_open()) {
        Room room;
        while (roomFile >> room.roomID >> room.type >> room.price >> room.isAvailable) {
            rooms.push_back(room);
        }
        roomFile.close();
    }

    ifstream customerFile("customers.txt");
    if (customerFile.is_open()) {
        Customer customer;
        while (customerFile >> customer.customerID >> customer.name >> customer.contact) {
            customers.push_back(customer);
        }
        customerFile.close();
    }

    ifstream bookingFile("bookings.txt");
    if (bookingFile.is_open()) {
        Booking booking;
        while (bookingFile >> booking.bookingID >> booking.customerID >> booking.roomID >> booking.duration >> booking.totalBill) {
            bookings.push_back(booking);
        }
        bookingFile.close();
    }
}

// ===============================
// Check-Out Function
// ===============================
void checkOut(vector<Booking> &bookings, vector<Room> &rooms) {
    int bookingID;
    cout << "\nEnter Booking ID to check out: ";

    while (!(cin >> bookingID)) {
        cout << "Invalid input! Enter valid Booking ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bool found = false;
    for (auto it = bookings.begin(); it != bookings.end(); it++) {
        if (it->bookingID == bookingID) {

            for (auto &room : rooms) {
                if (room.roomID == it->roomID)
                    room.isAvailable = true;
            }

            cout << "\nCheck-Out Details:\n";
            it->displayBooking();

            bookings.erase(it);
            cout << "Check-out successful!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Booking ID not found.\n";
}

// ===============================
// Main Menu
// ===============================
void mainMenu(vector<Room> &rooms, vector<Customer> &customers, vector<Booking> &bookings) {
    int choice;

    do {
        system("cls");
        cout << "\n====== JNTM HOTEL MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Room\n";
        cout << "2. View Rooms\n";
        cout << "3. Add Customer\n";
        cout << "4. View Customers\n";
        cout << "5. Create Booking\n";
        cout << "6. View Bookings\n";
        cout << "7. Check-Out\n";
        cout << "8. Save Data\n";
        cout << "9. Load Data\n";
        cout << "10. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 10) {
            cout << "Invalid choice! Enter 1-10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1: {
            Room room;
            room.addRoom();
            rooms.push_back(room);
            system("pause");
            break;
        }
        case 2:
            if (rooms.empty()) cout << "No rooms available.\n";
            else for (const auto &room : rooms) room.displayRoom();
            system("pause");
            break;

        case 3: {
            Customer c;
            c.addCustomer(customers);
            customers.push_back(c);
            system("pause");
            break;
        }

        case 4:
            if (customers.empty()) cout << "No customers.\n";
            else for (const auto &c : customers) c.displayCustomer();
            system("pause");
            break;

        case 5: {
            Booking b;
            b.createBooking(rooms, bookings);
            bookings.push_back(b);
            system("pause");
            break;
        }

        case 6:
            if (bookings.empty()) cout << "No bookings.\n";
            else for (const auto &b : bookings) b.displayBooking();
            system("pause");
            break;

        case 7:
            checkOut(bookings, rooms);
            system("pause");
            break;

        case 8:
            saveData(rooms, customers, bookings);
            cout << "Data saved!\n";
            system("pause");
            break;

        case 9:
            loadData(rooms, customers, bookings);
            cout << "Data loaded!\n";
            system("pause");
            break;

        case 10:
            cout << "Exiting system... Goodbye!\n";
            break;
        }

    } while (choice != 10);
}

// ===============================
// Main Function
// ===============================
int main() {
    vector<Room> rooms;
    vector<Customer> customers;
    vector<Booking> bookings;

    mainMenu(rooms, customers, bookings);

    return 0;
}

