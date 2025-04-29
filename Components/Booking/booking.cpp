#include "booking.h"

bool validateDate(Date date){   
    bool lower_limits = date.year > 2000 && date.month > 0 && date.date > 0; 
    bool upper_limits = date.year < 3000 && date.month <= 12 && date.date <= 31;
    return lower_limits && upper_limits;
}

bool getBookingById(int &booking_id, Booking &booking) {
    for(Booking &b : bookings) {
        if(b.booking_id == booking_id) {
            booking = b;
            return true;
        }
    }
    return false;
}

void findBooking() {
    Room room;
    Customer customer;
    string email;
    int room_number;

    cout << "Enter customer email: ";
    cleanInput();
    getline(cin, email);

    cout << "Enter the room number: ";
    cin >> room_number;

    if(cin.fail()) {
        showChoiceError();
        return;
    }

    if(!getRoomByRoomNumber(room_number, room)) {
        showWarning("Room not found.");
        return;
    }
    
    if(!getCustomerByEmail(email, customer)) {
        showWarning("Customer not found.");
        return;
    }

    bool found = false;
    for(Booking &b : bookings) {
        if(b.customer_id == customer.customer_id && room.room_number == room_number) {
            showBookingDetails(b.booking_id);
            found = true;
            break;
        }
    }
    
    if(!found) {
        showWarning("Booking not found");
    }
}

Booking addBooking(){
    Customer customer;
    Staff staff;
    Room room;

    string customer_email, staff_email; 
    int room_number;
    Date check_in, check_out;

    cleanInput();
    cout << "Enter customer email: ";
    getline(cin, customer_email);
    cout << "Enter staff email: ";
    getline(cin, staff_email);
    cout << "Enter the room number: ";
    cin >> room_number;

    cout << "Enter check_in year (yyyy) : "; cin >> check_in.year;
    cout << "Enter check_in month (mm) : "; cin >> check_in.month;
    cout << "Enter check_in date (dd) : "; cin >> check_in.date;

    cout << endl << "Enter check_out year (yyyy): "; cin >> check_out.year;
    cout << "Enter check_out month (mm): "; cin >> check_out.month;
    cout << "Enter check_out date (dd): "; cin >> check_out.date;
    
    if(cin.fail()){
        showChoiceError();
        return Booking();
    }

    if(!validateDate(check_in) || !validateDate(check_out)){
        showError("Invalid Date");
        return Booking();
    }

    if(!getCustomerByEmail(customer_email, customer)){
        showWarning("Customer not found.");
        return Booking();
    }

    if(!getStaffByEmail(staff_email, staff)){
        showWarning("Staff not found.");
        return Booking();
    }

    if(!getRoomByRoomNumber(room_number, room)){
        showWarning("Room not found.");
        return Booking();
    }


    try{
        string check_in_date = to_string(check_in.year) + "-" + to_string(check_in.month) + "-" + to_string(check_in.year);
        string check_out_date = to_string(check_out.year) + "-" + to_string(check_out.month) + "-" + to_string(check_out.date);

        string insertQuery = 
        "INSERT INTO Bookings (room_id, customer_id, staff_id, check_in, check_out) VALUES (" + 
        to_string(room.room_id) + "," + to_string(customer.customer_id) + "," + to_string(staff.staff_id) + "," + check_in_date + ");";

        if(!insertObject(insertQuery, "Bookings", BookingCallback, &bookings)){
            throw runtime_error("Failed to add booking");
        }
        showSuccess("Booking succcessfully added");
    }
    catch(const exception& e){
        showError("Error: " + string(e.what()));
        exitProgram();
    }
    return Booking();
}


void showBookingDetails(int &booking_id) {
    Booking booking;

    if(!getBookingById(booking_id, booking)) {
        showWarning("Booking not found.");
        return;
    }

    Customer customer;
    Room room;
    RoomType roomtype;
    Staff staff;

    getCustomerById(booking.customer_id, customer);
    getStaffById(booking.staff_id, staff);
    getRoomById(booking.room_id, room);
    getRoomTypeById(room.room_type_id, roomtype);

    showHighlight("--- Booking Details ---");
    cout << "Booking Id: " << booking.booking_id << endl; 
    cout << "Customer(Id): " << customer.name << " ("<< customer.customer_id << ")" << endl; 
    cout << "Room Number: " << room.room_number << endl;
    cout << "Room Type: " << roomtype.type_name << endl;
    cout << "Staff(Id): " << staff.name << " ("<< staff.staff_id << ")" << endl << endl; 

    cout << "Check In: " << booking.check_in << endl;
    cout << "Check Out: " << booking.check_out << endl;
}


