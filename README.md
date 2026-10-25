# C++ Library Management System

A command-line application demonstrating dynamic memory management and complete CRUD operations in C++. 

### Core Architecture
*   **Data Structures:** Utilizes standard C++ vectors for dynamic, resizable storage of custom `LibraryItem` structs.
*   **Function Overloading:** Implements overloaded insertion and display functions to handle variable parameter data types (searching by integer ID vs. Author string).
*   **State Management:** Features complete inventory tracking, including checkout/check-in decrementing logic and automated input stream resetting.

### Tech Stack
*   **Language:** C++ (Standard Template Library)
*   **Environment:** Windows (PowerShell), GCC Compiler / MinGW

### How to Run
Compile using g++ and execute the output binary:
> g++ main.cpp -o library_manager.exe
> .\library_manager.exe
