SOCIAL MEDIA DATASET RECORD MANAGER

Files required to compile:
  main.cpp
  DatasetRecord.cpp / DatasetRecord.h
  RecordManager.cpp / RecordManager.h
  User.cpp / User.h
  records.txt

Compile on Windows with MinGW g++:
  g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp DatasetRecord.cpp RecordManager.cpp User.cpp -o record_manager.exe

Run:
  .\record_manager.exe records.txt

The program loads records from records.txt, places them into a dynamically
allocated sorted array, and supports display, binary search, average
calculation, pointer access, and data-size display. Admin users may add,
delete, and save records. Regular users have read-only access.
