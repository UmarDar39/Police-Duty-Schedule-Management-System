#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Structure to store policeman's information
struct Policeman {
    string name;
    int id;
    string dutyDays;
    string dutyStartTime;
    string dutyEndTime;
};

// Turn a record into one '|'-delimited line (safe even if name has spaces)
string toLine(const Policeman& r) {
    ostringstream oss;
    oss << r.name << "|" << r.id << "|" << r.dutyDays << "|"
        << r.dutyStartTime << "|" << r.dutyEndTime;
    return oss.str();
}

// Parse one '|'-delimited line back into a record. Returns false if malformed.
bool fromLine(const string& line, Policeman& r) {
    stringstream ss(line);
    string idStr;
    if (!getline(ss, r.name, '|'))          return false;
    if (!getline(ss, idStr, '|'))           return false;
    if (!getline(ss, r.dutyDays, '|'))      return false;
    if (!getline(ss, r.dutyStartTime, '|')) return false;
    if (!getline(ss, r.dutyEndTime, '|'))   return false;
    try {
        r.id = stoi(idStr);
    } catch (...) {
        return false;
    }
    return true;
}

// Function to add a new record to the file
void addRecord(const Policeman& record) {
    ofstream outFile("police_schedule.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    outFile << toLine(record) << endl;
    outFile.close();
}

// Function to generate a nicely formatted, human-readable report
// from all records currently stored in police_schedule.txt
void generateReport() {
    ifstream inFile("police_schedule.txt");
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    ofstream reportFile("police_schedule_report.txt");
    if (!reportFile) {
        cerr << "Error opening report file for writing." << endl;
        return;
    }

    reportFile << "==============================================\n";
    reportFile << "           POLICE DUTY SCHEDULE REPORT\n";
    reportFile << "==============================================\n\n";

    string line;
    Policeman record;
    int count = 0;
    while (getline(inFile, line)) {
        if (line.empty() || !fromLine(line, record)) continue;
        count++;
        reportFile << "Record #" << count << "\n";
        reportFile << "  Name            : " << record.name << "\n";
        reportFile << "  ID              : " << record.id << "\n";
        reportFile << "  Duty Days       : " << record.dutyDays << "\n";
        reportFile << "  Duty Start Time : " << record.dutyStartTime << "\n";
        reportFile << "  Duty End Time   : " << record.dutyEndTime << "\n";
        reportFile << "----------------------------------------------\n";
    }

    if (count == 0) {
        reportFile << "No records found.\n";
    } else {
        reportFile << "\nTotal Policemen on Record: " << count << "\n";
    }

    inFile.close();
    reportFile.close();
}

// Function to search for a specific policeman's schedule
void searchRecord() {
    ifstream inFile("police_schedule.txt");
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    int searchId;
    cout << "Enter Policeman's ID to search: ";
    cin >> searchId;

    string line;
    Policeman record;
    while (getline(inFile, line)) {
        if (line.empty() || !fromLine(line, record)) continue;
        if (record.id == searchId) {
            cout << "Policeman found:" << endl;
            cout << "Name: " << record.name << endl;
            cout << "ID: " << record.id << endl;
            cout << "Duty Days: " << record.dutyDays << endl;
            cout << "Duty Start Time: " << record.dutyStartTime << endl;
            cout << "Duty End Time: " << record.dutyEndTime << endl;
            return;
        }
    }
    cout << "Policeman with ID " << searchId << " not found." << endl;
}

// Function to delete a specific policeman's data
void deleteRecord() {
    ifstream inFile("police_schedule.txt");
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    int deleteId;
    cout << "Enter Policeman's ID to delete: ";
    cin >> deleteId;

    vector<string> lines;
    string line;
    Policeman record;
    bool found = false;
    while (getline(inFile, line)) {
        if (line.empty() || !fromLine(line, record)) continue;
        if (record.id != deleteId) {
            lines.push_back(line);
        } else {
            found = true;
        }
    }
    inFile.close();

    ofstream outFile("police_schedule.txt");
    for (const string& l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    if (found)
        cout << "Policeman with ID " << deleteId << " deleted successfully." << endl;
    else
        cout << "Policeman with ID " << deleteId << " not found." << endl;
}

int main() {
    int choice;
    Policeman newRecord;
    do {
        cout << "1. Add Record\n2. Search Record\n3. Delete Record\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                cin.ignore(); // clear leftover newline before getline
                cout << "Enter Policeman's Name: ";
                getline(cin, newRecord.name);
                cout << "Enter Policeman's ID: ";
                cin >> newRecord.id;
                cout << "Enter Duty Days: ";
                cin >> newRecord.dutyDays;
                cout << "Enter Duty Start Time: ";
                cin >> newRecord.dutyStartTime;
                cout << "Enter Duty End Time: ";
                cin >> newRecord.dutyEndTime;
                addRecord(newRecord);
                generateReport();
                cout << "Record added successfully." << endl;
                cout << "A readable report has been saved to police_schedule_report.txt" << endl;
                break;
            }
            case 2:
                searchRecord();
                break;
            case 3:
                deleteRecord();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 4);
    return 0;
}
