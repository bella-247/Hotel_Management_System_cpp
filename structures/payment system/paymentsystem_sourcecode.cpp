#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <ctime>

using namespace std;

struct Payment {
    int payment_id;
    float amount;
    string payment_date, payment_method, name;
    bool is_paid;
};

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return string(buffer);
}

bool isDuplicateID(const vector<Payment>& payments, int id) {
    for (const auto& p : payments) if (p.payment_id == id) return true;
    return false;
}

int generatePaymentID(const vector<Payment>& payments) {
    return payments.empty() ? 1 : payments.back().payment_id + 1;
}

void addPayment(vector<Payment>& payments, int id, float amount, const string& method, bool isPaid, const string& name) {
    payments.push_back({id, amount, getCurrentDate(), method, name, isPaid});
    cout << "Payment added. Payment ID: " << id << endl;
}

void updatePaymentStatus(vector<Payment>& payments, int id, bool status) {
    for (auto& payment : payments) {
        if (payment.payment_id == id) {
            payment.is_paid = status;
            cout << "Payment ID " << id << " status updated to " << (status ? "Paid" : "Unpaid") << endl;
            return;
        }
    }
    cout << "Payment ID not found.\n";
}

void displayPayments(const vector<Payment>& payments) {
    if (payments.empty()) { cout << "No payments recorded.\n"; return; }
    for (const auto& p : payments) {
        cout << "\nPayment ID: " << p.payment_id << "\nAmount: " << p.amount << "\nDate: " << p.payment_date
             << "\nMethod: " << p.payment_method << "\nName: " << p.name << "\nStatus: " << (p.is_paid ? "Paid" : "Unpaid") << endl;
    }
}

void clearInput() { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

void showMenu(vector<Payment>& payments) {
    int choice;
    while (true) {
        cout << "\nPayment System Menu\n1. Add Payment\n2. Update Payment Status\n3. Display Payments\n4. Exit\nEnter choice: ";
        if (!(cin >> choice)) { clearInput(); cout << "Invalid input! Try again.\n"; continue; }

        switch (choice) {
            case 1: {
                float amount; string method, name; int customID = -1, statusInput; bool isPaid;
                cout << "Enter Amount: "; cin >> amount;
                cout << "Enter Payment Method: "; cin >> method;
                cout << "Enter Status (1=Paid, 0=Unpaid): "; cin >> statusInput;
                isPaid = statusInput == 1;
                cout << "Enter User Name: "; cin >> name;
                cout << "Enter your own Payment ID? (1 for Yes, 0 for No): "; cin >> customID;
                if (customID == 1) {
                    cout << "Enter Payment ID: "; cin >> customID;
                    if (isDuplicateID(payments, customID)) { cout << "Payment ID already exists.\n"; break; }
                }
                addPayment(payments, customID == -1 ? generatePaymentID(payments) : customID, amount, method, isPaid, name);
                break;
            }
            case 2: {
                int id, statusInput;
                cout << "Enter Payment ID to Update: "; cin >> id;
                cout << "Enter Status (1=Paid, 0=Unpaid): "; cin >> statusInput;
                updatePaymentStatus(payments, id, statusInput == 1);
                break;
            }
            case 3: displayPayments(payments); break;
            case 4: cout << "Exiting Payment System...\n"; return;
            default: cout << "Invalid choice! Please try again.\n";
        }
    }
}

int main() {
    vector<Payment> payments;
    cout << "🏦 Welcome to the Payment Management System of Utopia Hotel!\n";
    showMenu(payments);
    return 0;
}
