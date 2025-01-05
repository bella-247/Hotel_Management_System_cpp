#include <iostream>  // For input/output operations
#include <iomanip>   // For formatting output
#include <cstring>   // For string operations (not heavily used here)

using namespace std;

// Constants to define the total number of rooms and room types in the hotel
const int TOTAL_ROOMS = 100;      // Total number of rooms in the hotel
const int NUM_ROOM_TYPES = 5;     // Number of different room types

// Arrays to hold information about room types
string roomTypes[] = {"Single", "Double", "Family", "Deluxe", "Suite"}; // Names of room types
int roomPrices[] = {1500, 2500, 5000, 8000, 10000};                     // Prices for each room type
int roomSizes[] = {50, 30, 10, 7, 3};                                  // Number of rooms available for each type

// Arrays to keep track of room availability and reservations
int roomsReserved[NUM_ROOM_TYPES] = {0};          // Number of rooms reserved for each type
int prefixRoomSizes[NUM_ROOM_TYPES + 1] = {0};    // Used to calculate the range of room numbers for each type
int num_available_rooms = TOTAL_ROOMS;            // Total number of available rooms in the hotel

// Array to indicate if a room is available (true means available, false means booked)
bool roomAvailability[TOTAL_ROOMS];

// Array to store user information for each room: Name, ID, and Phone
string personalInfo[TOTAL_ROOMS][3];

// Function prototypes (declaring functions before their implementation for clarity)
int showMenu();
void bookRoom();
int searchById();
void showRoomAvailability();
void showRoomDetails();
void showUsersList();
void leaveRoom();

// Main function - The entry point of the program
int main() {
    // Displaying a welcome message
    cout << "\n============================================\n";
    cout << "\033[1;32m" << "         Welcome to Utopia Hotel        " << "\033[0m\n";
    cout << "============================================\n";

    // Initialize all rooms to be available (true = available)
    for (int i = 0; i < TOTAL_ROOMS; i++) {
        roomAvailability[i] = true;
    }

    // Calculate the prefix sum array for room type ranges
    // This helps in determining the range of room numbers for each room type
    for (int i = 0; i < NUM_ROOM_TYPES; i++) {
        prefixRoomSizes[i + 1] = prefixRoomSizes[i] + roomSizes[i];
    }

    // Infinite loop to keep showing the menu until the user chooses to exit
    while (true) {
        int choice = showMenu();  // Display the menu and get the user's choice
        switch (choice) {
        case 1: bookRoom(); break;                     // Book a room
        case 2: showRoomAvailability(); break;         // Check which rooms are available
        case 3: showRoomDetails(); break;              // Display detailed information about all rooms
        case 4: showUsersList(); break;                // Show a list of all users who have booked rooms
        case 5:
            if (searchById() == -1) {  // Search for a user by their ID
                cout << "\033[1;31m" << "User not found!" << "\033[0m\n";
            }
            break;
        case 6: leaveRoom(); break;                    // Vacate a room
        case 7: return 0;                              // Exit the program
        default:                                       // Handle invalid choices
            cout << "\033[1;31m" << "Invalid choice! Please try again." << "\033[0m\n";
        }
    }

    return 0;  // Program ends successfully
}

// Function to display the main menu and get the user's choice
int showMenu() {
    int choice;  // Variable to store the user's menu choice

menuChoice:  // Label to allow retrying in case of invalid input
    cout << "\n********** Hotel Menu **********\n";
    cout << "1. Book a Room\n";
    cout << "2. Check Room Availability\n";
    cout << "3. Display Room Details\n";
    cout << "4. Display Users List\n";
    cout << "5. Search users by ID\n";
    cout << "6. Leave room\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;  // Get input from the user


    // Validate the input to ensure it's a valid menu option
    if (cin.fail() || choice < 1 || choice > 7) {
        cout << "\033[1;31m" << "Invalid choice, please try again." << "\033[0m\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n');  // Ignore invalid input
        goto menuChoice;         // Retry input
    }

    return choice;  // Return the valid choice
}

// Function to register the user's information for a specific room
int registerInfo(int roomNumber) {
    string name, id, phone;  // Variables to store user details

    // Get the user's name
    cout << "Enter your name: ";
    cin.ignore();  // Ignore leftover newline character from previous input
    getline(cin, name);

    // Get the user's ID
    cout << "Enter your ID: ";
    getline(cin, id);

    // Get the user's phone number
    cout << "Enter your phone number: ";
    getline(cin, phone);

    // Check if any of the input fields are empty
    if (name.empty() || id.empty() || phone.empty()) {
        cout << "\033[1;31m" << "Invalid input. Registration failed." << "\033[0m\n";
        return -1;  // Return -1 to indicate failure
    }

    // Store the user's information in the corresponding room's array
    personalInfo[roomNumber - 1][0] = name;
    personalInfo[roomNumber - 1][1] = id;
    personalInfo[roomNumber - 1][2] = phone;

    return 0;  // Return 0 to indicate success
}

