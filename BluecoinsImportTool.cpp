// BluecoinsImportTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BluecoinsImportTool.h"

int countEntry = 0,
countDiscard = 0;

int main() {

	// Future feature: json file creator.

	pause();
	while (true) {
		// If json file is empty then load.
		if (properties.empty()) {
			readFile();
		}
		heading("Please make sure that your json file is updated to the latest format.");

		cout << endl;
		cout << "Json file path: \"" << jsonFilename << "\"" << endl;
		cout << "Output file path: \"" << outFilename << "\"" << endl;
		cout << endl;

		cout << "Next action?" << endl;
		int selection = mainMenu();
		system("cls");

		switch (selection) {
			// Load a new json file.
		case 0:
		{
			cout << "Are you sure you want to clear the current json configuration and load a new one? " << endl;

			if (decider()) {
				properties.clear();
				cout << "json file cleared. " << endl;
				readFile();
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
			system("pause");
			break;
		}
		// View last inputted entry.
		case 3:
		{
			if (countEntry == 0 && countDiscard == 0) {
				cout << "There are no entries inputted before this." << endl;

			}
			else {
				inputted();

			}
			system("pause");
			break;
		}
		// Creates a new entry.
		case 4:
		{
			reset();
			if (entryInput()) {
				if (!file.is_open()) {
					fileFunc();
				}
				writeToFile();
				append = true;
				cout << "Written to file. ";
				countEntry++;
			}
			else {
				cout << "Entry discarded. ";
				countDiscard++;
			}
			system("pause");
			break;
		}
		// To toggle split transaction mode
		case 6:
		{
			splitTransac = !splitTransac;
			break;
		}

		case 9:
		{
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


	//outAllProperties();

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
