#include "database.cpp"
using namespace std;

int STAFF_SIZE = 5;
int room_ROOM_TYPES_SIZE = 5;
int ROOMS_SIZE = 100;
int CUSTOMER_SIZE = 5;
int BOOKING_SIZE = 5;
int PAYMENT_SIZE = 5;

struct Staff {
    int staff_id;
    string name, role, email, password, phone_number;
} staff[1000];


// Room Types Data
struct RoomType {
    int room_type_id;
    string type_name;
    float price;
    int num_of_rooms, rooms_range_start, rooms_range_end;
} room_types[5];


// Room Data
struct Room {
    int room_id;
    int room_number;
    RoomType room_type;
    bool is_available;
} rooms[100];


// Customer Data
struct Customer {
    int customer_id;
    string name, email, password, phone_number;
    int room_id;
} customers[10000];


// Booking Data
struct Booking {
    int booking_id;
    Customer customer;
    Room room;
    string check_in_date, check_out_date;
    float total_price;
} bookings[10000];



struct Payment {
    int payment_id;
    Booking booking;
    float amount;
    string payment_date;
    bool is_paid;
} payments[10000];

// Initialization Functions

void initializeStaff() {
    staff[0] = {1, "Michael Smith", "Manager", "michael.smith@example.com", "managerpass", "555-0100"};
    staff[1] = {2, "Sarah Johnson", "Receptionist", "sarah.johnson@example.com", "reception123", "555-0101"};
    staff[2] = {3, "David Williams", "Housekeeper", "david.williams@example.com", "cleaner123", "555-0102"};
    staff[3] = {4, "Emma Brown", "Chef", "emma.brown@example.com", "chefpass", "555-0103"};
    staff[4] = {5, "James Davis", "Security", "james.davis@example.com", "security123", "555-0104"};
}
void initializeRoomTypes() {
    room_types[0] = {1, "Single", 100.0, 50, 1, 50};
    room_types[1] = {2, "Double", 200.0, 30, 51, 80};
    room_types[2] = {3, "Family", 5000.0, 10, 81, 90};
    room_types[3] = {4, "Deluxe", 300.0, 7, 91, 97};
    room_types[4] = {5, "Suite", 400.0, 3, 98, 100};
}
void initializeRooms() {
    int room_type_idx = 0;
    for (int i = 0; i < 100; i++) {
        // Check if the current room number falls within the range of the current room type
        if (i + 1 > room_types[room_type_idx].rooms_range_end) {
            room_type_idx++; // Move to the next room type
        }
        rooms[i] = {i + 1, i + 1, room_types[room_type_idx], true};
    }
}
void initializeCustomers() {
    customers[0] = {1, "John Doe", "johndoe@example.com", "password123", "1234567890", 1};
    customers[1] = {2, "Jane Smith", "janesmith@example.com", "securepassword", "0987654321", 2};
    customers[2] = {3, "Alice Brown", "alicebrown@example.com", "password456", "1122334455", 3};
    customers[3] = {4, "Bob Johnson", "bobjohnson@example.com", "mypassword", "2233445566", 4};
    customers[4] = {5, "Charlie Williams", "charliewilliams@example.com", "charliepass", "3344556677", 5};
}
void initializeBookings() {
    bookings[0] = {1, customers[0], rooms[0], "2025-03-01", "2025-03-05", rooms[0].room_type.price * 4};
    bookings[1] = {2, customers[1], rooms[1], "2025-03-02", "2025-03-06", rooms[1].room_type.price * 4};
    bookings[2] = {3, customers[2], rooms[2], "2025-03-03", "2025-03-07", rooms[2].room_type.price * 4};
    bookings[3] = {4, customers[3], rooms[3], "2025-03-04", "2025-03-08", rooms[3].room_type.price * 4};
    bookings[4] = {5, customers[4], rooms[4], "2025-03-05", "2025-03-09", rooms[4].room_type.price * 4};
}
void initializePayments() {
    payments[0] = {1, bookings[0], bookings[0].total_price, "2025-03-01", true};
    payments[1] = {2, bookings[1], bookings[1].total_price, "2025-03-02", false};
    payments[2] = {3, bookings[2], bookings[2].total_price, "2025-03-03", true};
    payments[3] = {4, bookings[3], bookings[3].total_price, "2025-03-04", true};
    payments[4] = {5, bookings[4], bookings[4].total_price, "2025-03-05", false};
}


void showAvailableRooms(){
    cout << "Available Rooms" << endl;
    bool found = false;

    for(int i = 0; i < ROOMS_SIZE; i++){
        if(rooms[i].is_available){
            cout << "Room " << rooms[i].room_number << endl;
        }
    }
    if(!found){
        cout << "No rooms available" << endl;
    }
}