// Function to book a room
void bookRoom() {
    int roomNumber;  // Variable to store the room number chosen by the user

roomNumberChoice:  // Label to allow retrying in case of invalid input
    cout << "\nEnter room number to book (1-" << TOTAL_ROOMS << ") (enter 0 to go back): ";
    cin >> roomNumber;

    // Validate the room number input
    if (cin.fail() || roomNumber < 0 || roomNumber > TOTAL_ROOMS) {
        cout << "\033[1;31m" << "Invalid room number! Please try again." << "\033[0m\n";
        cin.clear();             // Clear the error flag
        cin.ignore(INT_MAX, '\n');  // Ignore invalid input
        goto roomNumberChoice;   // Retry input
    } else if (roomNumber == 0) {
        return;  // Return to the main menu if the user enters 0
    } else if (!roomAvailability[roomNumber - 1]) {
        cout << "\033[1;31m" << "Sorry, Room " << roomNumber << " is already booked." << "\033[0m\n";
        goto roomNumberChoice;  // Retry input if the room is already booked
    } else {
        // Register the user's information for the room
        int status = registerInfo(roomNumber);
        if (status == -1) {  // If registration failed
            cout << "\033[1;31m" << "Room not reserved due to registration failure." << "\033[0m\n";
            return;
        }

        // Determine the room type based on the room number
        int room_type = 0;
        while (roomNumber - 1 >= prefixRoomSizes[room_type + 1]) {
            room_type++;
        }

        // Update room reservation data
        roomsReserved[room_type]++;
        roomAvailability[roomNumber - 1] = false;  // Mark the room as booked
        num_available_rooms--;  // Decrease the count of available rooms

        // Success message
        cout << "\033[1;32m" << "Room " << roomNumber << " of type *" << roomTypes[room_type]
             << "* has been successfully booked!" << "\033[0m\n";
    }
}


void showRoomAvailability() {
    // Displays the availability of rooms in the hotel.
    // Shows available rooms if more rooms are reserved; otherwise, shows reserved rooms.

    cout << "\nRoom Availability:\n";

    int room, num_reserved_rooms = TOTAL_ROOMS - num_available_rooms;


    if (num_reserved_rooms > num_available_rooms) { 
        // If more rooms are reserved than available, show the available rooms.
        cout << "\nThese are the available rooms\n";
        room = 0;
        for (int type = 0; type < NUM_ROOM_TYPES; type++) {
            cout << left << "\t" << roomTypes[type] << setw(5) << " - ";
            if (roomsReserved[type] == roomSizes[type]) {
                // If all rooms of this type are reserved.
                cout << "All Booked";
            } else {
                // Display the room numbers that are still available.
                int available = roomSizes[type] - roomsReserved[type];
                for (; room < prefixRoomSizes[type + 1]; room++) {
                    if (roomAvailability[room] == true) {
                        // Display room numbers separated by commas.
                        bool islast = --available > 0;
                        cout << room + 1;
                        if (!islast) {
                            cout << ", ";
                        }
                    }
                }
            }
            cout << endl;
        }
    } else { 
        // If there are more available rooms than reserved ones, show reserved rooms.
        cout << "\nThese are the reserved rooms" << endl;
        room = 0;
        for (int type = 0; type < NUM_ROOM_TYPES; type++) {
            cout << roomTypes[type] << " [" << prefixRoomSizes[type] + 1 << "-" << prefixRoomSizes[type + 1] << "]" << right << setw(3) << " - ";
            if (roomsReserved[type] == 0) {
                // If no rooms of this type are reserved.
                cout << "All Available";
            } else {
                // Display the reserved room numbers.
                int reserved = roomsReserved[type];
                for (; room < prefixRoomSizes[type + 1]; room++) {
                    if (roomAvailability[room] == false) {
                        bool islast = --reserved == 0;
                        cout << room + 1;
                        if (!islast) {
                            cout << ", ";
                        }
                    }
                }
            }
            cout << endl;
        }
    }
}

