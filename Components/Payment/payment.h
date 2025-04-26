#ifndef PAYMENT_H
#define PAYMENT_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include "../../Structures/structures.h"
#include "../../Database/database.h"
#include "../../Global/globals.h"
using namespace std;

bool getPaymentById(int& payment_id, Payment& payment);
void getPayments();
Payment addPayment(int &booking_id, float &amount, bool &is_paid);
void showPaymentHistory();
void generateInvoice(int &payment_id);
int PaymentCallback(void*, int, char**, char**);

#endif
