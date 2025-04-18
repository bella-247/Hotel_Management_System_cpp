-- can be used in sqlite
CREATE TABLE IF NOT EXISTS Payments (
    payment_id INTEGER PRIMARY KEY AUTOINCREMENT,
    amount REAL NOT NULL,
    payment_date TEXT NOT NULL,
    payment_method TEXT NOT NULL,
    name TEXT NOT NULL,
    is_paid INTEGER NOT NULL CHECK (is_paid IN (0, 1))
);

INSERT INTO Payments (amount, payment_date, payment_method, name, is_paid)
VALUES (2000.0, '2025-04-18', 'Cash', 'selamawit', 1);
