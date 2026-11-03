#include "DatasetRecord.h"

#include <iomanip>
#include <iostream>

using namespace std;

DatasetRecord::DatasetRecord() {
    participantId = "";
    primaryPlatform = "";
    dailyHours = 0.0;
}

DatasetRecord::DatasetRecord(const string& id,
                             const string& platform,
                             double hours) {
    participantId = id;
    primaryPlatform = platform;
    dailyHours = hours;
}

string DatasetRecord::getParticipantId() const {
    return participantId;
}

string DatasetRecord::getPrimaryPlatform() const {
    return primaryPlatform;
}

double DatasetRecord::getDailyHours() const {
    return dailyHours;
}

void DatasetRecord::display() const {
    cout << left << setw(16) << participantId
         << setw(16) << fixed << setprecision(1) << dailyHours
         << primaryPlatform << endl;
}
