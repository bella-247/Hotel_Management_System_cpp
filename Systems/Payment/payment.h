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

Payment makePayment(vector<Payment> &payments, int &booking_id, float &amount, bool &is_paid);
void showPaymentHistory(vector<Payment> &payments);
int PaymentCallback(void*, int, char**, char**);

#endif
