#include "customer.h"

Customer createCustomer(vector<Customer> &customers, string &name, string &email, string &password, string &phone_number) {
    try {
        string insertQuery = 
        "INSERT INTO Customers (name, email, password, phone_number) VALUES ('" + 
        name + "', '" + email + "', '" + password + "', '" + phone_number + "');";
        
        if (!g_database->insertObject(insertQuery, "Customers", CustomerCallback, &customers)) {
            throw runtime_error("Failed to create customer in database");
        }
    
        cout << "Customer " << name << " created successfully!" << endl;
        return customers.back();
    }
    catch(const exception& e) {
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
    cout << setw(12) << "Customer ID" 
         << setw(20) << "Name" 
         << setw(30) << "Email" 
         << setw(15) << "Phone" << endl;
    
    cout << string(77, '-') << endl;

    for (const Customer &customer : customers) {
        cout << setw(12) << customer.customer_id
             << setw(20) << customer.name
             << setw(30) << customer.email
             << setw(15) << customer.phone_number << endl;
    }
}

int CustomerCallback(void* data, int columns, char** values, char** column_names) {
    vector<Customer>* customers = static_cast<vector<Customer>*>(data);
    Customer customer;
    
    customer.customer_id = atoi(values[0]);
    customer.name = values[1] ? values[1] : "";
    customer.email = values[2] ? values[2] : "";
    customer.password = values[3] ? values[3] : "";
    customer.phone_number = values[4] ? values[4] : "";
    
    customers->push_back(customer);
    return 0;
}

