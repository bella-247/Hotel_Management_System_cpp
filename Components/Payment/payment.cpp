#include "payment.h"


bool getPaymentById(int &payment_id, Payment &payment) {
    for(Payment payment : payments) {
        if(payment.payment_id == payment_id) {
            return true;
        }
    }
    return false;
}

void getPayments() {
    try {
        string query = "SELECT * FROM Payments;";
        if (!getObjects(query, PaymentCallback, &payments)) {
            throw runtime_error("Error when retrieving all the payments");
        }
    }
    catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
        exit(1);
    }
}

Payment addPayment(int &booking_id, float &amount, bool &is_paid) {
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
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    exit(1);
  }
}

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

void generateInvoice(int &payment_id) {
    cout << "Invoice for payment ID " << payment_id << endl;
    Payment payment;
    Booking booking;
    Customer customer;
    Room room;
    RoomType roomtype;
    Staff staff;
    
    if(!getPaymentById(payment_id, payment)){
        cout << "Payment not found" << endl;
        return;
    }
    cout << "----------------------" << endl;

    booking.booking_id = payment.booking_id;
    customer.customer_id = payment.booking_id;
    staff.staff_id = payment.booking_id;
    room.room_id = payment.booking_id;
    roomtype.room_type_id = payment.booking_id;
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
