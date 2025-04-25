#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include "../../Structures/structures.h"
#include "../../Database/database.h"

using namespace std;

Customer createCustomer(vector<Customer> &customers, string &name, string &email, string &password, string &phone_number);
void showCustomers(const vector<Customer> &customers);
int CustomerCallback(void*, int, char**, char**);

#endif