<<<<<<< HEAD
# Hotel_Management_System_cpp
=======
# Hotel Reservation System

This project is a **C++ Hotel Reservation System** designed to handle room bookings, manage room availability, display user details, and more. The program is interactive and user-friendly, suitable for educational purposes or as a starting point for a more advanced hotel management application.

## Features

- **Room Booking**: Users can book rooms by specifying room numbers.
- **Room Availability Check**: Displays the available and reserved rooms.
- **Room Details**: Shows room types, their prices, and availability.
- **User Management**: Tracks users who have booked rooms, including their details (name, ID, and phone number).
- **Room Leaving**: Allows users to vacate rooms when their stay ends.
- **Search Functionality**: Find user details by ID.
- **Menu System**: Provides a clean and intuitive menu for navigation.

## Technologies Used

- **Programming Language**: C++
- **Libraries**:
  - `<iostream>`: For input/output operations.
  - `<iomanip>`: For formatting output.
  - `<string>`: For string manipulation

## Room Types and Pricing

| Room Type  | Price (ETB) | Total Rooms |  
|------------|-------------|-------------|  
| Single     | 1500        | 50          |  
| Double     | 2500        | 30          |  
| Family     | 5000        | 10          |  
| Deluxe     | 8000        | 7           |  
| Suite      | 10000       | 3           |  

## How to Run

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/hotel-management-system.git
   cd hotel-management-system

2. **Compile the Program**:  
   Ensure you have a C++ compiler installed (e.g., GCC or MinGW). Use the following command to compile the program:  
   ```bash
   g++ -o hotel_management main.cpp

3. **Run the Program**
    ./main

4. **Interact with the Program**
    Follow the menu on the screen to navigate and use the features of the system


## Code Snippet
```C++
int showMenu() {
int choice;

cout << "\n********** Hotel Menu **********\n";
cout << "1. Book a Room\n";
cout << "2. Check Room Availability\n";
cout << "3. Display Room Details\n";
cout << "4. Display Users List\n";
cout << "5. Search users by ID\n";
cout << "6. Leave room\n";
cout << "7. Exit\n";
cout << "Enter your choice: ";
cin >> choice;

return choice;
}
```


## Sample Usage
When you run the program, you will see the hotel menu displayed on the screen. You can

1. Select option 1 to book a room.
2. Enter the room number and your details (name, ID, phone number).
3. Use option 2 to check room availability.
4. Use option 6 to vacate a room when the stay ends.

## Potential Enhancements
This program is designed as a starting point. Here are some ideas for future development:

1. **Implementing a Graphical User Interface (GUI)**: Utilize libraries like Qt or wxWidgets to create a user-friendly interface for improved user experience.
2. **Database Integration**: Use a database management system like MySQL or SQLite to store user and room data persistently, enabling data retrieval and manipulation.
3. **Online Payment Gateway**: Integrate a payment gateway API (e.g., PayPal, Stripe) to support online payments for room bookings, enhancing the overall user experience.
4. **Room Service and Amenities**: Expand the system to include room service and amenities management, allowing users to request services and track their expenses.
5. **Staff Management**: Develop a staff management module to track employee details, roles, and responsibilities, streamlining hotel operations.
6. **Reporting and Analytics**: Implement a reporting system to provide insights into hotel occupancy, revenue, and customer behavior, aiding in data-driven decision-making.
7. **Security Enhancements**: Implement robust security measures, such as encryption and access controls, to protect sensitive user data and prevent unauthorized access.


## Group Members
    1. Abel Mekonen
    2. Abel Birhane
    3. Abraham Teramed
    4. Addis Shiferaw
    5. Abenezer Shiferaw
    6. Addisalem Hailay


## License 
This project is for **academic** and educational purpose only. **All rights reserved.**


## Acknowledgments
Thanks to our instructor **Fedlu Nur Hussein**  for providing the opportunity to work on this project




## Sample OutPut Images

![Output image 1](<./Output Screenshots/image 1.png>)
![Output image 1](<./Output Screenshots/image 2.png>)
![Output image 1](<./Output Screenshots/image 3.png>)
![Output image 1](<./Output Screenshots/image 4.png>)
![Output image 1](<./Output Screenshots/image 5.png>)
![Output image 1](<./Output Screenshots/image 6.png>)
>>>>>>> 337d420e165e18a203398a37a3f308c2b17a8196