void showRoomDetails() {
    // Displays detailed information about room types, including range, price, and availability.

    cout << "\nRoom Details:\n";
    cout << left << setw(10) << "Types" << setw(15) << "Range" << setw(10) << "Price" << setw(15) << "Status" << "\n";
    cout << "----------------------------------------------------\n";
    for (int i = 0; i < NUM_ROOM_TYPES; i++) {
        // Build range string, e.g., [1-5], for each room type.
        string range = "[" + to_string(prefixRoomSizes[i] + 1) + "-" + to_string(prefixRoomSizes[i + 1]) + "]";
        cout << left << setw(10) << roomTypes[i] << setw(15) << range << setw(10) << to_string(roomPrices[i]) + " Br";
        if (roomsReserved[i] == roomSizes[i]) {
            // All rooms of this type are booked.
            cout << "All Booked\n";
        } else {
            // Display how many rooms are available for this type.
            cout << roomSizes[i] - roomsReserved[i] << " rooms Available\n";
        }
    }
}

void showUsersList() {
    // Displays a list of users currently staying in the hotel, along with their room details.

    cout << "\n\nList of People in this Hotel\n\n";

    cout << left << setw(10) << "Room No." << setw(20) << "Name" << setw(10) << "Id" << setw(15) << "Phone Number" << setw(10) << "Room Types";
    cout << setw(10 + 20 + 10 + 15 + 10 + 5) << setfill('-') << "\n";
    cout << setfill(' ') << endl;

    int room_type = 0;
    for (int room = 0; room < TOTAL_ROOMS; room++) {
        // Determine the room type for the current room.
        if (room >= prefixRoomSizes[room_type + 1]) {
            room_type++;
        }


        if (roomAvailability[room] == false) {
            // If the room is occupied, display the occupant's details.
            string name = personalInfo[room][0], id = personalInfo[room][1], phone = personalInfo[room][2];
            cout << left << setw(10) << room + 1 << setw(20) << name << setw(10) << id << setw(15) << phone << setw(10) << roomTypes[room_type] << endl;
        }
    }
    cout << "\033[1;32m" << "\v\v\v" << "\033[0m";
}

int searchById() {
    // Searches for a user by their ID and displays their details if found.
    string id;
    cout << "Enter the Id: ";
    cin.ignore();
    getline(cin, id);

    int room_type = 0;
    for (int room = 0; room < TOTAL_ROOMS; room++) {
        if (roomAvailability[room] == false) {
            // Compare input ID with the ID of the user in the room.
            string roomUserId = personalInfo[room][1];
            if (roomUserId == id) {
                // User found; display their details.
                cout << "\033[1;32m" << "\nFound the user" << "\033[0m" << endl;
                cout << "Name: " << personalInfo[room][0] << endl;
                cout << "Id: " << personalInfo[room][1] << endl;
                cout << "Phone: " << personalInfo[room][2] << endl;
                cout << "Room No.: " << room + 1 << endl;
                cout << "Room type: " << roomTypes[room_type] << endl;
                cout << "\v\v\v";
                return 0; // Exit function after finding the user.
            }
        }
        if (room + 1 >= prefixRoomSizes[room_type + 1]) {
            room_type++;
        }
    }
    return -1; // Return -1 if the user is not found.
}

void leaveRoom() {
    // Allows a user to check out of their room.

    int roomNumber;
leave_room:
    cout << "\nEnter the room number (0 to go back): ";
    cin >> roomNumber;
    if (cin.fail() || roomNumber < 0) {
        // Validate input and retry if invalid.
        cin.clear();
        cin.ignore();
        goto leave_room;
    }

    if (roomNumber != 0) {
        roomNumber--; // Convert the room number to zero-based indexing.
        if (roomAvailability[roomNumber] == true) {
            // If the room is already empty, prompt again.
            cout << "\033[1;31m" << "Room is already empty \v\v\v" << "\033[0m";
            goto leave_room;
        }

        // Clear the occupant's information.
        string name = personalInfo[roomNumber][0];
        for (int i = 0; i < 3; i++) {
            personalInfo[roomNumber][i] = '\0';
        }
        roomAvailability[roomNumber] = true; // Mark the room as available.
        num_available_rooms++; // Increment the count of available rooms.

        // Determine the room type of the checked-out room.
        int room_type = 0;
        while (roomNumber >= prefixRoomSizes[room_type + 1]) {
            room_type++;
        }
        roomsReserved[room_type]--; // Decrease the reserved count for this room type.

        // Thank the user for their stay.
        cout << "\033[1;32m" << "Thank you for using Our Hotel " << name << ". Goodbye!" << "\033[0m\n";
    }
}
