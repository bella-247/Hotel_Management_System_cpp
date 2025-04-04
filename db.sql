CREATE DATABASE IF NOT EXISTS HOTEL_MANAGEMENT_SYSTEM;
USE HOTEL_MANAGEMENT_SYSTEM;

DROP TABLE IF EXISTS Customers;
CREATE TABLE Customers (
    customer_id INT AUTO_INCREMENT PRIMARY KEY, -- Unique identifier for each customer
    name VARCHAR(100) NOT NULL,                 -- Customer's full name
    email VARCHAR(100) NOT NULL,
    password VARCHAR(100) NOT NULL,
    phone_number VARCHAR(20) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP -- Date and time the customer was added
);

DROP TABLE IF EXISTS Staff;
CREATE TABLE Staff (
    staff_id INT AUTO_INCREMENT PRIMARY KEY,     -- Unique identifier for each staff member
    name VARCHAR(100) NOT NULL,                   -- Staff name
    role VARCHAR(50) NOT NULL,                    -- Staff role (e.g., Admin, Receptionist, Housekeeping)
    phone_number VARCHAR(20) NOT NULL,
    email VARCHAR(100) NOT NULL,
    password VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Date and time the staff record was created
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP -- Record update timestamp
);

DROP TABLE IF EXISTS RoomTypes;
CREATE TABLE RoomTypes (
    room_type_id INT AUTO_INCREMENT PRIMARY KEY,  -- Unique identifier for each room type
    type_name VARCHAR(50) NOT NULL,               -- Room type name (e.g., Single, Double, Suite)
	price DECIMAL(10, 2) NOT NULL,					-- Price of the room types
    num_of_rooms INT NOT NULL,
    rooms_range_start INT NOT NULL UNIQUE,
    rooms_range_end INT NOT NULL UNIQUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP -- Date and time the room type was added
);

DROP TABLE IF EXISTS Rooms;
CREATE TABLE Rooms (
    room_id INT AUTO_INCREMENT PRIMARY KEY,     -- Unique identifier for each room
    room_number INT NOT NULL UNIQUE,     -- Room number (should be unique)
    room_type_id INT NOT NULL,                   -- Foreign key linking to Room_Types table
    customer_id INT DEFAULT NULL UNIQUE,
    is_available BOOLEAN DEFAULT TRUE, -- Room status
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Date and time the room was added
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id) ON DELETE SET NULL,
    FOREIGN KEY (room_type_id) REFERENCES RoomTypes(room_type_id) ON DELETE RESTRICT
);

DROP TABLE IF EXISTS Bookings;
CREATE TABLE Bookings (
    booking_id INT AUTO_INCREMENT PRIMARY KEY,   -- Unique identifier for each booking
    customer_id INT NOT NULL,                    -- Foreign key linking to Customers table
    room_id INT NOT NULL,                        -- Foreign key linking to Rooms table
    staff_id INT,                                -- Foreign key linking to Staffs table (optional)
    check_in DATE NOT NULL,                      -- Check-in date for the booking
    check_out DATE NOT NULL,                     -- Check-out date for the booking
    booking_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Date and time the booking was made
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id) ON DELETE CASCADE, -- FK constraint for customer
    FOREIGN KEY (room_id) REFERENCES Rooms(room_id) ON DELETE CASCADE, -- FK constraint for room
    FOREIGN KEY (staff_id) REFERENCES Staff(staff_id) ON DELETE SET NULL, -- FK constraint for staff (optional)
    CONSTRAINT unique_booking UNIQUE (room_id, check_in) -- Prevent double booking a room
);

DROP TABLE IF EXISTS Payments;
CREATE TABLE Payments (
    payment_id INT AUTO_INCREMENT PRIMARY KEY,   -- Unique identifier for each payment
    booking_id INT NOT NULL,                     -- Foreign key linking to Bookings table
    amount DECIMAL(10, 2) NOT NULL,               -- Amount paid for the booking
    payment_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Date and time the payment was made
    FOREIGN KEY (booking_id) REFERENCES Bookings(booking_id) ON DELETE CASCADE -- FK constraint for booking
);





-- Deletion Query

-- DROP TABLE IF EXISTS payments; 
-- DROP TABLE IF EXISTS bookings;
-- DROP TABLE IF EXISTS staffs;
-- DROP TABLE IF EXISTS rooms;
-- DROP TABLE IF EXISTS customers;
-- DROP TABLE IF EXISTS room_types;