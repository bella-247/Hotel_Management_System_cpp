#include "customer.h"

using namespace std;
// helper functions

bool isCustomerAlreadyRegistered(Customer &customer) {
  for (const Customer &c : customers) {
    if (c.email == customer.email) {
      return true;
    }
  }
  return false;
}

bool getCustomerData(Customer &customer) {
  cleanInput();
  while (true) {
    cout << "Name: ";
    getline(cin, customer.name);
    cout << "Email: ";
    getline(cin, customer.email);
    cout << "Password: ";
    getline(cin, customer.password);
    cout << "Phone Number: ";
    getline(cin, customer.phone_number);

    // if any of the fields are empty i want them to insert again
    if (isEmpty(customer.name) || isEmpty(customer.email) ||
        isEmpty(customer.password) || isEmpty(customer.phone_number)) {
      cout << "Empty fields detected. Please fill all fields correctly.\n"
           << endl;
      continue;
    }
    // if the customer already exists i want to return to the menu
    if (isCustomerAlreadyRegistered(customer)) {
      cout << "Customer already registered. Please try again.\n" << endl;
      return false;
    }
    return true;
  }
}

int findCustomer() {
  string email;
  cout << "Enter the email of the customer: ";
  cleanInput();
  getline(cin, email);

  for (Customer c : customers) {
    if (c.email == email) {
      return c.customer_id;
    }
  }
  cout << "Customer not found." << endl;
  return -1;
}

bool getCustomerById(int &customer_id, Customer &customer) {
  for (Customer c : customers) {
    if (c.customer_id == customer_id) {
      customer = c;
      return true;
    }
  }
  return false;
}


// main functions

Customer addCustomer() {
  Customer customer;
  if(!getCustomerData(customer)){
    return Customer();
  }

  try {
    string insertQuery = "INSERT INTO Customers (name, email, password, "
                         "phone_number) VALUES ('" +
                         customer.name + "', '" + customer.email + "', '" +
                         customer.password + "', '" + customer.phone_number +
                         "');";

    if (!insertObject(insertQuery, "Customers", CustomerCallback, &customers)) {
      throw runtime_error("Failed to create customer in database");
    }

    cout << "Customer " << customer.name << " created successfully!" << endl;
    return customers.back();
  } 
  catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exitProgram();
    return Customer(); // Return an empty Customer object in case of error
  }
}

void removeCustomer() {
  string email;
  cleanInput();
  cout << "Enter the email of the customer to remove: ";
  getline(cin, email);

  bool found = false;
  for (int i = 0; i < customers.size(); ++i) {
    if (customers.at(i).email == email) {
      customers.erase(customers.begin() + i);
      found = true;
      break;
    }
  }
  if (!found) {
    cout << "Customer not found." << endl;
    return;
  }
  
  try {
    string deleteQuery = "DELETE FROM Customers WHERE email = '" + email + "';";

    if (!deleteObject(deleteQuery)) {
      throw runtime_error("Failed to delete customer from database");
    }

    cout << "Customer deleted successfully!" << endl;
  }
  catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exitProgram();
  }
}

// Show the profile of the current customer
void showCustomerProfile(int &customer_id) {
  Customer customer;
  if (!getCustomerById(customer_id, customer)) {
    cout << "Customer not found." << endl;
    return;
  }

  cout << "\n--- Customer Profile ---\n";

  cout << "\tCustomer ID: " << customer.customer_id << endl;
  cout << "\tName: " << customer.name << endl;
  cout << "\tEmail: " << customer.email << endl;
  cout << "\tPhone Number: " << customer.phone_number << endl;
}

// Print the list of customers in tabular format in reverse order
void showCustomers() {
  if (customers.empty()) {
    cout << "No customers registered.\n";
    return;
  }

  cout << "\n--- Customer List ---\n";
  cout << left << setw(12) << "Customer ID" << setw(20) << "Name" << setw(30)
       << "Email" << setw(15) << "Phone" << endl;

  cout << string(77, '-') << endl;

  for (int i = customers.size() - 1; i > -1; --i) {
    const Customer &customer = customers.at(i);
    cout << left << setw(12) << customer.customer_id << setw(20)
         << customer.name << setw(30) << customer.email << setw(15)
         << customer.phone_number << endl;
  }
}


// database functions

// get customers from the database
void getCustomers() {
  try {
    string query = "SELECT * FROM Customers;";

    if (!getObjects(query, CustomerCallback, &customers)) {
      throw runtime_error("Error when retrieving all the customers");
    }
    cout << "Customers initialized successfully." << endl;
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exitProgram();
  }
}

int CustomerCallback(void *data, int columns, char **values,
                     char **column_names) {
  vector<Customer> *customers = static_cast<vector<Customer> *>(data);
  Customer customer;

  customer.customer_id = atoi(values[0]);
  customer.name = values[1] ? values[1] : "";
  customer.email = values[2] ? values[2] : "";
  customer.password = values[3] ? values[3] : "";
  customer.phone_number = values[4] ? values[4] : "";

  customers->push_back(customer);
  return 0;
}
