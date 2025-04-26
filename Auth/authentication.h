#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "../Components/Customer/customer.h"
#include "../Components/Staff/staff.h"
#include "../Structures/structures.h"
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <stdexcept>
using namespace std;

bool isEmpty(const string &str);
void cleanInput();
bool getData(Customer &customer);
bool getData(Staff &staff);
bool isAlreadyRegistered(Customer &customer);
bool isAlreadyRegistered(Staff &staff);
bool signUp();
bool logIn();
void logOut(void (*startProgram)());

#endif
