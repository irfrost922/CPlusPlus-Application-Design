#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "RecordTools.h"

using namespace std;

int main(int argc, char* argv[]) {
    const int RECORDS_TO_LOAD = 5;

    string participantIds[MAX_RECORDS];
    double dailySocialMediaHours[MAX_RECORDS];
    string primaryPlatforms[MAX_RECORDS];

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

        if (!participantId.empty() && !primaryPlatform.empty()) {
            addRecord(participantIds,
                      dailySocialMediaHours,
                      primaryPlatforms,
                      recordCount,
                      participantId,
                      dailyHours,
                      primaryPlatform);
        }
    }

    inputFile.close();

    if (recordCount < RECORDS_TO_LOAD) {
        cout << "Error: The file contains fewer than " << RECORDS_TO_LOAD
             << " usable records." << endl;
        return 1;
    }

    displayRecords(participantIds,
                   dailySocialMediaHours,
                   primaryPlatforms,
                   recordCount);

    double averageHours = calculateAverageHours(dailySocialMediaHours,
                                                recordCount);

    cout << "\nAverage daily social media use: "
         << fixed << setprecision(1) << averageHours << " hours" << endl;

    double* hoursPointer = &dailySocialMediaHours[0];

    cout << "\nFirst participant's daily hours through pointer: "
         << *hoursPointer << endl;

    return 0;
}
