// BluecoinsImportTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BluecoinsImportTool.h"

ENTRY fixedEntryMenu(json, ENTRY);
ENTRY entryTemplate;

int countEntry = 0,
countDiscard = 0;

const int menusize = 10;

// Main menu for program.
int mainMenu() {
	int selection;

	struct MENU {
		int count = 0;
		string content = "";
	};
	MENU menu[menusize];

	// Define menus
	menu[0].count = 0;
	menu[0].content = "Load New Json File";
	menu[1].count = 1;
	menu[1].content = "Set New Output File";
	menu[2].count = 2;
	menu[2].content = "View All Current Categories";
	menu[3].count = 3;
	menu[3].content = "View Last Entry";
	menu[4].count = 4;
	menu[4].content = "Input New Entry";

	menu[6].count = 6;
	menu[6].content = "Toggle split entry status";
	if (splitTransac) {
		menu[6].content += " [!! Enabled !!]";
	}
	else {
		menu[6].content += " [Disabled]";
	}

	menu[7].count = 7;
	menu[7].content = "Toggle fixed entries status (WIP)";

	menu[9].count = 9;
	menu[9].content = "Exit";

	// Output menu.
	menuHeading();
	for (int j = 0; j < menusize; j++) {
		if (menu[j].content != "") {
			cout << left << setw(5) << menu[j].count << menu[j].content;
		}
		cout << endl;
	}

	cout << endl;

	// To output the status of split transaction mode if there is.
	if (splitTransac) {
		line(50, '-', true);
		cout << "- Please make sure that the date, time and title are the same." << endl;
		cout << "- Using different label sets and status for each split is not currently supported. Only the first row of those will be used for each split transaction." << endl;
		cout << "- You can only import one split transaction per csv file." << endl;
		line(50, '-', true);
	}

	cout << "Your Selection";
	selection = inputNumber<int>();

	return selection;
}

int main() {
	// Future feature: json file creator.
	introduction();

	while (true) {
		try {
			// If json file is empty then load.
			if (properties.empty()) {
				readFile();
			}
			heading("Main Menu");
			cout << "Json file path   : \"" << jsonFilename << "\"" << endl;
			cout << "Output file path : \"" << outFilename << "\"" << endl;

			int selection = mainMenu();

			switch (selection) {
				// Load a new json file.
			case 0:
			{
				heading("Reload JSON File");
				cout << "Are you sure you want to clear the current json configuration and load a new one? " << endl;

				if (decider()) {
					properties.clear();
					continue;

				}
				else {
					cout << "No actions taken. ";
					system("pause");

				}

				break;
			}
			// Set a new output file.
			case 1:
			{
				fileFunc();
				break;
			}
			// Outputs all properties.
			case 2:
			{
				outAllProperties();
				break;
			}
			// View last inputted entry.
			case 3:
			{
				heading("View Last Entry");
				if (countEntry == 0 && countDiscard == 0) {
					cout << "There are no entries inputted before this." << endl;

				}
				else {
					show_inputted(entry);

				}
				system("pause");
				break;
			}
			// Creates a new entry.
			case 4:
			{
				reset();
				int decision = entryInput(entryTemplate);
				if (decision == 0) {
					if (!file.is_open()) {
						fileFunc();
					}
					writeToFile();
					append = true;
					cout << "\nWritten to file. ";
					countEntry++;
					if (splitTransac) {
						usedSplit = true;
						entryTemplate = syncFixed(entry, entryTemplate);
					}

					system("pause");
				}
				else if (decision == 1) {
					cout << "\nEntry discarded. ";
					countDiscard++;
					system("pause");
				}
				break;
			}
			// To toggle split transaction mode
			case 6:
			{
				if (!splitTransac && usedSplit) {
					cout << "Only one split transaction can be used per CSV file. Are you sure you want to continue?" << endl;
					if (decider()) {
						splitTransac = true;
					}
					else {
						break;
					}

				}
				else if (!splitTransac) {
					splitTransac = true;
				}
				else {
					splitTransac = false;
				}
				break;
			}
			case 7:
			{
				entryTemplate = fixedEntryMenu(properties, entryTemplate);
				break;
			}

			case 9:
			{
				heading("Exit");
				cout << "Thank you for using the bluecoins import tool. Throughout this session, you have: " << endl;
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
		catch (...) {
			cout << "Congratulations! You found a bug!" << endl
				<< "Please file a bug report (issue) at the following page:" << endl
				<< "https://github.com/kwongtn/Bluecoins-ImportTool/issues" << endl << endl
				<< "Within the issue, please detail the things you were doing (steps, etc) when you encountered this bug." << endl << endl
				<< "Thank you! :D";
		}


		//outAllProperties();

		return 0;
		system("pause");
	}
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
