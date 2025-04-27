#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>
#include <climits>
#include "../Database/database.h"

using namespace std;

// User structure to store user data
struct User {
    int customer_id = -1, staff_id = -1;
    bool isCustomer, isStaff;
    int room_id = -1;
};

// Staff structure
struct Staff {
    int staff_id = -1;
    string name, role, email, password, phone_number;
};

// Room Types structure
struct RoomType {
    int room_type_id = -1;
    string type_name;
    float price;
};

// Room structure
struct Room {
    int room_id = -1;
    int room_number;
    int room_type_id;
    bool is_available;
};

// Customer structure
struct Customer {
    int customer_id = -1;
    string name, email, password, phone_number;
};

// Booking structure
struct Booking {
    int booking_id = -1, customer_id, room_id;
    string check_in_date, check_out_date;
    float total_price;
};

// Payment structure
struct Payment {
    int payment_id = -1, booking_id;
    float amount;
    string payment_date;
    bool is_paid;
};



bool isEmpty(const string &str);
void cleanInput();
void showChoiceError();


// User state manager 
extern User current_user;

// Global vectors to store data
extern vector<Staff> staffs;
extern vector<RoomType> roomtypes;
extern vector<Room> rooms;
extern vector<Customer> customers;
extern vector<Booking> bookings;
extern vector<Payment> payments;

#endif // STRUCTURES_H

