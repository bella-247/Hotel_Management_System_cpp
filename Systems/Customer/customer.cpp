#include "customer.h"

void getCustomers(vector<Customer> &customers) {
  try {
    string query = "SELECT * FROM Customers;";

    if (!getObjects(query, CustomerCallback, &customers)) {
      throw runtime_error("Erorr when retrieving all the customers");
    }
    cout << "Customers initialized succesfully." << endl;
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exit(1);
  }
}

Customer addCustomer(vector<Customer> &customers, string &name, string &email,
                     string &password, string &phone_number) {
  try {
    string insertQuery = "INSERT INTO Customers (name, email, password, "
                         "phone_number) VALUES ('" +
                         name + "', '" + email + "', '" + password + "', '" +
                         phone_number + "');";

    if (!insertObject(insertQuery, "Customers", CustomerCallback, &customers)) {
      throw runtime_error("Failed to create customer in database");
    }

    cout << "Customer " << name << " created successfully!" << endl;
    return customers.back();
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exit(1);
  }
}

void removeCustomer(vector<Customer> &customers, int &customer_id) {
  try {
    string deleteQuery =
        "DELETE FROM Customers WHERE customer_id = " + to_string(customer_id) +
        ";";

    if (!deleteObject(deleteQuery)) {
      throw runtime_error("Failed to delete customer from database");
    }

    bool found = false;
    for (int i = 0; customers.size(); ++i) {
      if (customers.at(i).customer_id == customer_id) {
        customers.erase(customers.begin() + i);
        found = true;
        break;
      }
    }
    if (found) {
      cout << "Customer deleted successfully!" << endl;
    } else {
      cout << "Couldn't find the specified customer!" << endl;
    }
    return;
  }

  catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exit(1);
  }
}

void showCustomers(const vector<Customer> &customers) {
  if (customers.empty()) {
    cout << "No customers registered.\n";
    return;
  }

  cout << "\n--- Customer List ---\n";
  cout << left << setw(12) << "Customer ID" << setw(20) << "Name" << setw(30) << "Email"
       << setw(15) << "Phone" << endl;

  cout << string(77, '-') << endl;

  for (int i = customers.size() - 1; i > -1; --i) {
    const Customer &customer = customers.at(i);
    cout << left << setw(12) << customer.customer_id << setw(20) << customer.name
         << setw(30) << customer.email << setw(15) << customer.phone_number
         << endl;
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