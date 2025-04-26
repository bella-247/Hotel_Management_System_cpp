#ifndef STAFF_H
#define STAFF_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>
#include "../../Structures/structures.h"
#include "../../Database/database.h"

using namespace std;

bool getStaffById(int& staff_id, Staff& staff);
void getStaffs();
Staff addStaff(Staff& staff);
void removeStaff(int& staff_id);
void showStaffs();
int StaffCallback(void*, int, char**, char**);

#endif
