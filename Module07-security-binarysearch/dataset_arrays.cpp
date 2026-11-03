#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "RecordTools.h"
#include "UserRoles.h"

using namespace std;

int readChoice(int minimum, int maximum) {
    int choice;

    while (!(cin >> choice) || choice < minimum || choice > maximum) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Enter a number from "
             << minimum << " to " << maximum << ": ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int loadRecords(const string& fileName,
                string participantIds[],
                double dailySocialMediaHours[],
                string primaryPlatforms[]) {
    const int RECORDS_TO_LOAD = 5;
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        return -1;
    }

    string line;
    getline(inputFile, line);
    int recordCount = 0;

    while (recordCount < RECORDS_TO_LOAD && getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            continue;
        }

        stringstream row(line);
        string field;
        int fieldIndex = 0;
        string participantId;
        double dailyHours = 0.0;
        string primaryPlatform;

        while (getline(row, field, ',')) {
            if (fieldIndex == 0) {
                participantId = field;
            } else if (fieldIndex == 13) {
                dailyHours = stod(field);
            } else if (fieldIndex == 15) {
                primaryPlatform = field;
            }

            fieldIndex++;
        }

        addRecord(participantIds,
                  dailySocialMediaHours,
                  primaryPlatforms,
                  recordCount,
                  participantId,
                  dailyHours,
                  primaryPlatform);
    }

    return recordCount;
}

void searchForRecord(const string participantIds[],
                     const double dailySocialMediaHours[],
                     const string primaryPlatforms[],
                     int recordCount) {
    string targetId;
    cout << "Enter the participant ID to find: ";
    getline(cin, targetId);

    int recordIndex = binarySearchById(participantIds,
                                       recordCount,
                                       targetId);

    if (recordIndex == -1) {
        cout << "Record not found." << endl;
        return;
    }

    cout << "\nRecord found:" << endl;
    cout << "Participant ID: " << participantIds[recordIndex] << endl;
    cout << "Daily Hours: " << fixed << setprecision(1)
         << dailySocialMediaHours[recordIndex] << endl;
    cout << "Primary Platform: " << primaryPlatforms[recordIndex] << endl;
}

int main(int argc, char* argv[]) {
    string participantIds[MAX_RECORDS];
    double dailySocialMediaHours[MAX_RECORDS];
    string primaryPlatforms[MAX_RECORDS];

    string fileName = "social_media_dopamine_productivity.csv";

    if (argc > 1) {
        fileName = argv[1];
    }

    int recordCount = loadRecords(fileName,
                                  participantIds,
                                  dailySocialMediaHours,
                                  primaryPlatforms);

    if (recordCount == -1) {
        cout << "Error: Could not open " << fileName << endl;
        return 1;
    }

    if (recordCount == 0) {
        cout << "Error: No usable records were found." << endl;
        return 1;
    }

    string username;
    cout << "Enter your username: ";
    getline(cin, username);

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

    while (menuChoice != 6) {
        cout << "\n=== DATASET RECORD MENU ===" << endl;
        cout << "1. Display Records" << endl;
        cout << "2. Search by Participant ID" << endl;
        cout << "3. Calculate Average Daily Hours" << endl;
        cout << "4. Add Record (Admin only)" << endl;
        cout << "5. Delete Record (Admin only)" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";
        menuChoice = readChoice(1, 6);

        switch (menuChoice) {
            case 1:
                displayRecords(participantIds,
                               dailySocialMediaHours,
                               primaryPlatforms,
                               recordCount);
                break;

            case 2:
                searchForRecord(participantIds,
                                dailySocialMediaHours,
                                primaryPlatforms,
                                recordCount);
                break;

            case 3:
                cout << "Average daily social media use: "
                     << fixed << setprecision(1)
                     << calculateAverageHours(dailySocialMediaHours,
                                              recordCount)
                     << " hours" << endl;
                break;

            case 4: {
                if (!currentUser->canModifyRecords()) {
                    cout << "Permission denied. Admin access is required."
                         << endl;
                    break;
                }

                string newId;
                string newPlatform;
                double newHours;

                cout << "Enter the new participant ID: ";
                getline(cin, newId);
                cout << "Enter average daily social media hours: ";

                while (!(cin >> newHours) || newHours < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter a nonnegative number: ";
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter the primary platform: ";
                getline(cin, newPlatform);

                if (addRecord(participantIds,
                              dailySocialMediaHours,
                              primaryPlatforms,
                              recordCount,
                              newId,
                              newHours,
                              newPlatform)) {
                    cout << "Record added in sorted order." << endl;
                } else {
                    cout << "Record could not be added. The ID may already "
                         << "exist, or the array may be full." << endl;
                }
                break;
            }

            case 5: {
                if (!currentUser->canModifyRecords()) {
                    cout << "Permission denied. Admin access is required."
                         << endl;
                    break;
                }

                string idToDelete;
                cout << "Enter the participant ID to delete: ";
                getline(cin, idToDelete);

                if (deleteRecord(participantIds,
                                 dailySocialMediaHours,
                                 primaryPlatforms,
                                 recordCount,
                                 idToDelete)) {
                    cout << "Record deleted." << endl;
                } else {
                    cout << "Record not found." << endl;
                }
                break;
            }

            case 6:
                cout << "Goodbye!" << endl;
                break;
        }
    }

    return 0;
}
