flowchart TB
    A([Start]) --> B[Initialize Variables]
    B --> C[Display Welcome Message]
    C --> D{User Chooses Menu Option}
    
    D -->|1| E[Book a Room]
    D -->|2| F[Check Room Availability]
    D -->|3| G[Display Room Details]
    D -->|4| H[Display Users List]
    D -->|5| I[Search Users by ID]
    D -->|6| J[Leave Room]
    D -->|7| K[Exit Program]
    
    E --> L[Enter Room Number to Book]
    L --> M{Room Number Valid?}
    M -->|Yes| N[Is Room Available?]
    M -->|No| O[Prompt for Valid Room Number]
    
    N -->|Yes| P[Register User Information]
    P --> Q[Update Room Reservation and Availability]
    Q --> R[Show Successful Booking Message]
    R --> D
    
    N -->|No| S[Show Room Already Booked Message]
    S --> L
    
    O --> L
    
    F --> T[Display Available Rooms]
    T --> D
    
    G --> U[Display Room Types, Range, Price, Status]
    U --> D
    
    H --> V[Display List of All Users]
    V --> D
    
    I --> W[Enter User ID]
    W --> X{User Found?}
    X -->|Yes| Y[Display User Details]
    X -->|No| Z[Show User Not Found Message]
    Z --> D
    Y --> D
    
    J --> AA[Enter Room Number to Leave]
    AA --> AB{Room Number Valid?}
    AB -->|Yes| AC[Mark Room as Available]
    AC --> AD[Show Successful Room Vacancy Message]
    AD --> D
    
    AB -->|No| AE[Show Invalid Room Number Message]
    AE --> AA
    
    K --> AF[Display Goodbye Message]
    AF --> AG([End])
    
    D -->|Other| AH[Display Invalid Choice Message]
    AH --> D
