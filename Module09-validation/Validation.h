#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>

std::string trim(const std::string& text);
bool isValidParticipantId(const std::string& participantId);
bool isValidDailyHours(double hours);

int readChoice(int minimum, int maximum);
std::string readNonEmptyLine(const std::string& prompt,
                             const std::string& fieldName);
std::string readParticipantId(const std::string& prompt);
double readDailyHours(const std::string& prompt);

#endif
