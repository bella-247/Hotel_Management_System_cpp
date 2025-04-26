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


void getCustomers(vector<Customer>& customers);
Customer addCustomer(vector<Customer>& customers, string& name, string& email, string& password, string& phone_number);
void removeCustomer(vector<Customer>& customers, int& customer_id);
void showCustomers(const vector<Customer>& customers);
int CustomerCallback(void*, int, char**, char**);

#endif
