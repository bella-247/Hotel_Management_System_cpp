#include "staff.h"

// Get staff by ID
bool getStaffById(int &staff_id, Staff &staff) {
  for (Staff s : staffs) {
    if (s.staff_id == staff_id) {
      staff = s;
      return true;
    }
  }
  return false;
}

// Retrieve all the staffs from the database
void getStaffs() {
  try {
    string query = "SELECT * FROM Staff;";

    if (!getObjects(query, StaffCallback, &staffs)) {
      throw runtime_error("Error when retrieving all the staffs");
    }
    cout << "Staffs initialized successfully." << endl;
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exit(1);
  }
}

Staff addStaff(Staff &staff) {
  try {
    string insertQuery = "INSERT INTO Staff (name, email, password, "
                         "phone_number, role) VALUES ('" +
                         staff.name + "', '" + staff.email + "', '" +
                         staff.password + "', '" + staff.phone_number + "', '" +
                         staff.role + "');";

    if (!insertObject(insertQuery, "Staff", StaffCallback, &staffs)) {
      throw runtime_error("Failed to create staff in database");
    }

    cout << "Staff < " << staff.name << " > created successfully!" << endl;
    current_user.staff_id = staffs.back().staff_id;
    return staffs.back();
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exit(1);
  }
}

void removeStaff(int &staff_id) {
  try {
    string deleteQuery =
        "DELETE FROM Staff WHERE staff_id = " + to_string(staff_id) + ";";

    if (!deleteObject(deleteQuery)) {
      throw runtime_error("Failed to delete staff from database");
    }

    bool found = false;
    for (int i = 0; staffs.size(); ++i) {
      if (staffs.at(i).staff_id == staff_id) {
        staffs.erase(staffs.begin() + i);
        found = true;
        break;
      }
    }
    if (found) {
      cout << "Staff deleted successfully!" << endl;
    } else {
      cout << "Couldn't find the specified staff!" << endl;
    }
    return;
  }

  catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exit(1);
  }
}

void showStaffs() {
  if (staffs.empty()) {
    cout << "No staffs registered.\n";
    return;
  }

  cout << "\n--- Staff List ---\n";
  cout << left << setw(12) << "Staff ID" << setw(20) << "Name" << setw(30)
       << "Email" << setw(15) << "Phone" << setw(10) << "Role" << endl;

  cout << string(77, '-') << endl;

  for (int i = staffs.size() - 1; i > -1; --i) {
    const Staff &staff = staffs.at(i);

    cout << left << setw(12) << staff.staff_id << setw(20) << staff.name
         << setw(30) << staff.email << setw(15) << staff.phone_number
         << setw(10) << staff.role << endl;
  }
}

int StaffCallback(void *data, int columns, char **values, char **column_names) {
  vector<Staff> *staffs = static_cast<vector<Staff> *>(data);
  Staff staff;

  staff.staff_id = atoi(values[0]);
  staff.name = values[1] ? values[1] : "";
  staff.email = values[2] ? values[2] : "";
  staff.password = values[3] ? values[3] : "";
  staff.phone_number = values[4] ? values[4] : "";
  staff.role = values[5] ? values[5] : "";

  staffs->push_back(staff);
  return 0;
}
