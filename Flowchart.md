```mermaid
flowchart TB
    A([Start]) --> B[Initialize Variables]
    B --> C{numStudents == 0?}
    C -->|Yes| D[/Display Welcome Message and Add Student Option/]
    C -->|No| E[/Display Welcome Message with All Options/]
    D --> F[/Enter User Choice/]
    E --> F
    F --> G{User Choice}
    G -->|1| H[/Enter Student Name and Code/]
    H --> I[/Enter Study Hours for Each Day/]
    I --> J[Calculate Totals and Averages]
    J --> K[Increment numStudents]
    K --> F
    G -->|2| L{numStudents == 0?}
    L -->|Yes| M[/Display Please add students first./]
    L -->|No| N[/Display Total Study Hours and Averages/]
    N --> O[/Print Student List/]
    O --> F
    G -->|3| P{numStudents == 0?}
    P -->|Yes| Q[/Display Please add students first./]
    P -->|No| R[Search by Name or Code]
    R --> S[/Enter Search Criteria/]
    S --> T[Search for Student]
    T --> U{Student Found?}
    U -->|Yes| V[/Display Student Details and Study Hours/]
    U -->|No| W[/Display Student not found./]
    V --> F
    W --> F
    G -->|4| X[/Display Good Bye!/]
    X --> Y([End])
    G -->|Other| Z[/Display Invalid choice. Please try again./]
    Z --> F
