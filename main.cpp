#include <iostream>
#include <iomanip>
#include <string>
#include "database/database.cpp"
#include "structures/structures.cpp"
#include "Auth/authentication.cpp"

using namespace std;

// --------------------- global variables ----------------- //
int customer_id, staff_id;
bool isUserRegistered = false;
bool isStaff = false, isCustomer = false;

// ---------- main functions --------------//
void initializeDatabase();

// -----------------menu functions ------------------------ //
void showRegistrationMenu();
void showCustomerMenu();
void showStaffMenu();

// ------------- authentication functions --------------//





// --------- helper functions -------------- //
void showChoiceError();


// initialize vectors 
vector <Staff> staffs;
vector <RoomType> room_types;
vector <Room> rooms;
vector <Customer> customers;
vector <Booking> bookings;
vector <Payment> payments;

int main(){
    initializeDatabase();
    main:
        cout << "\n============================================\n";
        cout << "\033[1;32m" << "         Welcome to Utopia Hotel        " << "\033[0m\n";
        cout << "============================================\n";

        while(true){
            if (!isUserRegistered){
                showRegistrationMenu();
            }
            else{
                if(isCustomer){
                    showCustomerMenu();
                }
                else{
                    showStaffMenu();
                }
            }
        }
    return 0;
}




// menu functions

void showRegistrationMenu(){
    int choice;
    typeOfUser:
        cout << "1, Staff" << endl;
        cout << "2, Customer" << endl;
        cout << "Choice the type of user: ";
        cin >> choice;

        if(cin.fail()){
            showChoiceError();
            goto typeOfUser;
        }

        switch(choice){
                case 1:
                    isCustomer = false;
                    isStaff = true;
                    break;
                case 2:
                    isCustomer = true;
                    isStaff = false;
                    break;
                default:
                    showChoiceError();
                    goto typeOfUser;
        }


        authenticationType:
            cout << "0, Previous menu" << endl;
            cout << "1, Sign Up " << endl;
            cout << "2, Log In " << endl;
            cout << "Choose from the above: ";
            cin >> choice;

            if(cin.fail()){
                showChoiceError();
                goto authenticationType;
            }

            switch(choice){
                case 0:
                    goto typeOfUser;
                case 1:
                    if(signUp() == -1)
                        goto authenticationType;
                    break;

                case 2:
                    if(logIn() == -1)
                        goto authenticationType;
                    break;
                default:
                    showChoiceError();
                    goto authenticationType;
            }
}

void showCustomerMenu(){
    int choice;
    menu:
        cout << "\n********** Hotel Menu **********\n";
        cout << "1. Book a Room\n";
        cout << "2. Check Room Availability\n";
        cout << "3. Display Room Details\n";
        cout << "4. Leave Room\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;  // Get input from the user

        if(cin.fail() || choice < 1 || choice > 5){
            showChoiceError();
            goto menu;
        }

}

void showStaffMenu(){
    int choice;

    menu:
        cout << "\n********** Hotel Menu **********\n";
        cout << "1. Display Users List\n";
        cout << "2. Search Users by ID\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail() || choice < 1 || choice > 2){
            showChoiceError();
            goto menu;
        }
}






void showChoiceError(){
    cout << "\033[1;31m" << "Invalid choice, please try again." << "\033[0m\n\n";
    cin.clear();             // Clear the error flag
    cin.ignore(INT_MAX, '\n');  // Ignore invalid input
}

































void initializeDatabase(){
    initializeRoomTypes();
    initializeRooms();
    initializeCustomers();
    initializeBookings();
    initializePayments();
}
