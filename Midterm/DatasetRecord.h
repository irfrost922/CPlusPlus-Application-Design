#ifndef DATASETRECORD_H
#define DATASETRECORD_H

#include <string>

class DatasetRecord {
private:
    std::string participantId;
    std::string primaryPlatform;
    double dailyHours;

public:
    DatasetRecord();
    DatasetRecord(const std::string& id,
                  const std::string& platform,
                  double hours);

    std::string getParticipantId() const;
    std::string getPrimaryPlatform() const;
    double getDailyHours() const;
    void display() const;
};

#endif
