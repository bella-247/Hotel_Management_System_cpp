#include "main.h"

// Load data from the database into in-memory containers
void retrieveDatabaseData() {
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
}

// Main program loop
void startProgram() {
    cout << "\n\n============================================\n";
    showHighlight("Welcome to the Hotel Management System");
    cout << "============================================\n\n";

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
