#include "../Components/Customer/customer.h"
#include "../Structures/structures.h"
#include <vector>


using namespace std;

bool logIn(int &user_id, bool &isStaff, bool &isCustomer,
           bool &isUserRegistered);
void logOut(int &user_id, bool &isStaff, bool &isCustomer,
            bool &isUserRegistered, void (*startProgram)());
bool signUp(int &user_id, bool &isStaff, bool &isCustomer,
            bool &isUserRegistered);
