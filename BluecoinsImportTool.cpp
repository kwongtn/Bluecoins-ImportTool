// BluecoinsImportTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BluecoinsImportTool.h"

int countEntry = 0,
	countDiscard = 0;

int main() {

	// Future feature: json file creator.
	
	while (true) {
		system("cls");
		// If json file is empty then load.
		if (properties.empty()) {
			readFile();
		}

		cout << endl;
		cout << "Json file path: \"" << jsonFilename << "\"" << endl;
		cout << "Output file path: \"" << outFilename << "\"" << endl;
		cout << endl;



		cout << "Next action?" << endl;
		int selection = mainMenu();
		system("cls");

		switch (selection) {
		case 0 : {	// Load a new json file.
			char intent;
			cout << "Are you sure you want to clear the current json configuration and load a new one? (y/n)" << endl;
			cin >> intent;
			intent = tolower(intent);

			if (intent == 'y') {
				properties.clear();
				cout << "json file cleared.";
			} else {
				cout << "No actions taken. ";
			}
			system("pause");

			break;
		}
		case 1 : {	// Set a new output file.
			fileFunc();
			break;
		}
		case 2: {
			// Outputs all properties.
			outAllProperties();
			system("pause");
			break;
		}
		case 3 : {
			// Creates a new entry.
			if (entryInput()) { //Fix functionality to request file when file is not loaded.
				if (!file) {
					fileFunc();
				}
				writeToFile();
				cout << "Written to file. ";
				countEntry++;
			} else {
				cout << "Entry discarded. ";
				countDiscard++;
			}
			system("pause");
			break;
		}
		case 4 : {
			cout << "Thank you for using. Throughout this session, you have: " << endl;
			cout << endl;
			cout << "Inserted " << countEntry << " entries." << endl;
			cout << "Discarded " << countDiscard << " entries." << endl;
			cout << endl;

			system("pause");
			exit(0);
		}

		default:
			break;
		}
	}
	
	
	//outAllProperties();



	// testbed



	return 0;
	system("pause");
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
