#include "authentication.h"


bool signUp() {
    if(current_user.isCustomer){
        Customer new_customer = addCustomer();
        if(new_customer.customer_id == -1){
            return false;
        }
        current_user.customer_id = new_customer.customer_id;
        return true;
    }
    else if(current_user.isStaff){
        Staff new_staff = addStaff();
        if(new_staff.staff_id == -1){
            return false;
        }
        current_user.staff_id = new_staff.staff_id;
        return true;
    }

    return false;
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
