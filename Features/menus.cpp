#include <iostream>
#include <string>
#include <vector>
#include "../structures/structures.h"
#include "../Auth/authentication.h"

using namespace std; 


void showChoiceError(){
    cout << "\033[1;31m" << "Invalid choice, please try again." << "\033[0m\n\n";
    cin.clear();             // Clear the error flag
    cin.ignore(INT_MAX, '\n');  // Ignore invalid input
}

void showRegistrationMenu(int &customer_id, int &staff_id, bool &isUserRegistered, bool &isStaff, bool &isCustomer, vector<Customer> &customers, vector<Staff> &staffs){
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
                    if(signUp(customer_id, staff_id, isUserRegistered, isStaff, isCustomer, customers, staffs) == -1)
                        goto authenticationType;
                    break;

                case 2:
                    if(logIn(customer_id, staff_id, isUserRegistered, isStaff, isCustomer, customers, staffs) == -1)
                        goto authenticationType;
                    break;
                default:
                    showChoiceError();
                    goto authenticationType;
            }
}

void showStaffMenu(){
    int choice;

    menu:
        cout << "\n********** Hotel Menu **********\n";
        cout << "1. Display Users List\n";
        cout << "2. Search Users by email\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if(cin.fail() || choice < 1 || choice > 2){
            showChoiceError();
            goto menu;
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

