#include "RecordTools.h"

#include <iomanip>
#include <iostream>

using namespace std;

bool addRecord(string participantIds[],
               double dailySocialMediaHours[],
               string primaryPlatforms[],
               int& recordCount,
               const string& participantId,
               double dailyHours,
               const string& primaryPlatform) {
    if (recordCount >= MAX_RECORDS || dailyHours < 0) {
        return false;
    }

    participantIds[recordCount] = participantId;
    dailySocialMediaHours[recordCount] = dailyHours;
    primaryPlatforms[recordCount] = primaryPlatform;
    recordCount++;

    return true;
}

void displayRecords(const string participantIds[],
                    const double dailySocialMediaHours[],
                    const string primaryPlatforms[],
                    int recordCount) {
    cout << "\n=== SOCIAL MEDIA DATASET RECORDS ===" << endl;
    cout << left << setw(16) << "Participant"
         << setw(16) << "Daily Hours"
         << "Primary Platform" << endl;
    cout << string(48, '-') << endl;

    for (int i = 0; i < recordCount; i++) {
        cout << left << setw(16) << participantIds[i]
             << setw(16) << fixed << setprecision(1)
             << dailySocialMediaHours[i]
             << primaryPlatforms[i] << endl;
    }
}

double calculateAverageHours(const double dailySocialMediaHours[],
                             int recordCount) {
    if (recordCount == 0) {
        return 0.0;
    }

    double totalHours = 0.0;

    for (int i = 0; i < recordCount; i++) {
        totalHours += dailySocialMediaHours[i];
    }

    return totalHours / recordCount;
}
