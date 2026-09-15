#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    string userName = "Ian";
    string applicationName = "ATLAS Data Explorer";
    double versionNumber = 1.0;

    cout << "================================" << endl;
    cout << "  Welcome to " << applicationName << "!" << endl;
    cout << "================================" << endl;
    cout << "User: " << userName << endl;
    cout << "Version: " << fixed << setprecision(1) << versionNumber << endl;
    cout << "Explore ATLAS datasets, trees," << endl;
    cout << "events, and values in one place." << endl;
    cout << "================================" << endl;

    return 0;
}
