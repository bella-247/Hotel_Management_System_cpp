#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <vector>
#include <string>
#include "../Structures/structures.h"
#include "../Auth/authentication.h"

using namespace std;

void showRegistrationMenu(int &staff_id, int &customer_id, bool &isStaff, bool &isCustomer, bool &isUserRegistered, vector<Customer> &customers, vector<Staff> &staffs);
void showStaffMenu(int &staff_id, bool &isStaff, bool &isCustomer, bool &isUserRegistered, vector<Staff> &staffs, vector<Customer> &customers, vector<Room> &rooms, vector<RoomType> &roomtypes, vector<Booking> &bookings, vector<Payment> &payments, void (*startProgram)());
void showCustomerMenu(int &customer_id, bool &isStaff, bool &isCustomer, bool &isUserRegistered, vector<Customer> &customers, vector<Room> &rooms, vector<RoomType> &roomtypes, void (*startProgram)());

#endif
