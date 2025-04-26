

#include "menus.h"
#include "../Components/Payment/payment.h"
#include <climits>
#include <iostream>

using namespace std;
using namespace std;

void clearInput() {
  cin.clear();
  cin.ignore(INT_MAX, '\n');
}

void showChoiceError() {
  cout << "\033[1;31m" << "Invalid choice, please try again." << "\033[0m\n\n";
  clearInput();
}

void showRegistrationMenu() {
  int choice;

  cout << "\n********** Registration Menu **********\n";
typeOfUser:
    cout << "1, Staff" << endl;
    cout << "2, Customer" << endl;
    cout << "Choice the type of user: ";
    cin >> choice;

  if (cin.fail()) {
    showChoiceError();
    goto typeOfUser;
  }

  switch (choice) {
  case 1:
    current_user.isCustomer = false;
    current_user.isStaff = true;
    break;
  case 2:
    current_user.isCustomer = true;
    current_user.isStaff = false;
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

  if (cin.fail()) {
    showChoiceError();
    goto authenticationType;
  }

  switch (choice) {
  case 0:
    goto typeOfUser;
  case 1: {
    if (current_user.isCustomer) {
      if (!signUp())
        goto authenticationType;
    } else {
      if (!signUp())
        goto authenticationType;
    }
    break;
  }
  case 2: {
    if (current_user.isCustomer) {
      if (!logIn())
        goto authenticationType;
    } else {
      if (!logIn())
        goto authenticationType;
    }
    break;
  }
  default:
    showChoiceError();
    goto authenticationType;
  }
}

void showStaffMenu(void (*startProgram)()) {
                  
  int choice;

menu:
  cout << "\n********** Staff Menu **********\n";
  cout << "1. Display Customers List\n";
  cout << "2. Search Customers by email\n";
  cout << "3. Display Staffs List\n";
  cout << "4. Search Staffs by email\n";
  cout << "5. Display Booking History\n";
  cout << "6. Display Payment History\n";
  cout << "7. Logout\n";
  cout << "8. Exit\n";
  cout << "Enter your choice: ";
  cin >> choice;

  if (cin.fail() || choice < 1 || choice > 8) {
    showChoiceError();
    goto menu;
  }

  switch (choice) {
  case 1:
    showCustomers();
    break;
  case 2:
    // Add search customers functionality
    break;
  case 3:
    // Add show staffs functionality
    break;
  case 4:
    // Add search staffs functionality
    break;
  case 5:
    // Add show booking history functionality
    break;
  case 6:
    showPaymentHistory();
    break;
  case 7:
    logOut(startProgram);
    break;
  case 8:
    exit(0);
    break;
  default:
    showChoiceError();
    goto menu;
  }
}

void showCustomerMenu(void (*startProgram)()) {
  int choice;
menu:
  cout << "\n********** Customer Menu **********\n";
  cout << "1. Book a Room\n";
  cout << "2. See Available Rooms\n";
  cout << "3. Display Room Details\n";
  cout << "4. Leave Room\n";
  cout << "5. Show Profile\n";
  cout << "6. Logout\n";
  cout << "7. Exit\n";

  cout << "Enter your choice: ";
  cin >> choice;

  if (cin.fail() || choice < 1 || choice > 7) {
    showChoiceError();
    goto menu;
  }

  switch (choice) {
  case 1:
    // Add book room functionality
    break;
  case 2:
    // Add show available rooms functionality
    break;
  case 3:
    // Add show room details functionality
    break;
  case 4:
    // Add leave room functionality
    break;
  case 5:
    // Add show profile functionality
    break;
  case 6:
    logOut(startProgram);
    break;
  case 7:
    exit(0);
    break;
  default:
    showChoiceError();
    goto menu;
  }
}
