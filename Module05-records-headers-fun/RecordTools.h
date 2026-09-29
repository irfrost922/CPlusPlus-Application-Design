#ifndef RECORDTOOLS_H
#define RECORDTOOLS_H

#include <string>

const int MAX_RECORDS = 10;

bool addRecord(std::string participantIds[],
               double dailySocialMediaHours[],
               std::string primaryPlatforms[],
               int& recordCount,
               const std::string& participantId,
               double dailyHours,
               const std::string& primaryPlatform);

void displayRecords(const std::string participantIds[],
                    const double dailySocialMediaHours[],
                    const std::string primaryPlatforms[],
                    int recordCount);

double calculateAverageHours(const double dailySocialMediaHours[],
                             int recordCount);

#endif
