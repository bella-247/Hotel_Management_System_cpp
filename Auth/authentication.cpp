#include <iostream>
#include <string>
#include "structures/structures.cpp"
using namespace std;

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
            for(Customer customer : customers){
                if(customer.email == email || customer.phone_number == phone_number){
                    cout << "User already registered, please login.";
                    return logIn();
                }
            }
            if(!found){
                customers.push_back({customers.back().customer_id + 1, name, email, password, phone_number});
                isUserRegistered = true;

                cout << "Customer<" << name << "> Successfully Registered!!" << endl;
                return 0;
            }
        }

        else{
            for(Staff staff : staffs){
                if(staff.email == email || staff.phone_number == phone_number){
                    cout << "User already registered, please login.";
                    return logIn();
                }
            }

            if(!found){
                staffs.push_back({staffs.back().staff_id + 1, name, email, password, phone_number, role});
                isUserRegistered = true;
                cout << "Staff<" << name << "> Successfully Registered!!" << endl;
                return 0;
            }
        }

}


int logIn(){
    string email, password;

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
            for(Customer customer : customers){
                if(customer.email == email && customer.password == password){
                    cout << "Successfully Logged In" << endl;
                    customer_id = customer.customer_id;
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
            for(Staff staff : staffs){
                if(staff.email == email || staff.password == password){
                    cout << "Successfully Logged In!!" << endl;
                    staff_id = staff.staff_id;
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
    isUserRegistered = false;
    isStaff = false;
    isCustomer = false;
    staff_id = -1;
    customer_id = -1;
    goto main;
}