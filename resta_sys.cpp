#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_CUSTOMERS = 100;
const int MAX_MENU_ITEMS = 50;
const int MAX_ORDERS = 200;

struct MenuItem {
    int id;
    string name;
    float price;
};

struct Customer {
    int tableNo;
    string name;
    string phone;
    float billAmount;
    string orders[MAX_ORDERS];
    float orderPrices[MAX_ORDERS]; 
    int orderCount;
    bool reserved;
    int loyaltyPoints; 
};

class Restaurant {
private:
    Customer customers[MAX_CUSTOMERS];
    int customerCount;
    MenuItem menu[MAX_MENU_ITEMS];
    int menuCount;

public:
    Restaurant();
    void addCustomer();
    void displayCustomers();
    void displayMenu();
    void orderFood();
    void displayBillingDetails();
    void modifyCustomerDetails();
    void splitBill();
    void makeReservation();
    void cancelReservation();
    void addLoyaltyPoints(int tableNo, float amount); 
    void displayLoyaltyPoints(int tableNo); 
    float applyDiscount(float amount, int points);
};

Restaurant::Restaurant() : customerCount(0), menuCount(0) {
    menu[menuCount++] = {1, "Idli", 30.0};
    menu[menuCount++] = {2, "Dosa", 50.0};
    menu[menuCount++] = {3, "Vada", 20.0};
    menu[menuCount++] = {4, "Uttapam", 60.0};
    menu[menuCount++] = {5, "Sambar", 25.0};
    menu[menuCount++] = {6, "Rasam", 25.0};
    menu[menuCount++] = {7, "Pongal", 40.0};
    menu[menuCount++] = {8, "Bisi Bele Bath", 70.0};
    menu[menuCount++] = {9, "Upma", 35.0};
    menu[menuCount++] = {10, "Masala Dosa", 70.0};
    menu[menuCount++] = {11, "Filter Coffee", 15.0};
    menu[menuCount++] = {12, "Spaghetti Carbonara", 120.0};
    menu[menuCount++] = {13, "Margherita Pizza", 150.0};
    menu[menuCount++] = {14, "Caesar Salad", 80.0};
    menu[menuCount++] = {15, "Grilled Chicken", 200.0};
    menu[menuCount++] = {16, "Beef Steak", 300.0};
    menu[menuCount++] = {17, "French Fries", 50.0};
    menu[menuCount++] = {18, "Cheeseburger", 100.0};
    menu[menuCount++] = {19, "Tiramisu", 70.0};
    menu[menuCount++] = {20, "Apple Pie", 60.0};
    menu[menuCount++] = {21, "Pancakes", 90.0};
    menu[menuCount++] = {22, "Milkshake", 40.0};
    menu[menuCount++] = {23, "Chicken Nuggets", 80.0};
    menu[menuCount++] = {24, "Fish and Chips", 140.0};
}

void Restaurant::addCustomer() {
    if (customerCount < MAX_CUSTOMERS) {
        Customer& c = customers[customerCount];
        cout << "Enter table number: ";
        cin >> c.tableNo;
        cin.ignore();

        cout << "Enter name: ";
        getline(cin, c.name);

        cout << "Enter phone number : ";
        cin >> c.phone;

        c.billAmount = 0.0;
        c.orderCount = 0;
        c.reserved = false;
        c.loyaltyPoints = 0;

        ++customerCount;
        cout << "Customer added successfully!\n";
    } else {
        cout << "Customer limit reached!\n";
    }
}

void Restaurant::displayCustomers() {
    if (customerCount == 0) {
        cout << "No customers to display.\n";
        return;
    }

    cout << left << setw(10) << "Table No" << setw(20) << "Name" << setw(15) << "Phone" << setw(10) << "Bill" << setw(10) << "Reserved" << setw(15) << "Loyalty Points" << "\n";
    for (int i = 0; i < customerCount; ++i) {
        const Customer& c = customers[i];
        cout << left << setw(10) << c.tableNo << setw(20) << c.name << setw(15) << c.phone << setw(10) << c.billAmount << setw(10) << (c.reserved ? "Yes" : "No") << setw(15) << c.loyaltyPoints << "\n";
    }
}

void Restaurant::displayMenu() {
    if (menuCount == 0) {
        cout << "No menu items to display.\n";
        return;
    }

    cout << left << setw(5) << "ID" << setw(25) << "Name" << setw(10) << "Price" << "\n";
    for (int i = 0; i < menuCount; ++i) {
        const MenuItem& item = menu[i];
        cout << left << setw(5) << item.id << setw(25) << item.name << setw(10) << item.price << "\n";
    }
}

void Restaurant::orderFood() {
    int tableNo;
    cout << "Enter table number to order food: ";
    cin >> tableNo;

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].tableNo == tableNo) {
            Customer& c = customers[i];

            cout << "\nFood Menu:\n";
            displayMenu();

            while (true) {
                int menuId;
                cout << "Enter menu item ID (0 to stop ordering): ";
                cin >> menuId;

                if (menuId == 0) break;

                bool itemFound = false;
                for (int j = 0; j < menuCount; ++j) {
                    if (menu[j].id == menuId) {
                        if (c.orderCount < MAX_ORDERS) {
                            c.orders[c.orderCount] = menu[j].name;
                            c.orderPrices[c.orderCount] = menu[j].price;
                            c.billAmount += menu[j].price;
                            ++c.orderCount;
                            addLoyaltyPoints(tableNo, menu[j].price);
                            cout << "Food ordered successfully!\n";
                            itemFound = true;
                            break;
                        } else {
                            cout << "Maximum orders reached!\n";
                            return;
                        }
                    }
                }
                if (!itemFound) {
                    cout << "Menu item not found.\n";
                }
            }
            return;
        }
    }
    cout << "Customer with table number " << tableNo << " not found.\n";
}

