#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Payment {
    int bookingID;
    double amount;
    string paymentMethod;
    bool status;
};

void makePayment(int bookingID, double amount, string method);
void showPaymentHistory();

#endif
