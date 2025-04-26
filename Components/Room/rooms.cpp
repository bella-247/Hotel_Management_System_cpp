#include "rooms.h"

void showAvailableRooms(){
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