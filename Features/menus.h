#include <vector>
#include "../structures/structures.h"

using namespace std;

void showChoiceError();
void showRegistrationMenu(int &customer_id, int &staff_id, bool &isUserRegistered, bool &isStaff, bool &isCustomer, vector<Customer> &customers, vector<Staff> &staffs);
void showStaffMenu();
void showCustomerMenu();
