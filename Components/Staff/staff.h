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

bool isStaffAlreadyRegistered(Staff &staff);
bool getStaffData(Staff &staff);
int findStaff();
bool getStaffById(int& staff_id, Staff& staff);
void getStaffs();
Staff addStaff();
void removeStaff();
void showStaffs();
void showStaffProfile(int& staff_id = current_user.staff_id);
int StaffCallback(void*, int, char**, char**);

#endif
