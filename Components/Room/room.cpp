#include "room.h"

// Helper Functions
// Functions to find the required rooms
bool getRoomById(int room_id, Room &room) {
  for (Room &r : rooms) {
    if (r.room_id == room_id) {
      room = r;
      return true;
    }
  }
  return false;
}

bool getRoomByRoomNumber(int room_id, Room &room) {
  for (Room &r : rooms) {
    if (r.room_number == room_id) {
      room = r;
      return true;
    }
  }
  return false;
}

// check if room number exists
bool validateRoomNumber(int &room_number) {
  for (Room &r : rooms) {
    if (r.room_number == room_number) {
      return true;
    }
  }
  return false;
}

// to add a room
Room addRoom() {
    Room new_room;
  int room_number;
  int room_type_id;

  while (true) {
    // enter the room number of the new room 
    cout << "Enter Room Number: ";
    cin >> room_number;

    if (cin.fail()) {
        showChoiceError();
        continue;
    }

    if(getRoomByRoomNumber(room_number, new_room)){
        cout << "Room number already exists." << endl;
        return Room();
    }

    // display all the available room types
    cout << "Available Room types " << endl;
    cout << setw(10) << "ID " << setw(10) << "Room Type name" << endl;
    for(RoomType &rt : roomtypes){
        cout << setw(10) << rt.room_type_id << setw(10) << rt.type_name << endl; 
    }

    cout << "Enter the room type id: ";
    cin >> room_type_id;

    // check if the room type id is valid (exists)
    if (!validateRoomTypeId(room_type_id)) {
        cout << "Invalid room type id. Please try again." << endl;
        continue;
    }

    break;
  }

  string insertQuery = "INSERT INTO Rooms (room_number, room_type_id) VALUES ('" + to_string(room_number) +
      "', " + to_string(room_type_id) + ");";

  if (insertObject(insertQuery, "Rooms", RoomCallback, &rooms)) {
    cout << "Room added successfully.\n";
    return rooms.back();
  }
  else {
    cout << "Failed to add Room.\n";
    return Room();
  }
}

// to remove a room
void removeRoom() {
  int room_number;
  cout << "Enter Room Number to remove: ";
  cin >> room_number;

  if(cin.fail()) {
    showChoiceError();
    return;
  }

  bool found = false;
  for (int i = 0; i < rooms.size(); i++) {
    if (rooms[i].room_number == room_number) {
      rooms.erase(rooms.begin() + i);
      found = true;
      break;
    }
  }
  if(!found){
    cout << "Room Not Found" << endl;
    return;
  }

  try{
      string deleteQuery = "DELETE FROM Rooms WHERE room_number = '" + to_string(room_number) + "';";
      if (!deleteObject(deleteQuery)) {
        throw runtime_error("Failed to remove the room!");
    } 
    cout << "Room removed successfully.\n";
  }
  catch (const exception &e) {
      cout << "Error: " << e.what() << endl;
      exitProgram();
  }
}


void bookRoom() {
    if(current_user.room_id != -1){
        cout << "You already booked a room." << endl;
        return;
    }

    int room_number;
    cout << "Enter the room number you want to book: ";
    cin >> room_number;

    if(cin.fail()) {
        showChoiceError();
        return;
    }

    Room room;
    if (!getRoomByRoomNumber(room_number, room)) {
        cout << "Room not found." << endl;
        return;
    }

    if (!room.is_available) {
        cout << "Room is not available." << endl;
        return;
    }

    // update the room availability in the database
    string updateQuery = "UPDATE Rooms SET is_available = 0 WHERE room_number = '" + to_string(room_number) + "';";
    
    try{
        if (!updateObject(updateQuery)) {
            throw runtime_error("Failed to update room availability.");
        }
        
        current_user.room_id = room.room_id; // set the current user's room id
        cout << "Room booked successfully.\n";
    }
    catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
        exitProgram();
    }
}

// show available rooms
void showAvailableRooms() {
    
    cout << "\n\n--- Available Rooms ---\n\n";
    cout << setw(10) << "Room ID" << setw(10) << "Room Number" << setw(10)
    << "Room Type" << endl;
    
  for (const Room &room : rooms) {
      if (!room.is_available) {
          continue;
        }
    
    RoomType roomtype;
    getRoomTypeById(room.room_type_id, roomtype);
    cout << "Room ID: " << room.room_id << "  Room Number: " << room.room_number << " Room Type: " << roomtype.type_name << endl;
  }
}

// show the properties of a room
void showRoomDetails(int room_number) {
  Room room;
  if (!getRoomByRoomNumber(room_number, room)) {
    cout << "Room not found." << endl;
    return;
  }

  RoomType roomtype;
  getRoomTypeById(room.room_type_id, roomtype);

  cout << "\n\n--- Room Details ---\n\n";
  cout << "\tRoom ID: " << room.room_id << endl;
  cout << "\tRoom Number: " << room.room_number << endl;
  cout << "\tRoom Type: " << roomtype.type_name << endl;
  cout << "\tAvailability: "
       << (room.is_available ? "Available" : "Not Available") << endl;
}


void leaveRoom() {
    if(current_user.room_id == -1){
        cout << "You didn't book any room yet." << endl;
        return;
    }

    int room_id = current_user.room_id;
    try{
        string updateQuery = "UPDATE Rooms SET is_available = 1 WHERE room_id = " + to_string(room_id) + ";";
        
        if (!updateObject(updateQuery)) {
        cout << "Failed to update room availability.\n";
        throw runtime_error("Failed to update room availability in database");
        }
    }
    catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
        exitProgram();
    }
    current_user.room_id = -1; // reset the room id of the current user
    cout << "You left the room successfully.\n";
}





// Show all rooms function
void showRooms() {
    string query = "SELECT * FROM Rooms;";
  
    try{
        if (!getObjects(query, RoomCallback, &rooms)) {
          throw runtime_error("Failed to fetch rooms from database");
        }
    }
      catch (const exception &e) {
          cout << "Error: " << e.what() << endl;
          exitProgram();
      }
  
    cout << "\n--- All Rooms ---\n";
    cout << left << setw(10) << "Room ID" << setw(10) << "Room Number" << setw(10)
         << "Room Type" << setw(15) << "Availability" << endl;
    for (const Room &room : rooms) {
      RoomType roomtype;
      getRoomTypeById(room.room_type_id, roomtype);
  
      cout << left << setw(10) << room.room_id << setw(10) << room.room_number
           << setw(10) << roomtype.type_name << setw(15) << (room.is_available ? "Available" : "Not Available") << endl;
    }
  }


// database functions

void getRooms() {
  try {
    string query = "SELECT * FROM Rooms;";
    if (!getObjects(query, RoomCallback, &rooms)) {
      throw runtime_error("Error when retrieving all the rooms");
    }
    cout << "Rooms initialized successfully." << endl;
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exitProgram();
  }
}

// callbacks
int RoomCallback(void *data, int columns, char **values, char **column_names) {
  vector<Room> *rooms = static_cast<vector<Room> *>(data);
  Room room;

  room.room_id = atoi(values[0]);
  room.room_number = atoi(values[1]);
  room.room_type_id = atoi(values[2]);
  room.is_available = atoi(values[3]) == 1 ? true : false;

  rooms->push_back(room);
  return 0;
}
