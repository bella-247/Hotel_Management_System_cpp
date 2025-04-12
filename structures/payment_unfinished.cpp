#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Payment {
    int payment_id;
    float amount;
    string payment_date; // formatted as YYYY-MM-DD
    bool is_paid;
    string payment_method; // Example: "Tele Birr ","Bank" etc.
};
void addPayment(vector<Payment>& payments, int id, float amount, string date, string method) {
    Payment newPayment = {id, amount, date, false, method};
    payments.push_back(newPayment);
    cout << "Payment added successfully!" << endl;
}
void updatePaymentStatus(vector<Payment>& payments, int id, bool status) {
    for (auto& payment : payments) {
        if (payment.payment_id == id) {
            payment.is_paid = status;
            cout << "Payment ID " << id << " status updated to " 
                 << (status ? "Paid" : "Unpaid") << endl;
            return;
        }
    }
    cout << "Payment ID not found!" << endl;
}
void displayPayments(const vector<Payment>& payments) {
    cout << "\n--- Payment Records ---\n";
    for (const auto& payment : payments) {
        cout << "Payment ID: " << payment.payment_id
             << ", Amount: " << payment.amount
             << ", Date: " << payment.payment_date
             << ", Method: " << payment.payment_method
             << ", Status: " << (payment.is_paid ? "Paid" : "Unpaid") << endl;
    }
}
void showMenu(vector<Payment>& payments) {
    int choice, id;
    float amount;
    string date, method;
    bool status;

    while (true) {
        cout << "\n--- Payment System Menu ---\n";
        cout << "1. Add Payment\n";
        cout << "2. Update Payment Status\n";
        cout << "3. Display Payments\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Payment ID: ";
                cin >> id;
                cout << "Enter Amount: ";
                cin >> amount;
                cout << "Enter Payment Date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter Payment Method: ";
                cin >> method;
                addPayment(payments, id, amount, date, method);
                break;

            case 2:
                cout << "Enter Payment ID to Update: ";
                cin >> id;
                cout << "Enter Status (1 for Paid, 0 for Unpaid): ";
                cin >> status;
                updatePaymentStatus(payments, id, status);
                break;

            case 3:
                displayPayments(payments);
                break;

            case 4:
                cout << "Exiting Payment System..." << endl;
                return;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}
int main() {
    vector<Payment> payments;
    cout << "Welcome to the Payment Management System!" << endl;
    showMenu(payments);
    return 0;
}