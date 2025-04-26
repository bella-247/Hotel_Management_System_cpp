#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <vector>
#include <string>
#include "../Structures/structures.h"
#include "../Auth/authentication.h"

using namespace std;

void showRegistrationMenu(int &staff_id, int &customer_id, bool &isUserRegistered, bool &isStaff, bool &isCustomer);
void showStaffMenu(int &staff_id, bool &isStaff, bool &isCustomer, bool &isUserRegistered, void (*startProgram)());
void showCustomerMenu(int &customer_id, bool &isStaff, bool &isCustomer, bool &isUserRegistered, void (*startProgram)());

#endif
