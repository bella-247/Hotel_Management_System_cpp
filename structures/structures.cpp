#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Staffs data
struct Staff {
    int staff_id;
    string name, role, email, password, phone_number;
};


// Room Types Data
struct RoomType {
    int room_type_id;
    string type_name;
    float price;
    int num_of_rooms, rooms_range_start, rooms_range_end;
};


// Room Data
struct Room {
    int room_id;
    int room_number;
    RoomType room_type;
    bool is_available;
};


// Customer Data
struct Customer {
    int customer_id;
    string name, email, password, phone_number;
    int room_id;
};


// Booking Data
struct Booking {
    int booking_id, customer_id, room_id;
    string check_in_date, check_out_date;
    float total_price;
};


// Payment Data
struct Payment {
    int payment_id, booking_id;
    float amount;
    string payment_date;
    bool is_paid;
};

// Initialization Functions

void initializeStaff(Staff &staffs) {
    staffs.push_back({1, "Michael Smith", "Manager", "michael.smith@example.com", "managerpass", "555-0100"});
    staffs.push_back({2, "Sarah Johnson", "Receptionist", "sarah.johnson@example.com", "reception123", "555-0101"});
    staffs.push_back({3, "David Williams", "Housekeeper", "david.williams@example.com", "cleaner123", "555-0102"});
    staffs.push_back({4, "Emma Brown", "Chef", "emma.brown@example.com", "chefpass", "555-0103"});
    staffs.push_back({5, "James Davis", "Security", "james.davis@example.com", "security123", "555-0104"});
}

void initializeRoomTypes(RoomType &room_types) {
    room_types.push_back({1, "Single", 100.0, 50, 1, 50});
    room_types.push_back({2, "Double", 200.0, 30, 51, 80});
    room_types.push_back({3, "Family", 5000.0, 10, 81, 90});
    room_types.push_back({4, "Deluxe", 300.0, 7, 91, 97});
    room_types.push_back({5, "Suite", 400.0, 3, 98, 100});
}

void initializeRooms(Room &rooms) {
    for(RoomType room_type : room_types){
        for(int i = room_type.rooms_range_start; i <= room_type.rooms_range_end; i++){
            rooms.push_back({i, i, room_type, true});
        }
    }
}

void initializeCustomers(Customer &customers) {
    customers.push_back({1, "John Doe", "johndoe@example.com", "password123", "1234567890", 1);
    customers.push_back({2, "Jane Smith", "janesmith@example.com", "securepassword", "0987654321", 2});
    customers.push_back({3, "Alice Brown", "alicebrown@example.com", "password456", "1122334455", 3});
    customers.push_back({4, "Bob Johnson", "bobjohnson@example.com", "mypassword", "2233445566", 4});
    customers.push_back({5, "Charlie Williams", "charliewilliams@example.com", "charliepass", "3344556677", 5});
}
void initializeBookings(Booking &bookings) {
    bookings.push_back({1, customers[0].id, rooms[0].id, "2025-03-01", "2025-03-05", rooms[0].room_type.price * 4});
    bookings.push_back({2, customers[1].id, rooms[1].id, "2025-03-02", "2025-03-06", rooms[1].room_type.price * 4});
    bookings.push_back({3, customers[2].id, rooms[2].id, "2025-03-03", "2025-03-07", rooms[2].room_type.price * 4});
    bookings.push_back({4, customers[3].id, rooms[3].id, "2025-03-04", "2025-03-08", rooms[3].room_type.price * 4});
    bookings.push_back({5, customers[4].id, rooms[4].id, "2025-03-05", "2025-03-09", rooms[4].room_type.price * 4});
}
void initializePayments(Payment &payments) {
    payments.push_back({1, bookings[0].id, bookings[0].total_price, "2025-03-01", true});
    payments.push_back({2, bookings[1].id, bookings[1].total_price, "2025-03-02", false});
    payments.push_back({3, bookings[2].id, bookings[2].total_price, "2025-03-03", true});
    payments.push_back({4, bookings[3].id, bookings[3].total_price, "2025-03-04", true});
    payments.push_back({5, bookings[4].id, bookings[4].total_price, "2025-03-05", false});
}


void showAvailableRooms(Room &rooms){
    cout << "Available Rooms" << endl;
    bool found = false;

    for(Room room : rooms){
        if(room.is_available){
            cout << "Room " << room.room_number << endl;
            found = true;
        }
    }
    if(!found){
        cout << "No available rooms";
    }
}
