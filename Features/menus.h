#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <vector>
#include "../Structures/structures.h"

using namespace std;

void showRegistrationMenu(int &customer_id, int &staff_id, bool &isUserRegistered, bool &isStaff, bool &isCustomer, vector<Customer> &customers, vector<Staff> &staffs);
void showStaffMenu(vector<Customer> &customers);
void showCustomerMenu(vector<Customer> &customers);

#endif
