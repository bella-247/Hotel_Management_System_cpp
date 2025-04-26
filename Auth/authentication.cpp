#include "authentication.h"


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

bool getData(Customer &customer){
    cleanInput();
    cout << "Name: "; getline(cin, customer.name);
    cout << "Email: "; getline(cin, customer.email);
    cout << "Password: "; getline(cin, customer.password);
    cout << "Phone Number: "; getline(cin, customer.phone_number);

    if (isEmpty(customer.name) || isEmpty(customer.email) || isEmpty(customer.password) || isEmpty(customer.phone_number)) {
        cout << "Empty fields detected. Please fill all fields correctly.\n" << endl;
        return false;
    }
    return true;
}

bool getData(Staff &staff){
    cleanInput();
    cout << "Name: ";  getline(cin, staff.name);
    cout << "Email: "; getline(cin, staff.email);
    cout << "Password: "; getline(cin, staff.password);
    cout << "Phone Number: "; getline(cin, staff.phone_number);
    cout << "Role: "; getline(cin, staff.role);

    if(isEmpty(staff.name) || isEmpty(staff.email) || isEmpty(staff.password) || isEmpty(staff.phone_number) || isEmpty(staff.role)) {
        cout << "Empty fields detected. Please fill all fields correctly.\n" << endl;
        return false;
    }
    return true;
}

bool isAlreadyRegistered(Customer &customer) {
    for (const Customer& c : customers) {
        if (c.email == customer.email) {
            return true;
        }
    }
    return false;
}

bool isAlreadyRegistered(Staff &staff) {
    for (const Staff& s : staffs) {
        if (s.email == staff.email) {
            return true;
        }
    }
    return false;
}

bool signUp() {
    Customer new_customer;
    Staff new_staff;
    bool success = false;

    while (!success) {
        cout << "\nSigning up..." << endl;
        if(current_user.isCustomer){
            if(!getData(new_customer)) {
                cout << "Failed to get customer data. Please try again.\n" << endl;
                continue;
            }
            success = true;
        } else {
            if(!getData(new_staff)) {
                cout << "Failed to get staff data. Please try again.\n" << endl;
                continue; 
            }
            success = true; 
        }

        // Check if user already exists
        bool alreadyRegistered = false;
        if (current_user.isCustomer) {
            alreadyRegistered = isAlreadyRegistered(new_customer);
        } else {
            alreadyRegistered = isAlreadyRegistered(new_staff);
        }

        if (alreadyRegistered) {
            cout << "User already registered. Please login.\n" << endl;
            return false;
        }

        // Registration
        if (current_user.isCustomer) {
            addCustomer(new_customer);
            cout << "Customer " << new_customer.name << " successfully registered!\n" << endl;
        } else {
            addStaff(new_staff);
            cout << "Staff " << new_staff.name << " successfully registered!\n" << endl;
        }
        success = true;
    }

    return success;
}



bool logIn() {
    string email, password;

    while (true) {
        cout << "\nLogging in..." << endl;
        cleanInput();
        cout << "Email: "; getline(cin, email);
        cout << "Password: "; getline(cin, password);

        if (isEmpty(email) || isEmpty(password)) {
            cout << "Empty fields detected. Please fill all fields correctly.\n" << endl;
            continue;
        }

        if (current_user.isCustomer) {
            for (const Customer& c : customers) {
                if (c.email == email && c.password == password) {
                    cout << "Successfully logged in as Customer!\n" << endl;
                    current_user.customer_id = c.customer_id;
                    return true;
                }
            }
        } else {
            for (const Staff& s : staffs) {
                if (s.email == email && s.password == password) {
                    cout << "Successfully logged in as Staff!\n" << endl;
                    current_user.staff_id = s.staff_id;
                    return true;
                }
            }
        }

        cout << "Email or password doesn't match!" << endl;
        cout << "If you don't have an account, please sign up.\n" << endl;
        return false;
    }
}

void logOut(void (*startProgram)()) {
    cout << "\nLogging out..." << endl;
    current_user.isStaff = false;
    current_user.isCustomer = false;
    current_user.customer_id = -1;
    current_user.staff_id = -1;
    if (startProgram) {
        startProgram();
    }
}
