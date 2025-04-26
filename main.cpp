#include "Auth/authentication.h"
#include "Components/Customer/customer.h"
#include "Components/Payment/payment.h"
#include "Database/database.h"
#include "Features/menus.h"
#include "Structures/structures.h"
#include <iomanip>
#include <iostream>
#include <string>


using namespace std;

// --------------------- global variables ----------------- //
bool isUserRegistered = false;
bool isStaff = false, isCustomer = false;
int customer_id, staff_id;

void retrieveDatabaseData() {
  getCustomers(); // retrieve the customers that are in the database
  getPayments();
}

void startProgram() {
  cout << "\n============================================\n";
  cout << "\033[1;32m" << "         Welcome to Utopia Hotel        "
       << "\033[0m\n";
  cout << "============================================\n";

  while (true) {
    if (!isUserRegistered) {
      showRegistrationMenu(staff_id, customer_id, isUserRegistered, isStaff,
                           isCustomer);
    } else {
      if (isCustomer) {
        showCustomerMenu(customer_id, isStaff, isCustomer, isUserRegistered,
                         startProgram);
      } else {
        showStaffMenu(staff_id, isStaff, isCustomer, isUserRegistered,
                      startProgram);
      }
    }
  }
}

int main() {
  connectToDatabase();
  createTables();
  retrieveDatabaseData(); // Retrieve data from database or initialize data if
                          // database

  startProgram();

  return 0;
}
