# Police Duty Schedule Management System

## Overview

The Police Duty Schedule Management System is a console-based application developed in C++. It helps manage police duty schedules by allowing users to add, search, and delete policeman records. The application stores data in a text file, providing simple file-based data persistence.

## Features

- Add new policeman records
- Search records by Policeman ID
- Delete records by Policeman ID
- Store data in a text file
- Input validation for menu selection
- Simple menu-driven interface

## Technologies Used

- C++
- File Handling
- Structures
- Standard Template Library (STL)

## Project Structure

```
Police-Duty-Schedule-Management-System/
│
├── project umar hasseb.cpp
├── police_schedule.txt
└── README.md
```

## Sample Menu

```
1. Add Record
2. Search Record
3. Delete Record
4. Exit

Enter your choice:
```

## How to Run

### Compile

```bash
g++ "project umar hasseb.cpp" -o PoliceSchedule
```

### Run

Windows

```bash
PoliceSchedule.exe
```

Linux/macOS

```bash
./PoliceSchedule
```

## Data Storage

The application stores records in:

```
police_schedule.txt
```

Each record contains:

- Policeman Name
- Policeman ID
- Duty Days
- Duty Start Time
- Duty End Time

## Learning Concepts

- Object-based data management using structures
- File handling in C++
- Input validation
- Searching algorithms
- CRUD (Create, Read, Delete) operations

## Author

Umar Ijaz Dar
