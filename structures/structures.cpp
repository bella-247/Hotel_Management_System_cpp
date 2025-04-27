#include "structures.h"
#include <iostream>

using namespace std;

User current_user;
vector<Staff> staffs;
vector<RoomType> roomtypes;
vector<Room> rooms;
vector<Customer> customers;
vector<Booking> bookings;
vector<Payment> payments;

// helper functions 
bool isEmpty(const string &str) {
    for(char c : str) {
        if (!isspace(c)) {
            return false; // Found a non-space character
        }
    }
    return str.empty();
}

void cleanInput(){
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

void showChoiceError() {
    cout << "\033[1;31m" << "Invalid input, please try again." << "\033[0m\n\n";
    cleanInput();
  }