#include <vector>
#include "../Structures/structures.h"
#include "../Systems/Customer/customer.h"

using namespace std;

bool logIn(int& user_id, bool& isStaff, bool& isCustomer, bool& isUserRegistered, vector<Customer>& customers, vector<Staff>& staffs);
void logOut(int& user_id, bool& isStaff, bool& isCustomer, bool& isUserRegistered, void (*startProgram)());
bool signUp(int& user_id, bool& isStaff, bool& isCustomer, bool& isUserRegistered, vector<Customer>& customers, vector<Staff>& staffs);
