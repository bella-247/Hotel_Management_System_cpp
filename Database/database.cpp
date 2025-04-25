#include "database.h"
#include "../Structures/structures.h"

HotelDatabase::HotelDatabase() : db(nullptr) {
    if (!connectToDatabase()) {
        cerr << "Failed to connect to the database." << endl;
        exitProgram();
    }
    if (!createTables()) {
        cerr << "Failed to create tables." << endl;
        exitProgram();
    }
}

HotelDatabase::~HotelDatabase() {
    if (db) {
        sqlite3_close(db);
        cout << "Database closed successfully." << endl;
    }
}

bool HotelDatabase::connectToDatabase() {
    int resultCode = sqlite3_open("hotel_database.sqlite3", &db);
    if (resultCode != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        exitProgram();
        return false;
    }
    return true;
}

bool HotelDatabase::createTables() {
    const string query = R"(
        CREATE TABLE IF NOT EXISTS Customers(
            customer_id INTEGER PRIMARY KEY, 
            name TEXT NOT NULL,
            email TEXT NOT NULL, 
            password TEXT NOT NULL,
            phone_number TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );

        CREATE TABLE IF NOT EXISTS Staff(
            staff_id INTEGER PRIMARY KEY, 
            name TEXT NOT NULL, 
            role TEXT NOT NULL,
            phone_number TEXT NOT NULL, 
            email TEXT NOT NULL, 
            password TEXT NOT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );

        CREATE TABLE IF NOT EXISTS RoomTypes(
            room_type_id INTEGER PRIMARY KEY, 
            type_name TEXT NOT NULL,
            price REAL NOT NULL, 
            num_of_rooms INTEGER NOT NULL,
            rooms_range_start INTEGER NOT NULL UNIQUE,
            rooms_range_end INTEGER NOT NULL UNIQUE,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );

        CREATE TABLE IF NOT EXISTS Rooms (
            room_id INTEGER PRIMARY KEY,
            room_number INTEGER NOT NULL UNIQUE,
            room_type_id INTEGER NOT NULL,
            customer_id INTEGER UNIQUE,
            is_available INTEGER DEFAULT 1, 
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (customer_id) REFERENCES Customers(customer_id) ON DELETE SET NULL,
            FOREIGN KEY (room_type_id) REFERENCES RoomTypes(room_type_id) ON DELETE RESTRICT
        );

        CREATE TABLE IF NOT EXISTS Bookings(
            booking_id INTEGER PRIMARY KEY, 
            customer_id INTEGER NOT NULL,
            room_id INTEGER NOT NULL, 
            staff_id INTEGER, 
            check_in DATE NOT NULL,
            check_out DATE NOT NULL,
            booking_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY(customer_id) REFERENCES Customers(customer_id) ON DELETE CASCADE,
            FOREIGN KEY(room_id) REFERENCES Rooms(room_id) ON DELETE CASCADE,
            FOREIGN KEY(staff_id) REFERENCES Staff(staff_id) ON DELETE SET NULL,
            UNIQUE(room_id, check_in) 
        );

        CREATE TABLE IF NOT EXISTS Payments(
            payment_id INTEGER PRIMARY KEY, 
            booking_id INTEGER NOT NULL,
            amount REAL NOT NULL,
            payment_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY(booking_id) REFERENCES Bookings(booking_id) ON DELETE CASCADE
        );
    )";

    return executeQuery(query);
}

bool HotelDatabase::executeQuery(const string& query, int (*callback)(void*, int, char**, char**), void* data) {
    char* err_msg = nullptr;
    int resultCode = sqlite3_exec(db, query.c_str(), callback, data, &err_msg);
    if (resultCode != SQLITE_OK) {
        cerr << "Error executing query: " << err_msg << endl;
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

bool HotelDatabase::getObject(const string& query, int (*callback)(void*, int, char**, char**), void* data) {
    return executeQuery(query, callback, data);
}

bool HotelDatabase::getObjects(const string& query, int (*callback)(void*, int, char**, char**), void* data) {
    return executeQuery(query, callback, data);
}

bool HotelDatabase::insertObject(const string& query, const string& tableName, int (*callback)(void*, int, char**, char**), void* data) {
    if (!executeQuery(query)) return false;

    sqlite3_int64 lastId = sqlite3_last_insert_rowid(db);
    string selectQuery = "SELECT * FROM " + tableName + " WHERE rowid = " + to_string(lastId);
    return executeQuery(selectQuery, callback, data);
}

void HotelDatabase::exitProgram() {
    if (db) {
        sqlite3_close(db);
    }
    exit(EXIT_FAILURE);
}
