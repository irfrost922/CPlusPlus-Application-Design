#include "RecordManager.h"
#include "Validation.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

RecordManager::RecordManager(int maximumRecords) {
    capacity = maximumRecords;
    recordCount = 0;
    records = new DatasetRecord[capacity];
}

RecordManager::~RecordManager() {
    delete[] records;
}

int RecordManager::binarySearch(const string& participantId) const {
    int left = 0;
    int right = recordCount - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;
        string middleId = records[middle].getParticipantId();

        if (middleId == participantId) {
            return middle;
        }

        if (middleId < participantId) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}

bool RecordManager::addRecord(const DatasetRecord& newRecord) {
    if (recordCount >= capacity ||
        !isValidParticipantId(newRecord.getParticipantId()) ||
        trim(newRecord.getPrimaryPlatform()).empty() ||
        newRecord.getPrimaryPlatform().find('|') != string::npos ||
        !isValidDailyHours(newRecord.getDailyHours())) {
        return false;
    }

    if (binarySearch(newRecord.getParticipantId()) != -1) {
        return false;
    }

    int insertIndex = recordCount;

    while (insertIndex > 0 &&
           records[insertIndex - 1].getParticipantId() >
               newRecord.getParticipantId()) {
        records[insertIndex] = records[insertIndex - 1];
        insertIndex--;
    }

    records[insertIndex] = newRecord;
    recordCount++;
    return true;
}

bool RecordManager::deleteRecord(const string& participantId) {
    int recordIndex = binarySearch(participantId);

    if (recordIndex == -1) {
        return false;
    }

    for (int i = recordIndex; i < recordCount - 1; i++) {
        records[i] = records[i + 1];
    }

    recordCount--;
    return true;
}

void RecordManager::displayRecords() const {
    cout << "\n=== SOCIAL MEDIA DATASET RECORDS ===" << endl;
    cout << left << setw(16) << "Participant ID"
         << setw(16) << "Daily Hours"
         << "Primary Platform" << endl;
    cout << string(52, '-') << endl;

    for (int i = 0; i < recordCount; i++) {
        records[i].display();
    }
}

double RecordManager::calculateAverageHours() const {
    if (recordCount == 0) {
        return 0.0;
    }

    double totalHours = 0.0;

    for (int i = 0; i < recordCount; i++) {
        totalHours += records[i].getDailyHours();
    }

    return totalHours / recordCount;
}

bool RecordManager::loadFromFile(const string& fileName) {
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        return false;
    }

    recordCount = 0;
    string line;

    while (getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream row(line);
        string id;
        string hoursText;
        string platform;

        getline(row, id, '|');
        getline(row, hoursText, '|');
        getline(row, platform);

        try {
            size_t processedCharacters = 0;
            double hours = stod(hoursText, &processedCharacters);

            if (processedCharacters != hoursText.length() ||
                !addRecord(DatasetRecord(trim(id),
                                         trim(platform),
                                         hours))) {
                cout << "Skipped invalid file row: " << line << endl;
            }
        } catch (...) {
            cout << "Skipped invalid file row: " << line << endl;
        }
    }

    return true;
}

bool RecordManager::saveToFile(const string& fileName) const {
    ofstream outputFile(fileName);

    if (!outputFile.is_open()) {
        return false;
    }

    for (int i = 0; i < recordCount; i++) {
        outputFile << records[i].getParticipantId() << "|"
                   << fixed << setprecision(1)
                   << records[i].getDailyHours() << "|"
                   << records[i].getPrimaryPlatform() << endl;
    }

    return true;
}

DatasetRecord* RecordManager::getRecordPointer(int index) {
    if (index < 0 || index >= recordCount) {
        return nullptr;
    }

    return &records[index];
}

int RecordManager::getRecordCount() const {
    return recordCount;
}
