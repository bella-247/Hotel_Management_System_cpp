#include <iostream>
// #include "sqlite3.h"
// #include <string>
// #include <iomanip>
// using namespace std;



// class Database {
// private:
//     sqlite3* db;
//     char* errorMsg = 0;

//     // Callback function for SELECT queries
//     static int callback(void* data, int argc, char** argv, char** azColName) {
//         for(int i = 0; i < argc; i++) {
//             cout << setw(15) << left << azColName[i] << ": "
//                  << setw(20) << left << (argv[i] ? argv[i] : "NULL");
//         }
//         cout << endl;
//         return 0;
//     }

// public:
//     Database() : db(nullptr) {}

//     bool connect() {
//         int rc = sqlite3_open("hotel.db", &db);
//         if (rc) {
//             cerr << "❌ Failed to connect to database: " << sqlite3_errmsg(db) << endl;
//             return false;
//         }
//         cout << "✅ Connected to SQLite database successfully!" << endl;
//         return true;
//     }

//     bool executeQuery(const string& query) {
//         cout << "\nExecuting query: " << query << endl;
//         int rc = sqlite3_exec(db, query.c_str(), callback, 0, &errorMsg);
//         if (rc != SQLITE_OK) {
//             cerr << "❌ SQL error: " << errorMsg << endl;
//             sqlite3_free(errorMsg);
//             return false;
//         }
//         cout << "✅ Query executed successfully!" << endl;
//         return true;
//     }

//     bool initializeTables() {
//         cout << "\nInitializing database tables..." << endl;

//         // Create RoomTypes table
//         if (!executeQuery(R"(
//             CREATE TABLE IF NOT EXISTS RoomTypes (
//                 room_type_id INTEGER PRIMARY KEY AUTOINCREMENT,
//                 type_name VARCHAR(50) NOT NULL,
//                 price DECIMAL(10, 2) NOT NULL,
//                 num_of_rooms INT NOT NULL,
//                 rooms_range_start INT NOT NULL UNIQUE,
//                 rooms_range_end INT NOT NULL UNIQUE
//             );
//         )")) return false;

//         // Create Rooms table
//         if (!executeQuery(R"(
//             CREATE TABLE IF NOT EXISTS Rooms (
//                 room_id INTEGER PRIMARY KEY AUTOINCREMENT,
//                 room_number INT NOT NULL UNIQUE,
//                 room_type_id INT NOT NULL,
//                 is_available BOOLEAN DEFAULT TRUE,
//                 FOREIGN KEY (room_type_id) REFERENCES RoomTypes(room_type_id)
//             );
//         )")) return false;

//         return true;
//     }

//     bool insertSampleData() {
//         cout << "\nInserting sample data..." << endl;

//         // Insert room types
//         if (!executeQuery(R"(
//             INSERT OR IGNORE INTO RoomTypes (type_name, price, num_of_rooms, rooms_range_start, rooms_range_end)
//             VALUES
//                 ('Single', 100.00, 20, 101, 120),
//                 ('Double', 150.00, 15, 201, 215),
//                 ('Suite', 300.00, 10, 301, 310);
//         )")) return false;

//         // Insert some rooms
//         if (!executeQuery(R"(
//             INSERT OR IGNORE INTO Rooms (room_number, room_type_id, is_available)
//             VALUES
//                 (101, 1, TRUE),
//                 (102, 1, TRUE),
//                 (201, 2, TRUE),
//                 (301, 3, TRUE);
//         )")) return false;

//         return true;
//     }

//     ~Database() {
//         if (db) {
//             sqlite3_close(db);
//             cout << "\nDatabase connection closed." << endl;
//         }
//     }
// };

// int main() {
//     Database db;

//     if (!db.connect()) {
//         return 1;
//     }

//     if (!db.initializeTables()) {
//         return 1;
//     }

//     if (!db.insertSampleData()) {
//         return 1;
//     }

//     // Query room types
//     cout << "\nQuerying room types:" << endl;
//     db.executeQuery("SELECT * FROM RoomTypes;");

//     // Query available rooms
//     cout << "\nQuerying available rooms:" << endl;
//     db.executeQuery(R"(
//         SELECT r.room_number, rt.type_name, rt.price
//         FROM Rooms r
//         JOIN RoomTypes rt ON r.room_type_id = rt.room_type_id
//         WHERE r.is_available = TRUE;
//     )");

//     return 0;
// }
