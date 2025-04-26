#include "authentication.h"

bool signUp(int &user_id, 
           bool &isStaff, bool &isCustomer, bool &isUserRegistered, vector<Customer> &customers,
           vector<Staff> &staffs) {
  string name, email, phone_number, password, role;

signup:
  cout << "\n Signing up.." << endl;

  cout << "Enter your name: ";
  cin >> name;
  cout << "Enter your email: ";
  cin >> email;
  cout << "Enter your password: ";
  cin >> password;
  cout << "Enter your phone number: ";
  cin >> phone_number;

  if (isStaff) {
    cout << "Enter your role: ";
    cin >> role;
  }

  if (name.empty() || email.empty() || phone_number.empty() ||
      password.empty() || (isStaff && role.empty())) {
    cout << "Empty fields detected, please fill all the fields correctly."
         << endl;
    goto signup;
  }

  bool found = false;
  if (isCustomer) {
    for (const Customer &customer : customers) {
      if (customer.email == email) {
        cout << "User already registered, please login.";
        return logIn(user_id, isUserRegistered, isStaff,
                     isCustomer, customers, staffs);
      }
    }
    if (!found) {
      addCustomer(customers, name, email, password, phone_number);
      isUserRegistered = true;
      return true;
    }
  }

  else {
    for (const Staff &staff : staffs) {
      if (staff.email == email) {
        cout << "User already registered, please login.";
        return logIn(user_id, isUserRegistered, isStaff,
                     isCustomer, customers, staffs);
      }
    }

    if (!found) {
      int new_id = staffs.empty() ? 1 : staffs.back().staff_id + 1;
      staffs.push_back({new_id, name, email, password, phone_number, role});
      isUserRegistered = true;
      cout << "Staff<" << name << "> Successfully Registered!!" << endl;
      return true;
    }
  }

  return false;
}

bool logIn(int &user_id, 
          bool &isStaff, bool &isCustomer, bool &isUserRegistered, vector<Customer> &customers,
          vector<Staff> &staffs) {
  string email, password;

login:
  cout << "first email: " << customers.at(0).email << endl;
  cout << "first password: " << customers.at(0).password << endl;
  cout << "\nLogging in.." << endl;

  cout << "Enter your email: ";
  cin >> email;
  cout << "Enter your password: ";
  cin >> password;
  cout << "Email: " << email;
  cout << "Password: " << password;

  if (email.empty() || password.empty()) {
    cout << "Empty fields detected, please fill all the fields correctly."
         << endl;
    goto login;
  }

  bool found = false;
  if (isCustomer) {
    for (Customer customer : customers) {
      cout << "Customer email: " << customer.email << endl;
      cout << "Customer password: " << customer.password << endl;
      if (customer.email == email && customer.password == password) {
        cout << "Successfully Logged In" << endl;
        user_id = customer.customer_id;
        isUserRegistered = true;
        return true;
      }
    }
    if (!found) {
      cout << "Email or Password doesn't match!" << endl;
      cout << "If you don't have account please sign up" << endl;
      return false;
    }
  }

  else {
    for (Staff staff : staffs) {
      cout << "Staff email: " << staff.email << endl;
      cout << "Staff password: " << staff.password << endl;
      if (staff.email == email && staff.password == password) {
        cout << "Successfully Logged In!!" << endl;
        user_id = staff.staff_id;
        isUserRegistered = true;
        return true;
      }
    }

    if (!found) {
      cout << "Email or Password doesn't match!" << endl;
      cout << "If you don't have account please sign up" << endl;
      return false;
    }
  }
  return false;
}

void logOut(int &user_id, bool &isStaff, bool &isCustomer, bool &isUserRegistered, void (*startProgram)()) {
  cout << "\nLogging out.." << endl;
  isUserRegistered = false;
  isStaff = false;
  isCustomer = false;
  user_id = -1;
  startProgram();
}
