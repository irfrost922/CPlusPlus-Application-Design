#include <iostream>
#include <limits>

using namespace std;

void browseDatasets() {
    cout << "\nDataset browser selected." << endl;
}

void searchDatasets() {
    cout << "\nDataset search selected." << endl;
}

void browseTrees() {
    cout << "\nTree browser selected." << endl;
}

void inspectEvent() {
    cout << "\nEvent inspector selected." << endl;
}

void visualizeValues() {
    cout << "\nValue visualization selected." << endl;
}

int main() {
    int choice = 0;

    while (choice != 6) {
        cout << "\n=== ATLAS DATA EXPLORER ===" << endl;
        cout << "1. Browse Datasets" << endl;
        cout << "2. Search Datasets" << endl;
        cout << "3. Browse Trees" << endl;
        cout << "4. Inspect an Event" << endl;
        cout << "5. Visualize Values" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            cout << "Invalid input. Please enter a number from 1 to 6." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                browseDatasets();
                break;
            case 2:
                searchDatasets();
                break;
            case 3:
                browseTrees();
                break;
            case 4:
                inspectEvent();
                break;
            case 5:
                visualizeValues();
                break;
            case 6:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 6." << endl;
        }
    }

    return 0;
}
