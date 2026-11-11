Assignment 8: 
Compile and Run with:
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp DatasetRecord.cpp RecordManager.cpp User.cpp Validation.cpp -o record_manager
./record_manager records.txt

Where is validation used? Input validation is handled mainly in Validation.cpp and used throughout main.cpp.
- Username: readNonEmptyLine() prevents a blank username. It displays an error and asks again.
- Menu and role choices: readChoice() requires a whole number within the displayed range. It rejects text, decimals, and out-of-range numbers.
- Participant ID: readParticipantId() requires the format P followed by exactly four digits, such as P0009.
- Daily usage hours: readDailyHours() accepts only numeric values from 0 through 24. It rejects negative numbers, values above 24, text, and numbers with extra characters.
- Platform name: readNonEmptyLine() prevents an empty platform name and rejects the | character because it is used as the delimiter in records.txt.
- File input: RecordManager::loadFromFile() validates every row read from records.txt. Invalid IDs, hours, platform names, or improperly formatted rows are skipped with an error message.
- Duplicate records: RecordManager::addRecord() uses binary search to reject a participant ID that already exists.
- Array capacity: addRecord() also prevents adding records after the dynamically allocated array reaches its maximum capacity.

Assignment 9:

AI-Powered Feature: Personalized Social Media Usage Insights
The application could include an AI Usage Advisor that analyzes participant records and provides personalized suggestions based on daily social media use and preferred platforms.

The AI would identify usage patterns, flag unusually high daily usage, and generate practical recommendations. For example, a participant using TikTok for 10 hours per day might receive suggestions for setting usage limits or scheduling screen-free periods.

Data required:
- Participant ID
- Average daily social media hours
- Primary social media platform

What the user would see:
A new menu option could appear:
9. Generate AI Usage Insight
10. Exit

After selecting a participant, the program might display:
=== AI USAGE INSIGHT ===
Participant: P0003
Daily Usage: 6.5 hours
Primary Platform: TikTok

Insight:
Your daily usage is above the dataset average. Consider setting
a daily limit and taking scheduled breaks from short-form content.

Where AI fits into the architecture:
The existing RecordManager would locate the participant using binary search. The selected DatasetRecord would then be passed to a new AIAdvisor class. This class would prepare the participant’s non-sensitive data, send it to an AI service, and return the generated recommendation for display.
User Menu
    → RecordManager
    → DatasetRecord
    → AIAdvisor
    → AI Service
    → Recommendation displayed to user