void Restaurant::displayBillingDetails() {
    int tableNo;
    cout << "Enter table number to display billing details: ";
    cin >> tableNo;

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].tableNo == tableNo) {
            Customer& c = customers[i];
            cout << "Name: " << c.name << "\n";
            cout << "Phone: " << c.phone << "\n";

            float finalBill = applyDiscount(c.billAmount, c.loyaltyPoints);

            cout << "Bill amount after discount: $" << finalBill << "\n";

            if (c.orderCount > 0) {
                cout << "Food Orders:\n";
                for (int j = 0; j < c.orderCount; ++j) {
                    cout << setw(20) << c.orders[j] << " $" << c.orderPrices[j] << "\n";
                }
            }
            return;
        }
    }
    cout << "Customer with table number " << tableNo << " not found.\n";
}

void Restaurant::modifyCustomerDetails() {
    int tableNo;
    cout << "Enter table number to modify customer details: ";
    cin >> tableNo;

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].tableNo == tableNo) {
            Customer& c = customers[i];
            cout << "Current Details:\n";
            cout << "Name: " << c.name << "\n";
            cout << "Phone: " << c.phone << "\n";

            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, c.name);

            cout << "Enter new phone number : ";
            cin >> c.phone;

            cout << "Customer details modified successfully!\n";
            return;
        }
    }
    cout << "Customer with table number " << tableNo << " not found.\n";
}

void Restaurant::splitBill() {
    int tableNo;
    cout << "Enter table number to split the bill: ";
    cin >> tableNo;

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].tableNo == tableNo) {
            Customer& c = customers[i];
            int numPayers;
            cout << "Enter the number of people splitting the bill: ";
            cin >> numPayers;

            if (numPayers <= 0) {
                cout << "Invalid number of payers.\n";
                return;
            }

            // Apply discount
            float splitAmount = applyDiscount(c.billAmount, c.loyaltyPoints) / numPayers;
            cout << "Bill split successfully. Each person owes: $" << splitAmount << "\n";
            return;
        }
    }
    cout << "Customer with table number " << tableNo << " not found.\n";
}

void Restaurant::makeReservation() {
    int tableNo;
    cout << "Enter table number for reservation: ";
    cin >> tableNo;

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].tableNo == tableNo) {
            if (customers[i].reserved) {
                cout << "Table already reserved.\n";
                return;
            }

            customers[i].reserved = true;
            cout << "Table " << tableNo << " reserved successfully!\n";
            return;
        }
    }
    cout << "Customer with table number " << tableNo << " not found.\n";
}

void Restaurant::cancelReservation() {
    int tableNo;
    cout << "Enter table number to cancel reservation: ";
    cin >> tableNo;

    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].tableNo == tableNo) {
            if (!customers[i].reserved) {
                cout << "Table is not reserved.\n";
                return;
            }

            customers[i].reserved = false;
            cout << "Reservation for table " << tableNo << " canceled successfully!\n";
            return;
        }
    }
    cout << "Customer with table number " << tableNo << " not found.\n";
}

void Restaurant::addLoyaltyPoints(int tableNo, float amount) {
    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].tableNo == tableNo) {
            customers[i].loyaltyPoints += static_cast<int>(amount / 10);
            cout << "Loyalty points added successfully!\n";
            return;
        }
    }
    cout << "Customer with table number " << tableNo << " not found.\n";
}

void Restaurant::displayLoyaltyPoints(int tableNo) {
    for (int i = 0; i < customerCount; ++i) {
        if (customers[i].tableNo == tableNo) {
            cout << "Customer " << customers[i].name << " has " << customers[i].loyaltyPoints << " loyalty points.\n";
            return;
        }
    }
    cout << "Customer with table number " << tableNo << " not found.\n";
}

float Restaurant::applyDiscount(float amount, int points) {
    float discount = 0.0;

    if (points > 100) {
        discount = 0.60;
    } else if (points > 50) {
        discount = 0.35;
    }

    return amount * (1 - discount);
}

void displayMainMenu() {
    cout << "\nRestaurant Management System\n";
    cout << "1. Add Customer\n";
    cout << "2. Display Customers\n";
    cout << "3. Order Food\n";
    cout << "4. Display Bill\n";
    cout << "5. Make Reservation\n";
    cout << "6. Cancel Reservation\n";
    cout << "7. Modify Customer Details\n";
    cout << "8. Split Bill\n";
    cout << "9. Display Loyalty Points\n"; 
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Restaurant restaurant;
    int choice;

    while (true) {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            restaurant.addCustomer();
            break;
        case 2:
            restaurant.displayCustomers();
            break;
        case 3:
            restaurant.orderFood();
            break;
        case 4:
            restaurant.displayBillingDetails();
            break;
        case 5:
            restaurant.makeReservation();
            break;
        case 6:
            restaurant.cancelReservation();
            break;
        case 7:
            restaurant.modifyCustomerDetails();
            break;
        case 8:
            restaurant.splitBill();
            break;
        case 9:
            int tableNo;
            cout << "Enter table number to display loyalty points: ";
            cin >> tableNo;
            restaurant.displayLoyaltyPoints(tableNo);
            break;
        case 10:
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
