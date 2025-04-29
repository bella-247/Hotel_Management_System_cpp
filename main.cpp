#include "main.h"

// Retrieve data from database or initialize data if database is empty
void retrieveDatabaseData() {
  getCustomers(); // retrieve the customers that are in the database
  getPayments(); // retrieve the payments that are in the database
  getStaffs(); // retrieve the staffs that are in the database
  getRooms(); // retrieve the rooms that are in the database
  getRoomTypes(); // retrieve the room types that are in the database
  getBookings();  
}

void startProgram() {
  cout << "\n\n============================================";
  showHighlight("Welcome to the Hotel Management System");
  cout << "============================================\n\n";

  while (true) {
    if (current_user.customer_id == -1 && current_user.staff_id == -1) {
      showRegistrationMenu();
    } else {
      if (current_user.isCustomer) {
        showCustomerMenu(startProgram);
      } else {
        showStaffMenu(startProgram);
      }
    }
  }
}

int main() {
  connectToDatabase();
  createTables();
  retrieveDatabaseData(); 

  startProgram();

  return 0;
}
