#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class DatasetRecord {
private:
    string participantId;
    string primaryPlatform;
    double dailySocialMediaHours;

public:
    DatasetRecord(string id, string platform, double dailyHours) {
        participantId = id;
        primaryPlatform = platform;
        dailySocialMediaHours = dailyHours;
    }

    void displayRecord() const {
        cout << "Participant ID: " << participantId << endl;
        cout << "Primary Platform: " << primaryPlatform << endl;
        cout << "Daily Social Media Hours: "
             << fixed << setprecision(1) << dailySocialMediaHours << endl;
        cout << "Usage Category: " << getUsageCategory() << endl;
    }

    string getUsageCategory() const {
        if (dailySocialMediaHours >= 7.0) {
            return "High usage";
        } else if (dailySocialMediaHours >= 4.0) {
            return "Moderate usage";
        }

        return "Low usage";
    }

    string getParticipantId() const {
        return participantId;
    }

    void setDailySocialMediaHours(double newDailyHours) {
        if (newDailyHours >= 0.0) {
            dailySocialMediaHours = newDailyHours;
        }
    }
};

int main() {
    DatasetRecord record1("P0001", "Instagram", 7.5);
    DatasetRecord record2("P0002", "TikTok", 8.0);

    record2.setDailySocialMediaHours(7.8);

    cout << "=== DATASET RECORD 1 ===" << endl;
    record1.displayRecord();

    cout << "\n=== DATASET RECORD 2 ===" << endl;
    record2.displayRecord();

    cout << "\nFirst record ID through getter: "
         << record1.getParticipantId() << endl;

    return 0;
}
