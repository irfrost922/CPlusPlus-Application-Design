#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include "DatasetRecord.h"

#include <string>

class RecordManager {
private:
    DatasetRecord* records;
    int recordCount;
    int capacity;

public:
    RecordManager(int maximumRecords);
    ~RecordManager();

    bool addRecord(const DatasetRecord& newRecord);
    bool deleteRecord(const std::string& participantId);
    int binarySearch(const std::string& participantId) const;
    void displayRecords() const;
    double calculateAverageHours() const;
    bool loadFromFile(const std::string& fileName);
    bool saveToFile(const std::string& fileName) const;
    DatasetRecord* getRecordPointer(int index);
    int getRecordCount() const;
};

#endif
