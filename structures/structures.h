#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>

using namespace std;

// Staff structure
struct Staff {
    int staff_id;
    string name, role, email, password, phone_number;
};

// Room Types structure
struct RoomType {
    int room_type_id;
    string type_name;
    float price;
    int num_of_rooms, rooms_range_start, rooms_range_end;
};

// Room structure
struct Room {
    int room_id;
    int room_number;
    RoomType room_type;
    bool is_available;
};

// Customer structure
struct Customer {
    int customer_id;
    string name, email, password, phone_number;
};

// Booking structure
struct Booking {
    int booking_id, customer_id, room_id;
    string check_in_date, check_out_date;
    float total_price;
};

// Payment structure
struct Payment {
    int payment_id, booking_id;
    float amount;
    string payment_date;
    bool is_paid;
};

// Function declarations for initialization
void initializeStaff(vector<Staff>& staffs);
void initializeRoomTypes(vector<RoomType>& room_types);
void initializeRooms(vector<Room>& rooms, vector<RoomType>& room_types);
void initializeCustomers(vector<Customer>& customers);
void initializeBookings(vector<Booking>& bookings, vector<Customer>& customers, vector<Room>& rooms);
void initializePayments(vector<Payment>& payments, vector<Booking>& bookings);


#endif // STRUCTURES_H
