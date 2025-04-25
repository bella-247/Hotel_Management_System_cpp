#include <iostream>
#include <iomanip>
#include <string>
#include "Database/database.h"
#include "Structures/structures.h"
#include "Auth/authentication.h"
#include "Features/features.h"
#include "Features/menus.h"
#include "Systems/Payment/payment.h"

using namespace std;

// --------------------- global variables ----------------- //
int customer_id, staff_id;
bool isUserRegistered = false;
bool isStaff = false, isCustomer = false;

// declare vectors 
vector<Staff> staffs;
vector<RoomType> room_types;
vector<Room> rooms;
vector<Customer> customers;
vector<Booking> bookings;
vector<Payment> payments;

// Global database instance
HotelDatabase* g_database = nullptr;

void initializeDatabase();

int main() {
    g_database = new HotelDatabase();
    
    main:
        cout << "\n============================================\n";
        cout << "\033[1;32m" << "         Welcome to Utopia Hotel        " << "\033[0m\n";
        cout << "============================================\n";

        while(true) {
            if (!isUserRegistered) {
                showRegistrationMenu(customer_id, staff_id, isUserRegistered, isStaff, isCustomer, customers, staffs);
            }
            else {
                if(isCustomer) {
                    showCustomerMenu(customers);  // Pass customers vector
                }
                else {
                    showStaffMenu(customers);     // Pass customers vector
                }
            }
        }

    delete g_database;
    return 0;
}

void initializeDatabase() {
    initializeRoomTypes(room_types);
    initializeRooms(rooms, room_types);
    initializeCustomers(customers);
    initializeBookings(bookings, customers, rooms);
    initializePayments(payments, bookings);
}
