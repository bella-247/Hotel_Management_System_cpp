#include <iostream>
#include <iomanip>
#include <string>
#include "database/database.h"
#include "structures/structures.h"
#include "Auth/authentication.h"
#include "Features/features.h"
#include "Features/menus.h"

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

        while(true){
            if (!isUserRegistered){
                showRegistrationMenu(customer_id, staff_id, isUserRegistered, isStaff, isCustomer, customers, staffs);
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