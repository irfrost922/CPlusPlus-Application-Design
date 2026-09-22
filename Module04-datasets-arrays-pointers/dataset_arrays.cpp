#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    const int RECORD_COUNT = 5;

    string participantIds[RECORD_COUNT];
    double dailySocialMediaHours[RECORD_COUNT];
    string primaryPlatforms[RECORD_COUNT];

    string fileName = "social_media_dopamine_productivity.csv";

    if (argc > 1) {
        fileName = argv[1];
    }

    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cout << "Error: Could not open " << fileName << endl;
        cout << "Place the CSV file in the same folder as the program," << endl;
        cout << "or enter its path when running the program." << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);  // Skip the header row.

    int recordIndex = 0;

    while (recordIndex < RECORD_COUNT && getline(inputFile, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            continue;
        }

        stringstream row(line);
        string field;
        int fieldIndex = 0;

        while (getline(row, field, ',')) {
            if (fieldIndex == 0) {
                participantIds[recordIndex] = field;
            } else if (fieldIndex == 13) {
                dailySocialMediaHours[recordIndex] = stod(field);
            } else if (fieldIndex == 15) {
                primaryPlatforms[recordIndex] = field;
            }

            fieldIndex++;
        }

        recordIndex++;
    }

    inputFile.close();

    if (recordIndex < RECORD_COUNT) {
        cout << "Error: The file contains fewer than " << RECORD_COUNT
             << " usable records." << endl;
        return 1;
    }

    cout << "\n=== SOCIAL MEDIA DATASET RECORDS ===" << endl;
    cout << left << setw(16) << "Participant"
         << setw(16) << "Daily Hours"
         << "Primary Platform" << endl;
    cout << string(48, '-') << endl;

    for (int i = 0; i < RECORD_COUNT; i++) {
        cout << left << setw(16) << participantIds[i]
             << setw(16) << fixed << setprecision(1)
             << dailySocialMediaHours[i]
             << primaryPlatforms[i] << endl;
    }

    double* hoursPointer = &dailySocialMediaHours[0];

    cout << "\nFirst participant's daily hours through pointer: "
         << *hoursPointer << endl;

    return 0;
}
