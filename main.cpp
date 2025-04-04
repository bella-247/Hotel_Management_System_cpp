#include <iostream>
#include <iomanip>
#include <string>
#include "database.cpp"
#include "structures.cpp"

using namespace std;

// --------------------- global variables ----------------- //
int customer_index;
bool isUserRegistered = false;
bool isStaff = false, isCustomer = false;

// ---------- main functions --------------//
void initializeDatabase();

// -----------------menu functions ------------------------ //
void showRegistrationMenu();
void showCustomerMenu();
void showStaffMenu();

// ------------- authentication functions --------------//
int logIn();
int signUp();
int logOut();

// --------- helper functions -------------- //
void showChoiceError();

int main(){
    initializeDatabase();
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

        if(cin.fail || choice < 1 || choice > 5){
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

        if(cin.fail || choice < 1 || choice > 2){
            showChoiceError();
            goto menu;
        }
}


int signUp(){
    string name, email, phone_number, password, role;

    signup:
        cout << "Signing up.." << endl;

        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        cin >> password;
        cout << "Enter your phone number: ";
        cin >> phone_number;

        if(isStaff){
            cout << "Enter your role: ";
            cin >> role;
        }

        if(name.empty() || email.empty() || phone_number.empty() || password.empty() || (isStaff && role.empty())){
                cout << "Empty fields detected, please fill all the fields correctly."<< endl;
                goto signup;
        }

        bool found = false;
        if(isCustomer){
            for(int i = 0; i < CUSTOMER_SIZE; i++){
                if(customers[i].email == email || customers[i].phone_number == phone_number){
                    cout << "User already registered, please login.";
                    return logIn();
                }
            }
            if(!found){
                customers[CUSTOMER_SIZE].customer_id = CUSTOMER_SIZE;
                customers[CUSTOMER_SIZE].name = name;
                customers[CUSTOMER_SIZE].email = email;
                customers[CUSTOMER_SIZE].password = password;
                customers[CUSTOMER_SIZE].phone_number = phone_number;
                isUserRegistered = true;
                CUSTOMER_SIZE++;

                cout << "Successfully Registered!!" << endl;
                return 0;
            }
        }

        else{
            for(int i = 0; i < STAFF_SIZE; i++){
                if(staff[i].email == email || staff[i].phone_number == phone_number){
                    cout << "User already registered, please login.";
                    return logIn();
                }
            }

            if(!found){
                staff[STAFF_SIZE].staff_id = STAFF_SIZE;
                staff[STAFF_SIZE].name = name;
                staff[STAFF_SIZE].email = email;
                staff[STAFF_SIZE].password = password;
                staff[STAFF_SIZE].phone_number = phone_number;
                staff[STAFF_SIZE].role = role;
                isUserRegistered = true;
                STAFF_SIZE++;

                cout << "Successfully Registered!!" << endl;
                return 0;
            }
        }

}


int logIn(){
    string name, email, phone_number, password, role;

    login:
        cout << "Logging in.." << endl;

        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        cin >> password;

        if(email.empty() || password.empty()){
                cout << "Empty fields detected, please fill all the fields correctly."<< endl;
                goto login;
        }

        bool found = false;
        if(isCustomer){
            for(int i = 0; i < CUSTOMER_SIZE; i++){
                if(customers[i].email == email && customers[i].password == password){
                    cout << "Successfully Logged In" << endl;
                    customer_index = i;
                    isUserRegistered = true;
                    return 0;
                }
            }
            if(!found){
                cout << "Email or Password doesn't match!" << endl;
                cout << "If you don't have account please sign up" << endl;
                return -1;
            }
        }

        else{
            for(int i = 0; i < STAFF_SIZE; i++){
                if(staff[i].email == email || staff[i].phone_number == phone_number){
                    cout << "Successfully Logged In!!" << endl;
                    customer_index = i;
                    isUserRegistered = true;
                    return 0;
                }
            }

            if(!found){
                cout << "Email or Password doesn't match!" << endl;
                cout << "If you don't have account please sign up" << endl;
                return -1;
            }
        }
}

int logOut(){
    cout << "Logging out.." << endl;
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
