#include <vector>
#include "../structures/structures.h"

using namespace std;

int logIn(int &customer_id, int &staff_id, bool &isUserRegistered, bool &isStaff, bool &isCustomer, vector<Customer> &customers, vector<Staff> &staffs);
int logOut(int &staff_id, int &customer_id, bool &isUserRegistered, bool &isStaff, bool &isCustomer);
int signUp(int &customer_id, int &staff_id, bool &isUserRegistered, bool &isStaff, bool &isCustomer, vector<Customer> &customers, vector<Staff> &staffs);
