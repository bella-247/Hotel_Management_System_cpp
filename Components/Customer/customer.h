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

bool getCustomerById(int& customer_id, Customer& customer);
void getCustomers();
Customer addCustomer(Customer& customer);
void removeCustomer(int& customer_id);
void showCustomers();
int CustomerCallback(void*, int, char**, char**);

#endif

