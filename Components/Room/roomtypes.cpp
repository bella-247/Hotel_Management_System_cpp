#include "roomtypes.h"
// Functions to find the required room types

string to_lower(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

// check if room type id exists
bool validateRoomTypeId(int room_type_id) {
    for (RoomType &rt : roomtypes) {
        if (rt.room_type_id == room_type_id) {
            return true;
        }
    }
    return false;
}


bool getRoomTypeById(int room_type_id, RoomType &roomtype) {
    for (RoomType &rt : roomtypes) {
        if (rt.room_type_id == room_type_id) {
            roomtype = rt;
            return true;
        }
    }
    return false;
}


bool getRoomTypeByTypeName(string type_name, RoomType &roomtype) {
    for (RoomType &rt : roomtypes) {
        if (to_lower(rt.type_name) == to_lower(type_name)) {
            roomtype = rt;
            return true;
        }
    }
    return false;
}


RoomType addRoomType() {
    RoomType new_roomtype;

    while(true){
        cout << "Enter Room Type Name: ";
        cleanInput();
        getline(cin, new_roomtype.type_name);

        if(isEmpty(new_roomtype.type_name)){
            showChoiceError();
            continue;
        }

        cout << "Enter Room Type Price: ";
        cin >> new_roomtype.price;
        if (cin.fail()) {
            showChoiceError();
            continue;
        }
        break;
    }



    if(getRoomTypeByTypeName(new_roomtype.type_name, new_roomtype)){
        cout << "Room Type already exists." << endl;
        return RoomType();
    }

    string insertQuery = "INSERT INTO RoomTypes (type_name, price) VALUES ('" + new_roomtype.type_name +
        "', " + to_string(new_roomtype.price) + ");";
    try {
        if (!insertObject(insertQuery, "RoomTypes", RoomTypeCallback, &roomtypes)) {
            throw runtime_error("Failed to add Room Type.");
        }
    }
    catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
        exitProgram();
    }
    cout << "Room Type < " << new_roomtype.type_name << " > created successfully!" << endl;
    return RoomType();
}


void removeRoomType() {
    RoomType roomtype;
    int room_type_id;
    cout << "Enter Room Type ID to remove: ";
    cin >> room_type_id;
    if (cin.fail()) {
        showChoiceError();
        return;
    }

    if(!getRoomTypeById(room_type_id, roomtype)){
        cout << "Room Type not found." << endl;
        return;
    }
    
    bool found = false;
    for(int i = 0; i < roomtypes.size(); i++){
        if(roomtypes[i].room_type_id == room_type_id){
            roomtypes.erase(roomtypes.begin() + i);
            found = true;
            break;
        }
    }

    if(!found){
        cout << "Room Type not found." << endl;
        return;
    }


    string deleteQuery = "DELETE FROM RoomTypes WHERE room_type_id = " + to_string(room_type_id) + ";";
    try {
        if (!executeQuery(deleteQuery)) {
            throw runtime_error("Failed to remove Room Type.");
        }
        
        cout << "Room Type with ID " << room_type_id << " removed successfully!" << endl;
    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
        exitProgram();
    }
}


void showRoomTypeDetails(){
    int room_type_id;
    cout << "Enter the room type id: ";
    cin >> room_type_id;
    if(cin.fail()){
        showChoiceError();
        return;
    }

    RoomType roomtype;
    if(!getRoomTypeById(room_type_id, roomtype)){
        cout << "Room Type not found " << endl;
        return;
    }

    int room_count = 0;
    for(Room &r : rooms){
        if(r.room_type_id == room_type_id){
            room_count++;
        }
    }

    cout << "\n\n -- Room Type Details -- \n\n";

    cout << "Room Type Id: " << roomtype.room_type_id << endl;
    cout << "Room Type Name: " << roomtype.type_name << endl;
    cout << "Room Type Price: " << roomtype.price << endl;
    cout << "Number of rooms: " << room_count << endl;
}

void showRoomTypes() {
    if (roomtypes.empty()) {
        cout << "No room types available.\n";
        return;
    }

    cout << "\n--- Room Types ---\n";
    cout << left << setw(10) << "ID" << setw(20) << "Type Name" << setw(10) << "Price" << endl;
    for (const RoomType &roomtype : roomtypes) {
        cout << left << setw(10) << roomtype.room_type_id << setw(20) << roomtype.type_name
             << setw(10) << roomtype.price << endl;
    }
}


// database functions 

void getRoomTypes() {
    try {
      string query = "SELECT * FROM RoomTypes;";
      if (!getObjects(query, RoomTypeCallback, &roomtypes)) {
        throw runtime_error("Error when retrieving all the room types");
      }
    } catch (const exception &e) {
      cout << "Error: " << e.what() << endl;
      exitProgram();
    }
}

// callback function to handle the result of the query
int RoomTypeCallback(void *data, int columns, char **values,
                     char **column_names) {
    vector<RoomType> *roomtypes = static_cast<vector<RoomType> *>(data);

    RoomType roomtype;
    roomtype.room_type_id = values[0] ? atoi(values[0]) : -1;
    roomtype.type_name = values[1] ? values[1] : "";
    roomtype.price = values[2] ? atof(values[2]) : -1;

    roomtypes->push_back(roomtype);
    return 0;
}