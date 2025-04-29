#ifndef MENUS_H
#define MENUS_H

#include <iostream>
#include <vector>
#include <string>
#include "../Structures/structures.h"
#include "Messages/messages.h"

#include "../Auth/authentication.h"
#include "../Components/Customer/customer.h"
#include "../Components/Staff/staff.h"
#include "../Components/Payment/payment.h"
#include "../Components/Booking/booking.h"
#include "../Components/Room/room.h"

using namespace std;

void showChoiceError();
void showRegistrationMenu();
void showStaffMenu(void (*startProgram)());
void showCustomerMenu(void (*startProgram)());

void CustomersMenu();
void StaffsMenu();
void RoomsMenu();
void BookingsMenu();
void PaymentsMenu();

#endif