void showCustomerBookings(){
    int customer_id;
    cout << "Enter the customer id: ";
    cin >> customer_id;
    if(cin.fail()){
        showChoiceError();
        return;
    }

    showHighlight("--- Customer Bookings ---" + to_string(customer_id));
    cout << left << setw(10) << "Booking Id" << setw(10) << "Room Number" << setw(10) << "Room Type" << setw(10) << "Check In" << setw(10) << "Check Out" << endl;
    string(100, '-');

    bool found = false;
    for(Booking &b : bookings){
        if(b.customer_id == customer_id){
            Room room;
            RoomType roomtype;
            getRoomById(b.room_id, room);
            getRoomTypeById(room.room_type_id, roomtype);

            cout <<  left << setw(10) << b.booking_id << setw(10) << room.room_number << setw(10) << roomtype.type_name << setw(10) << b.check_in << setw(10) << b.check_out << endl;
            found = true;
        }
    }
    if(!found){
        showWarning("Customer has no previous bookings.");
    }
}

void showRoomBookings(){
    int room_number;
    cout << "Enter the room number: ";
    cin >> room_number;

    if(cin.fail()){
        showChoiceError();
        return;
    }

    Room room;
    if(!getRoomByRoomNumber(room_number, room)){
        showWarning("Room not found.");
        return;
    }

    bool found = false;
    showHighlight("--- Room Bookings ---" + to_string(room_number));
    cout << left << setw(10) << "Booking Id" << setw(10) << "Customer" << setw(10) << "Room Type" << setw(10) << "Check In" << setw(10) << "Check Out" << endl;

    for(Booking &b : bookings){
        if(b.room_id == room.room_id){
            Customer customer;
            RoomType roomtype;
            getCustomerById(b.customer_id, customer);
            getRoomTypeById(room.room_type_id, roomtype);

            cout << left << setw(10) << b.booking_id << setw(10) << customer.customer_id << setw(10) << roomtype.type_name << setw(10) << b.check_in << setw(10) << b.check_out << endl;
            found = true;
        }
    }

    if(!found){
        showWarning("Room has no previous bookings");
    }
}

void showBookings(){
    if(bookings.empty()){
        showWarning("No Bookings yet");
        return;
    }

    showHighlight("--- Bookings List --- ");
    cout << left << setw(10) << "Booking Id" << setw(10) << "Customer" 
        << setw(10) << "Room Number" << setw(10) << "Room Type" << setw(10) 
        << "Staff" << setw(10) << "Check In" << setw(10) << "Check Out" << endl;

    for(Booking &b : bookings){
        Customer customer;
        Room room;
        RoomType roomtype;
        Staff staff;

        getCustomerById(b.customer_id, customer);
        getRoomById(b.room_id, room);
        getRoomTypeById(room.room_type_id, roomtype);
        getStaffById(b.staff_id, staff);

        cout << left << setw(10) << b.booking_id << setw(10) << customer.name << 
            setw(10) << room.room_number << setw(10) << roomtype.type_name <<
            setw(10) << staff.name << setw(10) << b.check_in << setw(10) << b.check_out;
    }
}

// database functions

void getBookings(){
    try{
        string selectQuery = "SELECT * FROM Bookings";
        if(!getObjects(selectQuery, BookingCallback, &bookings)){
            throw runtime_error("Failed to fetch all bookings");
        }
    }
    catch(const exception &e){
        showError("Error: " + string(e.what()));
        exitProgram();
    }
}

int BookingCallback(void *data, int columns, char **values, char **column_names){
    vector<Booking> *bookings = static_cast<vector<Booking> *>(data);

    Booking booking;

    booking.booking_id = values[0] ? atoi(values[0]) : -1;
    booking.customer_id = values[1] ? atoi(values[1]) : -1;
    booking.room_id = values[2]  ? atoi(values[2]) : -1;
    booking.staff_id = values[3] ? atoi(values[3]) : -1;
    booking.check_in = values[4] ? values[4] : "";
    booking.check_out = values[5] ? values[5] : "";

    bookings->push_back(booking);
    return 0;
}
