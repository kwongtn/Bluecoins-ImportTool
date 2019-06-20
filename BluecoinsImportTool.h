#pragma once
// BluecoinsImportTool.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

// Used to store all properties in the json file.
json properties;

// Used to store current entry before writing into file.
json entry;

// Some arbituary introduction to the program during launch.
void introduction() {

}


// Outputs a line of j length of character k.
void line(int j = 50, char k = '=', bool nextLineAtEnd = true) {
	for (int i = 0; i < j; i++) {
		cout << k;
	}
	if (nextLineAtEnd) {
		cout << endl;
	}
}


// Request file path, opens it and imports it into the json struct.
void readFile() {
	ifstream jsonFile;

	while (true) {
		cout << "File path for json file ? ";
		string filename;
		getline(cin, filename);

		if (filename == "d") {
			filename = "D:\\WinLibrary\\Documents\\GIT-Code\\Bluecoins-ImportTool\\Tests\\ktn.json";
		}

		jsonFile.open(filename);

		if (!jsonFile) {
			cout << "File does not exist. " << endl;
			continue;
		} else {
			break;
		}

	}

	jsonFile >> properties;

	cout << "File succesfully imported." << endl;

	jsonFile.close();
}

// Returns the json string without the quotes
string returnString(json i) {
	return(i);
}

// Outputs all properties and their respective values.
void outAllProperties() {
	cout << "json type : " << returnString(properties["jsonType"]) << endl;

	int i = 0,
		j = 0,
		k = 0;

	while (i < properties["presetLists"].size()) {
		j = 0;
		k = 0;
		cout << returnString(properties["presetLists"][i]["type"]) << " : " << endl;

		while (j < properties["presetLists"][i]["catList"].size()) {
			k = 0;
			line(4, ' ', false);
			cout << returnString(properties["presetLists"][i]["catList"][j]["cat"]) << " : " << endl;

			while (k < properties["presetLists"][i]["catList"][j]["child"].size()) {
				line(8, ' ', false);
				cout << returnString(properties["presetLists"][i]["catList"][j]["child"][k]) << endl;
				k++;
			}
			j++;
		}
		line();
		i++;
	}
}

// Outputs elements one level below, excluding unspecified arrays.
// Place a space if want to output all types.
// If only type provided, list cat.
// If both type and cat provided, list child.
void outArray(string type, string cat = " ") {
	int i = 0;
	bool found0 = false;

	if (type == " ") { // If type is space show all types.
		while (i < properties["presetLists"].size()) {
			cout << returnString(properties["presetLists"][i]["type"]) << endl;
			i++;
		}
	} else {


		while (i < properties["presetLists"].size()) {
			if (returnString(properties["presetLists"][i]["type"]) == type) {
				found0 = true;

				if (cat == " ") { // If only type stated then only output list of categories.
					int j = 0;

					while (j < properties["presetLists"][i]["catList"].size()) {
						cout << returnString(properties["presetLists"][i]["catList"][j]["cat"]) << endl;
						j++;
					}

					break;

				} else { // Else if stated then output child
					int j = 0;
					bool found1 = false;

					while (j < properties["presetLists"][i]["catList"].size()) {
						if (returnString(properties["presetLists"][i]["catList"][j]["cat"]) == cat) {
							int k = 0;
							found1 = true;

							while (k < properties["presetLists"][i]["catList"][j]["child"].size()) {
								cout << returnString(properties["presetLists"][i]["catList"][j]["child"][k]) << endl;
								k++;
							}

						}
						break;
					}

					if (!found1) { // If not found in list then category not found.
						cout << "Category not found." << endl;
					}

				}
				break;
			}

			i++;
		}
		if (!found0) { // If not found in list then type not found.
			cout << "Type not found." << endl;
		}
	}
}

