#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int TOTAL_ROOMS = 100, NUM_ROOM_TYPES = 5;
string roomTypes[] = {"Single", "Double", "Family", "Deluxe", "Suite"};
int roomPrices[] = {1500, 2500, 5000, 8000, 10000};
int roomSizes[] = {50, 30, 10, 7, 3};

int roomsReserved[NUM_ROOM_TYPES] = {0};
int prefixRoomSizes[NUM_ROOM_TYPES+1] = {0};
int num_available_rooms = TOTAL_ROOMS;

bool roomAvailability[TOTAL_ROOMS];
string personalInfo[TOTAL_ROOMS][3]; // to store id, name, and phone number

int showMenu();
int bookRoom();
int searchById();
void showRoomAvailability();
void showRoomDetails();
void showUsersList();
void leaveRoom();

//Main function
int main() {
    cout << "\n============================================\n";
    cout << "\033[1;32m" << "         Welcome to Utopia Hotel        " << "\033[0m\n";
    cout << "============================================\n";

    //  these variables are used by the user
    int choice;
    for(int i = 0; i < TOTAL_ROOMS; i++){
        roomAvailability[i] = true;
    }

    // this is creating prefix sum array for the range of rooms in each type
    for(int i = 0; i < NUM_ROOM_TYPES; i++){
        prefixRoomSizes[i+1] = prefixRoomSizes[i] + roomSizes[i];
    }

    while (true) {
        choice = showMenu();
        switch(choice){
        case 1:
            bookRoom();
            break;
        case 2:
            showRoomAvailability();
            break;
        case 3:
            showRoomDetails();
            break;
        case 4:
            showUsersList();
            break;
        case 5:
            if (searchById() == -1){
                cout << "\033[1;31m" << "User not found!" << "\033[0m";
                cout << "\v\v\v";
            }
            break;
        case 6:
            leaveRoom();
            break;
        case 7:
            return 0;
        default:
            cout << "\033[1;31m" << "Invalid choice! Please try again." << "\033[0m\n";
        }
    }

    return 0;
}

int showMenu(){
    int choice;

    menuchoice:
        cout << "\n********** Hotel Menu **********\n";
        cout << "1. Book a Room\n";
        cout << "2. Check Room Availability\n";
        cout << "3. Display Room Details\n";
        cout << "4. Display Users List\n";
        cout << "5. Search users by Id\n";
        cout << "6. Leave room\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || (choice < 1 || choice > 7)){
            cout << "\033[1;31m" << "Invalid choice, please try again" << "\033[0m" << endl;
            cin.clear();
            cin.ignore();
            goto menuchoice;
        }
    return choice;
}

int registerInfo(int roomNumber){
    string name, id, phone;
    cout << "Enter your name: ";
    cin.clear();
    cin.ignore();
    getline(cin, name);

    cout << "Enter your id: ";
    cin.clear();
    getline(cin, id);

    cout << "Enter your phone number: ";
    cin.clear();
    getline(cin, phone);

    personalInfo[roomNumber-1][0] = name;
    personalInfo[roomNumber-1][1] = id;
    personalInfo[roomNumber-1][2] = phone;

    return 0;
}

int bookRoom(){
    int roomNumber;

    roomNumberChoice:
        cout << "\nEnter room number to book (1-" << TOTAL_ROOMS << ") (enter 0 to go back):";
        cin >> roomNumber;

        if (cin.fail() || (roomNumber < 0 || roomNumber > TOTAL_ROOMS)) {
            cout << "\033[1;31m" << "Invalid room number! Please try again." << "\033[0m\n";
            cin.clear();
            cin.ignore();
            goto roomNumberChoice;
        }
        else if (roomNumber == 0){
            return 0;
        }
        else if (!roomAvailability[roomNumber - 1]) {
            cout << "\033[1;31m" << "Sorry, Room " << roomNumber << " is already booked." << "\033[0m\n";
            cout << "Check the available rooms in the previous menu\n";
            goto roomNumberChoice;
        }
        else {
            int status = registerInfo(roomNumber); // roomNumber passed to register the user in that room number information

            if (status == -1){ // if not registered, then the room will not be reserved for that user
                return 0;
            }

            int room_type = 0;
            while(roomNumber-1 >= prefixRoomSizes[room_type+1]){
                room_type++;
            }
            roomsReserved[room_type]++;
            roomAvailability[roomNumber - 1] = false; // Mark the room as booked
            cout << "\033[1;32m" << "Room " << roomNumber << " of the type *" << roomTypes[room_type] << "* has been successfully booked!" << "\033[0m\n";
            num_available_rooms--;
        }

    return roomNumber;
}

