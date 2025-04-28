#include "payment.h"

// Get payment by ID
bool getPaymentById(int &payment_id, Payment &payment) {
  for (Payment p : payments) {
    if (p.payment_id == payment_id) {
      payment = p;
      return true;
    }
  }
  return false;
}

bool getPaymentByBookingId(int &booking_id, Payment &payment) {
  for (Payment p : payments) {
    if (p.booking_id == booking_id) {
      payment = p;
      return true;
    }
  }
  return false;
}


// Retrieve all the payments from the database
void getPayments() {
  try {
    string query = "SELECT * FROM Payments;";
    if (!getObjects(query, PaymentCallback, &payments)) {
      throw runtime_error("Error when retrieving all the payments");
    }
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exitProgram();
  }
}

// Add payment to the database
Payment addPayment() {
  int booking_id;
  float amount;
  bool is_paid;
  cout << "Booking Id: "; cin >> booking_id;
  cout << "Amount: "; cin >> amount;
  cout << "Is Paid (1 for Yes, 0 for No): "; cin >> is_paid;
  
  if (cin.fail()) {
    showChoiceError();
    return Payment(); 
  }


  for(Payment &p : payments) {
    if (p.booking_id == booking_id) {
      cout << "Payment already exists for this booking." << endl;
      return Payment();
    }
  }

  try {
    string insertQuery =
        "INSERT INTO Payments (booking_id, amount, is_paid) VALUES (" +
        to_string(booking_id) + ", " + to_string(amount) + ", " +
        (is_paid ? "TRUE" : "FALSE") + ");";

    // Use g_database instance to call insertObject
    if (!insertObject(insertQuery, "Payments", PaymentCallback, &payments)) {
      throw runtime_error("Failed to create payment in database");
    }

    cout << "Payment of $" << amount << " received for Booking ID "
         << booking_id << endl;
    return payments.back();
  } 
  catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exitProgram();
    return Payment(); // Return an empty Payment object in case of error
  }
}

void updatePaymentStatus(int &payment_id, bool &is_paid) {
  Payment payment;
  if (!getPaymentById(payment_id, payment)) {
    cout << "Payment not found" << endl;
    return;
  }

  try {
    string updateQuery = "UPDATE Payments SET is_paid = " +
                         (is_paid ? "TRUE" : "FALSE") + " WHERE payment_id = " +
                         to_string(payment_id) + ";";

    if (!updateObject(updateQuery)) {
      throw runtime_error("Failed to update payment status in database");
    }

    cout << "Payment status updated successfully!" << endl;
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exitProgram();
  }
}

void showPaymentByBookingId(){
  int booking_id;
  cout << "Enter the booking id: ";
  cin >> booking_id;
  if (cin.fail()) {
    showChoiceError();
    return;
  }

  Payment payment;
  if(!getPaymentByBookingId(booking_id, payment)){
      cout << "Payment not found for this booking." << endl;
      return;
  }
  
  cout << "Payment ID: " << payment.payment_id << endl;
  cout << "Booking ID: " << payment.booking_id << endl;
  cout << "Amount: $" << payment.amount << endl;
  cout << "Payment Date: " << payment.payment_date << endl;
  cout << "Status: " << (payment.is_paid ? "Paid" : "Unpaid") << endl;
}


// Show payment history
void showPaymentHistory() {
  if (payments.empty()) {
    cout << "No payments recorded.\n";
    return;
  }

  cout << "\n--- Payment History ---\n";
  cout << setw(10) << "Payment ID" << setw(10) << "Booking ID" << setw(10)
       << "Amount" << setw(15) << "Payment Date" << setw(10) << "Status"
       << endl;
  for (int i = payments.size() - 1; i > -1; --i) {
    const Payment &payment = payments.at(i);
    cout << setw(10) << payment.payment_id << 
            setw(10) << payment.booking_id << 
            setw(10) << payment.amount << setw(15) << payment.payment_date << 
            setw(10) << (payment.is_paid ? "Paid" : "Unpaid") << endl;
  }
}

// ! Add other invoice informations like customer name, room type, etc.
void generateInvoice() {
  int payment_id;
  cout << "Enter the payment id: ";
  cin >> payment_id;

  if(cin.fail()) {
    showChoiceError();
    return;
  }

  Payment payment;
  Booking booking;
  Customer customer;
  Room room;
  RoomType roomtype;
  Staff staff;

  if (!getPaymentById(payment_id, payment)) {
    cout << "Payment not found" << endl;
    return;
  }
  if (!getBookingById(payment.booking_id, booking)) {
    cout << "Booking not found" << endl;
    return;
  }
  if(!getRoomById(booking.room_id, room)){
    cout << "Room not found " << endl;
    return;
  }
  if(!getRoomTypeById(room.room_type_id, roomtype)){
     cout << "Room Type not found " << endl;
     return;
  }

  if(!getCustomerById(booking.customer_id, customer)){
    cout << "Customer not found" << endl;
  }

  if (!getStaffById(booking.staff_id, staff)) {
    cout << "Staff not found" << endl;
    return;
  }

  cout << "----- Invoice -----" << endl;
  cout << "(Service Provider) Staff ID: " << booking.staff_id << endl;
  cout << "Staff Name: " << staff.name << endl;
  cout << "Staff Email: " << staff.email << endl << endl << endl;

  cout << "Payment ID: " << payment.payment_id << endl;
  cout << "Booking ID: " << payment.booking_id << endl;
  cout << "Booking Date " << booking.booking_date << endl << endl << endl;

  cout << "----- Customer Details -----" << endl;
  cout << "Customer ID: " << booking.customer_id << endl;
  cout << "Customer Name: " << customre.name << endl;
  cout << "Customer Email: " << customer.email << endl << endl << endl;

  cout << "----- Room Details -----" << endl; 
  cout << "Room Number: " << room.room_number << endl;
  cout << "Room Type: " << roomtype.type_name << endl << endl << endl;


  cout << "Check-in Date: " << booking.check_in_date << endl;
  cout << "Check-out Date: " << booking.check_out_date << endl << endl << endl;

  
  cout << "Total Price: $" << payment.amount << endl;
  cout << "Payment Date: " << payment.payment_date << endl;
  cout << "Status: " << (payment.is_paid ? "Paid" : "Unpaid") << endl;
}



int PaymentCallback(void *data, int columns, char **values,
                    char **column_names) {
  vector<Payment> *payments = static_cast<vector<Payment> *>(data);

  Payment payment;

  payment.payment_id = values[0] ? atoi(values[0]) : -1;
  payment.booking_id = values[1] ? atoi(values[1]) : -1;
  payment.amount = values[2] ? atof(values[2]) : -1;
  payment.payment_date = values[3] ? values[3] : "";
  payment.is_paid = (values[4] != nullptr && strcmp(values[4], "1") == 0); // check if the value is not null and if it is equal to "1" (true) or "0" (false)

  payments->push_back(payment);

  return 0;
}
