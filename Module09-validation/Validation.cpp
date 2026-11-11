#include "Validation.h"

#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

string trim(const string& text) {
    size_t first = 0;

    while (first < text.length() &&
           isspace(static_cast<unsigned char>(text[first]))) {
        first++;
    }

    size_t last = text.length();

    while (last > first &&
           isspace(static_cast<unsigned char>(text[last - 1]))) {
        last--;
    }

    return text.substr(first, last - first);
}

bool isValidParticipantId(const string& participantId) {
    if (participantId.length() != 5 || participantId[0] != 'P') {
        return false;
    }

    for (size_t i = 1; i < participantId.length(); i++) {
        if (!isdigit(static_cast<unsigned char>(participantId[i]))) {
            return false;
        }
    }

    return true;
}

bool isValidDailyHours(double hours) {
    return isfinite(hours) && hours >= 0.0 && hours <= 24.0;
}

int readChoice(int minimum, int maximum) {
    string input;

    while (true) {
        getline(cin, input);
        input = trim(input);

        stringstream parser(input);
        int choice;
        char extraCharacter;

        if (parser >> choice && !(parser >> extraCharacter) &&
            choice >= minimum && choice <= maximum) {
            return choice;
        }

        cout << "Invalid choice. Enter a whole number from "
             << minimum << " to " << maximum << ": ";
    }
}

string readNonEmptyLine(const string& prompt, const string& fieldName) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);
        value = trim(value);

        if (value.empty()) {
            cout << "Invalid entry. " << fieldName
                 << " cannot be empty. Please try again." << endl;
        } else if (value.find('|') != string::npos) {
            cout << "Invalid entry. " << fieldName
                 << " cannot contain the | character. Please try again."
                 << endl;
        } else {
            return value;
        }
    }
}

string readParticipantId(const string& prompt) {
    string participantId;

    while (true) {
        cout << prompt;
        getline(cin, participantId);
        participantId = trim(participantId);

        if (isValidParticipantId(participantId)) {
            return participantId;
        }

        cout << "Invalid participant ID. Use P followed by exactly four "
             << "digits, such as P0009. Please try again." << endl;
    }
}

double readDailyHours(const string& prompt) {
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);
        input = trim(input);

        stringstream parser(input);
        double hours;
        char extraCharacter;

        if (parser >> hours && !(parser >> extraCharacter) &&
            isValidDailyHours(hours)) {
            return hours;
        }

        cout << "Invalid daily hours. Enter a number from 0 through 24 "
             << "without extra characters. Please try again." << endl;
    }
}
