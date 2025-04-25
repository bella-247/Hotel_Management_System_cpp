#ifndef HOTEL_DATABASE_H
#define HOTEL_DATABASE_H

#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std;

class HotelDatabase {
private:
    sqlite3* db;

public:
    HotelDatabase();
    ~HotelDatabase();
    
    bool connectToDatabase();
    bool createTables();
    bool executeQuery(const string& query, int (*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
    bool getObject(const string& query, int (*callback)(void*, int, char**, char**), void* data);
    bool getObjects(const string& query, int (*callback)(void*, int, char**, char**), void* data);
    bool insertObject(const string& query, const string& tableName, int (*callback)(void*, int, char**, char**), void* data);
    void exitProgram();
};

// Global instance for database operations
extern HotelDatabase* g_database;

// Global helper functions
bool executeQuery(const string& query, int (*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
bool insertObject(const string& query, const string& tableName, int (*callback)(void*, int, char**, char**), void* data);

#endif // HOTEL_DATABASE_H
