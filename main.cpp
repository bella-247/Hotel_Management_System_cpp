
#include <iostream>
#include <iomanip>
#include <string>
#include "database/database.h"
#include "structures/structures.h"
#include "Auth/authentication.h"
#include "Features/features.h"
#include "Features/menus.h"

#include <iostream>  // For input/output operations
#include <iomanip>   // For formatting output
#include <string>   // For string operations
//#include <vector>   // For using vectors

#include "payment.h" // for the payment one 


using namespace std;

// --------------------- global variables ----------------- //
int customer_id, staff_id;
bool isUserRegistered = false;
bool isStaff = false, isCustomer = false;


// declare vectors 
vector <Staff> staffs;
vector <RoomType> room_types;
vector <Room> rooms;
vector <Customer> customers;
vector <Booking> bookings;
vector <Payment> payments;

void initializeDatabase();

int main(){
    initializeDatabase();
    main:
        cout << "\n============================================\n";
        cout << "\033[1;32m" << "         Welcome to Utopia Hotel        " << "\033[0m\n";
        cout << "============================================\n";

<<<<<<< HEAD
        while(true){
            if (!isUserRegistered){
                showRegistrationMenu(customer_id, staff_id, isUserRegistered, isStaff, isCustomer, customers, staffs);
=======
// Function prototypes
int showMenu();
void bookRoom();
int searchById();
void showRoomAvailability();
void showRoomDetails();
void showUsersList();
void leaveRoom();

// Main function - The entry point of the program
int main() {
    // Displaying a welcome message
    cout << "\n============================================\n";
    cout << "\033[1;32m" << "         Welcome to Utopia Hotel        " << "\033[0m\n";
    cout << "============================================\n";

    // Initialize all rooms to be available (true = available)
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        roomAvailability[i] = true;
    }

    // Calculate the prefix sum array for room type ranges
    // This helps in determining the range of room numbers for each room type
    for (int i = 0; i < NUM_ROOM_TYPES; i++) {
        prefixRoomSizes[i + 1] = prefixRoomSizes[i] + roomSizes[i];
    }

    // Infinite loop to keep showing the menu until the user chooses to exit
    while (true) {
        int choice = showMenu();  // Display the menu and get the user's choice
        switch (choice) {
        case 1: bookRoom(); break;                     // Book a room
        case 2: showRoomAvailability(); break;         // Check which rooms are available
        case 3: showRoomDetails(); break;              // Display detailed information about all rooms
        case 4: showUsersList(); break;                // Show a list of all users who have booked rooms
        case 5:
            if (searchById() == -1) {  // Search for a user by their ID
                cout << "\033[1;31m" << "User not found!" << "\033[0m\n";

            }
            else{
                if(isCustomer){
                    showCustomerMenu();
                }
                else{
                    showStaffMenu();
                }
            }
        }
    return 0;
}


void initializeDatabase(){
    initializeRoomTypes(room_types);
    initializeRooms(rooms, room_types);
    initializeCustomers(customers);
    initializeBookings(bookings, customers, rooms);
    initializePayments(payments, bookings);
}
makePayment(201, 500.00, "Cash");
makePayment(202, 300.50, "Tele birr");

showPaymentHistory();