// Outputs all elements one level below according to the index number.
// Also provides index number in the process.
// *Does not output bank accounts unless specified.
void outArray(bool isAccount = false, int type = 10000, int cat = 10000) {
	int i = 0;

	// If selection is account, then start from array entry 1.
	if (isAccount) {
		i = 0;
	} else {
		i = 1;
	}


	if (type == 10000) { // If type is unspecified show all types.
		cout << left << setw(5) << "ID" << "Description" << endl;
		while (i < properties["presetLists"].size()) {
			cout << left << setw(5) << i << returnString(properties["presetLists"][i]["type"]) << endl;
			i++;
		}
	} else {

		line(50, '-');
		if (type < properties["presetLists"].size()) { // Only display if type is less than size of presetList
			if (cat == 10000) { // If only type stated then only output list of categories.
				int j = 0;
				cout << left << setw(5) << "ID" << "Description" << endl;
				line(50, '-');

				while (j < properties["presetLists"][type]["catList"].size()) {
					cout << left << setw(5) << j << returnString(properties["presetLists"][type]["catList"][j]["cat"]) << endl;
					j++;
				}

			} else { // If type and cat stated then output child.
				int j = 0;

				if (cat < properties["presetLists"][type]["catList"].size()) {
					cout << left << setw(5) << "ID" << "Description" << endl;
					line(50, '-');
					while (j < properties["presetLists"][type]["catList"][cat]["child"].size()) {
						cout << left << setw(5) << j << returnString(properties["presetLists"][type]["catList"][cat]["child"][j]) << endl;
						j++;
					}

				} else {
					cout << "Category number invalid." << endl;
				}

			}


		} else {
			cout << "Type number invalid." << endl;
		}
	}
}

int mainMenu() {
	int i = 3,
		selection;
	string menuItem[][2] = { 
		{"0","Load File"},
		{"1", "Unload File"},
		{"2", "View All Entries"},
		{"3", "New Entry"} 
	};
		

	line(50, '-');
	cout << left << setw(5) << "ID" << "Details" << endl;
	line(50, '-');

	for (int j = 0; j < 3; j++) {
		cout << left << setw(5) << menuItem[j][0] << menuItem[j][1] << endl;
	}

	cout << "Your Selection? : ";
	cin >> selection;

	return selection;
}

struct ENTRY {
	string type;


};

bool entryInput() {
	// Integer for expense, income category parent and child.
	int
		i = 0,
		j = 0;

	ENTRY entry;
	bool illegal = true;

	// User input : Type of Transaction *No logic for transfer yet.
	while (illegal) {
		outArray(false);
		cout << endl << left << setw(5) << "5" << "Transfer" << endl;

		cout << endl << "Type? ";
		cin >> i;
		entry.type = returnString(properties["presetLists"][i]["type"]);
		cout << "Type: " << entry.type << endl;

		if ((i == 1) || (i == 2) || (i == 5)) {
			illegal = false;
		} else {
			cout << "Illegal action!" << endl;
		}

	}

	// User input : Expense / Income Parent Category
	illegal == true;
	while (illegal) {
		cout << "Type: " << entry.type << endl;
		outArray(false, i);
		cout << "Category? ";
		cin >> j;

		if ((j < properties["presetLists"][i]["catList"].size()) && (j >= 0)) {
			illegal = false;
		} else {
			cout << "Illegal action!" << endl;
		}

	}

	// User input : Expense / Income Category
	outArray(false, i, j);

	// User input : Account Type


	// User input : Account


	// Date & time input :
    unsigned short int 
        year = 0,
		month = 0,
		day = 0,
		hour = 0,
		mins = 0;

	// User input : Year
	cout << "Year? ";
	cin >> year;

	// User input : Month
	cout << "Month? ";
	cin >> month;

	// User input : Day
	cout << "Day? ";
	cin >> day;

	// User input : Hour
	cout << "Hour? ";
	cin >> hour;

	// User input : Mins
	cout << "Mins? ";
	cin >> mins;

	// User input : Amount


	// User input : Short Description

	// User input : Notes (No multi-line)

	// User input : Status

	// System generate : Label

	// Review entry, then press key to commit into file.


		return true;
}

// TODO: Reference additional headers your program requires here.
