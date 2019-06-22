// BluecoinsImportTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BluecoinsImportTool.h"


int main() {
	// If json file is empty then load.
	// If output file is empty then request.
	readFile();

	// Future feature: json file creator.
	
	while (true) {
		system("cls");
		cout << "Next action?" << endl;
		int selection = mainMenu();
		system("cls");
		switch (selection) {
		case 0 : {
			// Load a new json file.
			break;
		}
		case 1 : {
			// Set a new output file.
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
			cout << entry.label;
			entryInput();
			break;
		}
		case 4 : {
			cout << "Thank you for using. Goodbye." << endl;
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