void showRoomAvailability(){
    cout << "\nRoom Availability:\n";

    int room, num_reserved_rooms = TOTAL_ROOMS - num_available_rooms;

    if (num_reserved_rooms > num_available_rooms){
        cout << "\nThese are the available rooms\n";
        room = 0;
        for (int type = 0; type < NUM_ROOM_TYPES; type++){
            cout << left << "\t" << roomTypes[type] << setw(5) << " - ";
            if (roomsReserved[type] == roomSizes[type]){
                cout << "All Booked";
            }
            else{
                int available = roomSizes[type] - roomsReserved[type];
                for (; room < prefixRoomSizes[type+1]; room++){
                    if(roomAvailability[room] == true){
                        bool islast = --available > 0;
                        cout << room + 1;
                        if (!islast){
                            cout << ", ";
                        }
                    }
                }
            }
            cout << endl;
        }
    }
    else{ // if there are more free rooms than reserved ones
        cout << "\nThese are the reserved rooms"<<endl;
        room = 0;
        for (int type = 0; type < NUM_ROOM_TYPES; type++){
            cout << roomTypes[type] << " [" << prefixRoomSizes[type] + 1 << "-" << prefixRoomSizes[type + 1] << "]" << right << setw(3) <<" - ";
            if(roomsReserved[type] == 0){
                cout << "All Available";
            }
            else{
                int reserved = roomsReserved[type];
                cout << "reserved = " << reserved << endl;
                for (;room < prefixRoomSizes[type+1]; room++){
                    if(roomAvailability[room] == false){
                        bool islast = --reserved == 0;
                        cout << room + 1;
                        if (!islast){
                            cout << ", ";
                        }
                    }
                }
            }
            cout << endl;
        }
    }
}

void showRoomDetails(){
    cout << "\nRoom Details:\n";
    cout << left << setw(10) << "Types" << setw(15) << "Range" << setw(10) << "Price" << setw(15) << "Status" << "\n";
    cout << "----------------------------------------------------\n";
    for (int i = 0; i < NUM_ROOM_TYPES; i++) {
        string range = "[" + to_string(prefixRoomSizes[i] + 1) + "-" + to_string(prefixRoomSizes[i+1]) + "]";
        cout << left << setw(10) << roomTypes[i] << setw(15) << range << setw(10) << to_string(roomPrices[i]) + " Br";
        if (roomsReserved[i] == roomSizes[i]) {
            cout << "All Booked\n";
        } else {
            cout << roomSizes[i] - roomsReserved[i] << " rooms Available\n";
        }
    }
}

void showUsersList(){
    cout << "\n\nList of People in this Hotel\n\n";

    cout << left << setw(10) << "Room No." << setw(20) << "Name" << setw(10) << "Id" << setw(15) << "Phone Number" << setw(10) << "Room Types";
    cout << setw(10+ 20 + 10 + 15 + 10 + 5) << setfill('-')<<"\n";
    cout << setfill(' ')<<endl;
    int room_type = 0;
    for(int room = 0; room < TOTAL_ROOMS; room++){
        if (room >= prefixRoomSizes[room_type+1]){
            room_type++;
        }

        if(roomAvailability[room] == false){
            string name = personalInfo[room][0], id = personalInfo[room][1], phone = personalInfo[room][2];
            cout << left << setw(10) << room+1 << setw(20) << name << setw(10) << id << setw(15) << phone << setw(10) << roomTypes[room_type] << endl;
        }
    }
    cout << "\033[1;32m" << "\v\v\v" << "\033[0m";
}

int searchById(){
    string id;
    cout<< "Enter the Id: ";
    cin.ignore();
    getline(cin, id);

    int room_type = 0;
    for(int room = 0; room < TOTAL_ROOMS; room++){
        if(roomAvailability[room] == false){
            string roomUserId= personalInfo[room][1];
            if(roomUserId == id){
                cout << "\033[1;32m" << "\nFound the user" << "\033[0m"<< endl;
                cout << "Name: " << personalInfo[room][0]<< endl;
                cout << "Id: " << personalInfo[room][1] << endl;
                cout << "Phone: " << personalInfo[room][2] << endl;
                cout << "Room No.: " << room+1 << endl;
                cout << "Room type: " << roomTypes[room_type] << endl;
                cout <<"\v\v\v";
                return 0;
            }
        }
        if (room+1 >= prefixRoomSizes[room_type+1]){
            room_type++;
        }
    }
    return -1;
}

void leaveRoom(){
    int roomNumber;
    leave_room:
        cout << "\nEnter the room number (0 to go back): ";
        cin >> roomNumber;
        if (cin.fail() || roomNumber < 0){
            cin.clear();
            cin.ignore();
            goto leave_room;
        }

    if (roomNumber != 0){
        roomNumber--; // changing the user input into the index of the room
        if(roomAvailability[roomNumber] == true){
            cout << "\033[1;31m" << "Room is already empty \v\v\v" << "\033[0m";
            goto leave_room;
        }

        string name = personalInfo[roomNumber][0];
        for (int i = 0; i < 3; i++){
            personalInfo[roomNumber][i] = '\0';
        }
        roomAvailability[roomNumber] = true;
        num_available_rooms++;

        int room_type = 0;
        while (roomNumber >= prefixRoomSizes[room_type+1]){
            room_type++;
        }
        roomsReserved[room_type]--;

        cout << "\033[1;32m" << "Thank you for using Our Hotel " << name <<". Goodbye!" << "\033[0m\n";
    }
}
