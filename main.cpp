#include "Auth/authentication.h"
#include "Database/database.h"
#include "Features/features.h"
#include "Features/menus.h"
#include "Structures/structures.h"
#include "Systems/Customer/customer.h"
#include "Systems/Payment/payment.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// --------------------- global variables ----------------- //
int customer_id, staff_id;
bool isUserRegistered = false;
bool isStaff = false, isCustomer = false;

// declare vectors
vector<Staff> staffs;
vector<RoomType> roomtypes;
vector<Room> rooms;
vector<Customer> customers;
vector<Booking> bookings;
vector<Payment> payments;

void retrieveDatabaseData() {
  getCustomers(customers);// show the customers that are in the database 
  getPayments(payments);
}


void startProgram(){
    cout << "\n============================================\n";
    cout << "\033[1;32m" << "         Welcome to Utopia Hotel        "
        << "\033[0m\n";
    cout << "============================================\n";

    while (true) {
        if (!isUserRegistered) {
        showRegistrationMenu(staff_id, customer_id, isUserRegistered, isStaff,
                            isCustomer, customers, staffs);
        } else {
            if (isCustomer) {
                showCustomerMenu(customer_id, isStaff, isCustomer, isUserRegistered, 
                               customers, rooms, roomtypes, startProgram);
            } else {
                showStaffMenu(staff_id, isStaff, isCustomer, isUserRegistered, 
                            staffs, customers, rooms, roomtypes, bookings, 
                            payments, startProgram);
            }
        }
    }
}

int main() {
    connectToDatabase();
    createTables();
    retrieveDatabaseData(); // Retrieve data from database or initialize data if database

    startProgram();

  return 0;
}
