#include "../include/payment.h"

using namespace std;

vector<Payment> payments;

void makePayment(int bookingID, double amount, string method) {
    Payment p = {bookingID, amount, method, true};
    payments.push_back(p);
    cout << "Payment of $" << amount << " received for Booking ID " << bookingID << " via " << method << ".\n";
}

void showPaymentHistory() {
    cout << "\n--- Payment History ---\n";
    for (const auto& p : payments) {
        cout << "Booking ID: " << p.bookingID
             << ", Amount: $" << p.amount
             << ", Method: " << p.paymentMethod
             << ", Status: " << (p.status ? "Completed" : "Pending") << '\n';
    }
}
