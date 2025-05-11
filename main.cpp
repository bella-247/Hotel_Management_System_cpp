#include "main.h"

// Load data from the database into in-memory containers
void retrieveDatabaseData() {
<<<<<<< HEAD
  customers.clear();
  getCustomers(); // retrieve the customers that are in the database
  staffs.clear();
  getStaffs(); // retrieve the staffs that are in the database
  roomtypes.clear();
  getRoomTypes(); // retrieve the room types that are in the database
  rooms.clear();
  getRooms(); // retrieve the rooms that are in the database
  bookings.clear();
  getBookings();   
  payments.clear();
  getPayments(); // retrieve the payments that are in the database
=======
    customers.clear();
    getCustomers();     // Load customer data

    staffs.clear();
    getStaffs();        // Load staff data

    roomtypes.clear();
    getRoomTypes();     // Load room type data

    rooms.clear();
    getRooms();         // Load room data

    bookings.clear();
    getBookings();      // Load booking data

    payments.clear();
    getPayments();      // Load payment data
>>>>>>> ceaa085505993b4979c73b851771bd4bb091fa1c
}

// Main program loop
void startProgram() {
    cout << "\n\n============================================\n";
    showHighlight("Welcome to the Hotel Management System");
    cout << "============================================\n\n";

<<<<<<< HEAD
  while (true) {
    if (current_user.customer_id == -1 && current_user.staff_id == -1) {
        showRegistrationMenu();
    } else {
      if (current_user.isCustomer) {
        showCustomerMenu(startProgram, retrieveDatabaseData);
      } 
      else {
        showStaffMenu(startProgram, retrieveDatabaseData);
      }
=======
    while (true) {
        // No user is logged in
        if (current_user.customer_id == -1 && current_user.staff_id == -1) {
            showRegistrationMenu();
        } else {
            // Show the appropriate menu based on user role
            if (current_user.isCustomer) {
                showCustomerMenu(startProgram, retrieveDatabaseData);
            } else {
                showStaffMenu(startProgram, retrieveDatabaseData);
            }
        }
>>>>>>> ceaa085505993b4979c73b851771bd4bb091fa1c
    }
}

// Entry point of the program
int main() {
    connectToDatabase();       // Initialize DB connection
    createTables();            // Create required tables if they don't exist
    retrieveDatabaseData();    // Load initial data

    startProgram();            // Start the user interface loop

    return 0;
}
