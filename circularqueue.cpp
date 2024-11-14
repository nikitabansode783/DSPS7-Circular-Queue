#include <iostream>
#include <cstring>
using namespace std;

int f = -1, r = -1, n = 100; 

class Pizza {
    string name, address;
    int quantity;
    float price;

public:
    static const float fixedPrice; // Fixed price for pizza
    void acceptOrder();
    void serveOrder();
    void displayOrder();
    void applyDiscount(int orderNumber);
    void cancelOrder();
    int calculateWaitingTime(int orderCount);
};

const float Pizza::fixedPrice = 100.0; // Setting the fixed price

Pizza p[100];

void Pizza::acceptOrder() {
    if ((f == 0 && r == n - 1) || (f == r + 1)) {
        cout << "Orders are full." << endl;
        return;
    }

    // Temporary storage for the new order
    string tempName, tempAddress;
    int tempQuantity;

    cout << "Enter your Name: ";
    cin >> tempName;
    cout << "Enter your Address: ";
    cin >> tempAddress;
    cout << "Place the Quantity of your order: ";
    cin >> tempQuantity;

    // Calculate waiting time
    int waitingTime = calculateWaitingTime(r - f + 1); 
    cout << "Estimated waiting time: " << waitingTime << " minutes." << endl;

    char choice;
    cout << "Do you want to place the order (y/n)? ";
    cin >> choice;

    if (choice == 'n' || choice == 'N') {
        cout << "Order cancelled." << endl;
        return; // Do not add to the queue
    }

    // If the order is confirmed, update the queue
    r = (r + 1) % n; 
    if (f == -1) {
        f = 0; 
    }

    // Assign values to the queue
    p[r].name = tempName;
    p[r].address = tempAddress;
    p[r].quantity = tempQuantity;
    p[r].price = fixedPrice; // Use fixed price

    applyDiscount(r); 
    cout << "Order placed successfully!" << endl;
}

void Pizza::serveOrder() {
    if (f == -1) {
        cout << "No Orders. Please place the order first." << endl;
        return;
    }

    cout << "Serving Order: " << endl;
    cout << "Name: " << p[f].name << endl;
    cout << "Address: " << p[f].address << endl;
    cout << "Quantity: " << p[f].quantity << endl;
    cout << "Price: " << p[f].price << endl;

    if (f == r) {
        f = -1; 
        r = -1;
    } else {
        f = (f + 1) % n; 
    }
}

void Pizza::displayOrder() {
    if (f == -1) {
        cout << "No Orders to display." << endl;
        return;
    }

    cout << "Current Orders:" << endl;
    int i = f;
    while (i != r) {
        cout << "Name: " << p[i].name << ", Address: " << p[i].address 
             << ", Quantity: " << p[i].quantity 
             << ", Price: " << p[i].price << endl;
        i = (i + 1) % n; 
    }
    
    cout << "Name: " << p[r].name << ", Address: " << p[r].address 
         << ", Quantity: " << p[r].quantity 
         << ", Price: " << p[r].price << endl;
}

void Pizza::applyDiscount(int orderNumber) {
    if (orderNumber == 0) {
        p[orderNumber].price *= 0.5; 
        cout << "50% discount applied to the first order." << endl;
    } else if (orderNumber == 1) {
        p[orderNumber].price *= 0.8; 
        cout << "20% discount applied to the second order." << endl;
    }
}

void Pizza::cancelOrder() {
    if (f == -1) {
        cout << "No Orders to cancel." << endl;
        return;
    }

    cout << "Cancelling order for " << p[f].name << endl;
    cout << "Refund Amount: " << p[f].price * 0.5 << endl; // 50% refund

    // Move front to next order
    if (f == r) {
        f = -1; // Queue becomes empty
        r = -1;
    } else {
        f = (f + 1) % n; // Circular increment
    }
}

int Pizza::calculateWaitingTime(int orderCount) {
    return orderCount * 10; // Each order takes 10 minutes
}

int main() {
    Pizza pizzaOrder;
    int choice;
    
    while (true) {
        cout << "1. Accept Order" << endl;
        cout << "2. Serve Order" << endl;
        cout << "3. Display Orders" << endl;
        cout << "4. Cancel Order" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                pizzaOrder.acceptOrder();
                break;
            case 2:
                pizzaOrder.serveOrder();
                break;
            case 3:
                pizzaOrder.displayOrder();
                break;
            case 4:
                pizzaOrder.cancelOrder();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
