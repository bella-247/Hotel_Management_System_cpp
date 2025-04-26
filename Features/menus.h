#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <vector>
#include <string>
#include "../Structures/structures.h"
#include "../Auth/authentication.h"

using namespace std;

void showRegistrationMenu();
void showStaffMenu(void (*startProgram)());
void showCustomerMenu(void (*startProgram)());

#endif
