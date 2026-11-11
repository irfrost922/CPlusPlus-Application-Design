#include "RecordManager.h"
#include "User.h"
#include "Validation.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void showDataTypeSizes() {
    cout << "\n=== C++ DATA TYPE SIZES ON THIS COMPUTER ===" << endl;
    cout << "char: " << sizeof(char) << " byte(s)" << endl;
    cout << "bool: " << sizeof(bool) << " byte(s)" << endl;
    cout << "int: " << sizeof(int) << " byte(s)" << endl;
    cout << "double: " << sizeof(double) << " byte(s)" << endl;
    cout << "string object: " << sizeof(string) << " byte(s)" << endl;
    cout << "DatasetRecord object: " << sizeof(DatasetRecord)
         << " byte(s)" << endl;
    cout << "DatasetRecord pointer: " << sizeof(DatasetRecord*)
         << " byte(s)" << endl;
}

void showMenu() {
    cout << "\n=== SOCIAL MEDIA RECORD MANAGER ===" << endl;
    cout << "1. Display All Records" << endl;
    cout << "2. Binary Search by Participant ID" << endl;
    cout << "3. Calculate Average Daily Hours" << endl;
    cout << "4. Add Record (Admin only)" << endl;
    cout << "5. Delete Record (Admin only)" << endl;
    cout << "6. Demonstrate Pointer Access" << endl;
    cout << "7. Display Data Type Sizes" << endl;
    cout << "8. Save Records to File (Admin only)" << endl;
    cout << "9. Exit" << endl;
    cout << "Choose an option: ";
}

int main(int argc, char* argv[]) {
    const int MAX_RECORDS = 100;
    string dataFile = "records.txt";

    if (argc > 1) {
        dataFile = argv[1];
    }

    RecordManager manager(MAX_RECORDS);

    if (!manager.loadFromFile(dataFile)) {
        cout << "Error: Could not open " << dataFile << endl;
        return 1;
    }

    cout << "Loaded " << manager.getRecordCount()
         << " records from " << dataFile << "." << endl;

    string username = readNonEmptyLine("Enter your username: ", "Username");

    cout << "\nChoose your role:" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Regular User" << endl;
    cout << "Choose an option: ";
    int roleChoice = readChoice(1, 2);

    Admin adminUser(username);
    RegularUser regularUser(username);
    User* currentUser;

    if (roleChoice == 1) {
        currentUser = &adminUser;
    } else {
        currentUser = &regularUser;
    }

    cout << "\nWelcome, " << currentUser->getUsername() << "!" << endl;
    cout << "Role: " << currentUser->getRoleName() << endl;

    int menuChoice = 0;

    while (menuChoice != 9) {
        showMenu();
        menuChoice = readChoice(1, 9);

        switch (menuChoice) {
            case 1:
                manager.displayRecords();
                break;

            case 2: {
                string targetId = readParticipantId(
                    "Enter the participant ID to find: ");

                int recordIndex = manager.binarySearch(targetId);

                if (recordIndex == -1) {
                    cout << "Record not found." << endl;
                } else {
                    cout << "Record found at sorted array index "
                         << recordIndex << ":" << endl;
                    manager.getRecordPointer(recordIndex)->display();
                }
                break;
            }

            case 3:
                cout << "Average daily social media use: "
                     << fixed << setprecision(2)
                     << manager.calculateAverageHours()
                     << " hours" << endl;
                break;

            case 4: {
                if (!currentUser->canModifyRecords()) {
                    cout << "Permission denied: Admin access is required."
                         << endl;
                    break;
                }

                string id = readParticipantId(
                    "Enter new participant ID: ");
                double hours = readDailyHours(
                    "Enter average daily hours (0-24): ");
                string platform = readNonEmptyLine(
                    "Enter primary platform: ", "Platform name");

                if (manager.addRecord(DatasetRecord(id, platform, hours))) {
                    cout << "Record added in sorted order." << endl;
                } else {
                    cout << "Unable to add record. Check for a duplicate ID "
                         << "or a full array." << endl;
                }
                break;
            }

            case 5: {
                if (!currentUser->canModifyRecords()) {
                    cout << "Permission denied: Admin access is required."
                         << endl;
                    break;
                }

                string id = readParticipantId(
                    "Enter participant ID to delete: ");

                if (manager.deleteRecord(id)) {
                    cout << "Record deleted." << endl;
                } else {
                    cout << "Record not found." << endl;
                }
                break;
            }

            case 6: {
                DatasetRecord* recordPointer = manager.getRecordPointer(0);

                if (recordPointer == nullptr) {
                    cout << "No record is available for pointer access."
                         << endl;
                } else {
                    cout << "Pointer address: " << recordPointer << endl;
                    cout << "First record accessed through the pointer:"
                         << endl;
                    recordPointer->display();
                }
                break;
            }

            case 7:
                showDataTypeSizes();
                break;

            case 8:
                if (!currentUser->canModifyRecords()) {
                    cout << "Permission denied: Admin access is required."
                         << endl;
                } else if (manager.saveToFile(dataFile)) {
                    cout << "Records saved to " << dataFile << "." << endl;
                } else {
                    cout << "Error: Records could not be saved." << endl;
                }
                break;

            case 9:
                cout << "Goodbye! Dynamic memory has been released." << endl;
                break;
        }
    }

    return 0;
}
