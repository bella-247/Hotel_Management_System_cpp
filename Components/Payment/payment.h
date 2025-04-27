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
using namespace std;

bool getPaymentById(int& payment_id, Payment& payment);
void getPayments();
Payment addPayment();
void removePayment();
void showPaymentHistory();
void generateInvoice(int &payment_id);
int PaymentCallback(void*, int, char**, char**);

#endif
