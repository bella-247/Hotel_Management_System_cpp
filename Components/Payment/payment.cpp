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
  
  try {
    string insertQuery =
        "INSERT INTO Payments (booking_id, amount, is_paid) VALUES (" +
        to_string(booking_id) + ", " + to_string(amount) + ", " +
        (is_paid ? "1" : "0") + ");";

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

//! Update payment status in the database
// void updatePaymentStatus(int &payment_id, bool &is_paid) {
//   try {
//     string updateQuery = "UPDATE Payments SET is_paid = " +
//                          (is_paid ? "1" : "0") + " WHERE payment_id = " +
//                          to_string(payment_id) + ";";

//     if (!updateObject(updateQuery)) {
//       throw runtime_error("Failed to update payment status in database");
//     }

//     cout << "Payment status updated successfully!" << endl;
//   } catch (const exception &e) {
//     cout << "Error: " << e.what() << endl;
//     exitProgram();
//   }
// }

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
    cout << setw(10) << payment.payment_id << setw(10) << payment.booking_id
         << setw(10) << payment.amount << setw(15) << payment.payment_date
         << setw(10) << (payment.is_paid ? "Paid" : "Unpaid") << endl;
  }
}

// ! Add other invoice informations like customer name, room type, etc.
void generateInvoice(int &payment_id) {
  cout << "Invoice for payment ID: " << payment_id << endl;
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
  cout << "----------------------" << endl;

  cout << "Payment ID: " << payment.payment_id << endl;
  cout << "Booking ID: " << payment.booking_id << endl;
  cout << "Amount: $" << payment.amount << endl;
  cout << "Payment Date: " << payment.payment_date << endl;
  cout << "Status: " << (payment.is_paid ? "Paid" : "Unpaid") << endl;
}

int PaymentCallback(void *data, int columns, char **values,
                    char **column_names) {
  vector<Payment> *payments = static_cast<vector<Payment> *>(data);

  Payment payment;

  payment.payment_id = atoi(values[0]);
  payment.booking_id = atoi(values[1]);
  payment.amount = atof(values[2]);
  payment.payment_date = values[3];

  payment.is_paid =
      (values[4] != nullptr &&
       strcmp(values[4], "1") == 0); // check if the value is not null and if it
                                     // is equal to "1" (true) or "0" (false)
  payments->push_back(payment);

  return 0;
}
