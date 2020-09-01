#pragma once
// BluecoinsImportTool.h : Include file for standard system include files,
// or project specific include files.

#include "utils.h"
#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

const string defaultJsonFileName = "D:\\WinLibrary\\Documents\\GIT-Code\\Bluecoins-ImportTool\\Tests\\ktn_new.json";
bool splitTransac = false,
usedSplit = false;

// Global variables related with file output.
ifstream fileCheck;
ofstream file;
bool append = false;
string outFilename = "",
jsonFilename = "";

// Used to store all properties in the json file.
json properties;

#include "./entryDataStruct.h"

ENTRY entry;

// Utility functions:

// Resets all entry to initial values.
void reset() {
	entry.type.reset_input();
	entry.transCat.reset_input();
	entry.transChild.reset_input();
	entry.accCat.reset_input();
	entry.accChild.reset_input();
	entry.year.reset_input();
	entry.month.reset_input();
	entry.day.reset_input();
	entry.hour.reset_input();
	entry.mins.reset_input();
	entry.amount.reset_input();
	entry.title.reset_input();
	entry.notes.reset_input();
	entry.status.reset_input();
	entry.label.reset_input();
	entry.sourceAccCat.reset_input();
	entry.sourceAccChild.reset_input();
	entry.destAccCat.reset_input();
	entry.destAccChild.reset_input();

}

// Some arbituary introduction to the program during launch.
void introduction() {

}


// Returns all current inputted items in entry.
void inputted(ENTRY myEntry) {
	if (myEntry.title.isUsed) {
		cout << "Title: " << myEntry.title.value << endl;

	}

	if (myEntry.type.isUsed) {
		cout << "Type: " << myEntry.type.value << endl;

	}

	if (myEntry.transCat.isUsed) {
		cout << "Category: " << myEntry.transCat.value;

		if (myEntry.transChild.isUsed) {
			cout << " -> " << myEntry.transChild.value;

		}
		else {
			cout << " -> ?";

		}

		cout << endl;

	}

	if (myEntry.sourceAccCat.isUsed) {
		cout << "Source Account: " << myEntry.sourceAccCat.value;

		if (myEntry.sourceAccChild.isUsed) {
			cout << " -> " << myEntry.sourceAccChild.value;

		}
		else {
			cout << " -> ?";

		}

		cout << endl;
	}

	if (myEntry.destAccCat.isUsed) {
		cout << "Destination Account: " << myEntry.destAccCat.value;

		if (myEntry.destAccChild.isUsed) {
			cout << " -> " << myEntry.destAccChild.value;

		}
		else {
			cout << " -> ?";

		}

		cout << endl;

	}

	if (myEntry.accCat.isUsed) {
		cout << "Account: " << myEntry.accCat.value;

		if (myEntry.accChild.isUsed) {
			cout << " -> " << myEntry.accChild.value;

		}
		else {
			cout << "-> ?";

		}
		cout << endl;

	}

	if (myEntry.year.isUsed) {
		cout << "Date (YYYY/MM/DD): " << return_fixed_digits(myEntry.year.value, 4) << "/";

		if (myEntry.month.isUsed) {
			cout << return_fixed_digits(myEntry.month.value, 2) << "/";
		}
		else {
			cout << "--" << "/";
		}

		if (myEntry.day.isUsed) {
			cout << return_fixed_digits(myEntry.day.value, 2) << endl;

		}
		else {
			cout << "--" << endl;

		}

	}

	if (myEntry.hour.isUsed) {
		cout << "Time (HH:MM): " << return_fixed_digits(myEntry.hour.value, 2) << ":";

		if (myEntry.mins.isUsed) {
			cout << return_fixed_digits(myEntry.mins.value, 2) << endl;

		}
		else {
			cout << "--" << endl;
		}

	}

	if (myEntry.amount.isUsed) {
		cout << "Amount: " << fixed << showpoint << setprecision(2) << myEntry.amount.value << endl;

	}

	if (myEntry.status.isUsed) {
		cout << "Status: ";
		if (myEntry.status.value == 'R') {
			cout << "Reconciled";
		}
		else if (myEntry.status.value == 'C') {
			cout << "Cleared";
		}
		else {
			cout << "<None>";
		}
		cout << endl;

	}

	if (myEntry.label.isUsed) {
		cout << "Label: " << myEntry.label.value << endl;

	}

	if (myEntry.notes.isUsed) {
		cout << "\nNotes:\n" << myEntry.notes.value << endl << endl;

	}

}

// Outputs all properties and their respective values.
void outAllProperties() {
	heading("Output all fields");

	// If filepath property exist then load it as default path, and change behaviour accordingly
	cout << "Current output path : " << outFilename << endl;
	if (properties.contains("outFile")) {
		if (properties["outFile"][0].contains("filePath")) {
			cout << "JSON output path : " << returnString(properties["outFile"][0]["filePath"]) << endl;
		}
		if (properties["outFile"][0].contains("advFormat")) {
			cout << "Advanced file type : " << properties["outFile"][0]["advFormat"] << endl;
		}
		if (properties["outFile"][0].contains("defaultAppend")) {
			cout << "    Default is append : " << properties["outFile"][0]["defaultAppend"] << endl;
		}
	}

	for (json type : properties["presetLists"]) {
		cout << returnString(type["type"]) << " : " << endl;

		for (json cat : type["catList"]) {
			line(4, ' ', false);
			cout << returnString(cat["cat"]) << " : " << endl;

			for (json child : cat["child"]) {
				line(8, ' ', false);
				cout << returnString(child["childName"]);

				// If exist then only display
				if (child.contains("currency")) {
					cout << " (" << returnString(child["currency"]) << ") ";
				}
				cout << endl;
				if (child.contains("currentBal")) {
					line(10, ' ', false);
					cout << "Current Balance: " << child["currentBal"] << endl;
				}
				if (child.contains("actualBal")) {
					line(10, ' ', false);
					cout << "Actual Balance: " << child["actualBal"] << endl;
				}

			}

		}

		line();
	}

	system("pause");
}

// === Unused function ===
// Outputs elements one level below, excluding unspecified arrays.
// Place a space if want to output all types.
// If only type provided, list cat.
// If both type and cat provided, list child.
void outArray(string selectionType, string cat = " ") {
	heading("Output all fields one level below");

	bool found0 = false;

	if (selectionType == " ") { // If type is space show all types.
		for (json type : properties["presetLists"]) {
			cout << returnString(type["type"]) << endl;

		}
	}
	else {
		for (json type : properties["presetLists"]) {
			if (returnString(type["type"]) == selectionType) {
				found0 = true;

				if (cat == " ") { // If only type stated then only output list of categories.
					for (json cat : type["catList"]) {
						cout << returnString(cat["cat"]) << endl;

					}
					break;

				}
				else { // Else if stated then output child
					bool found1 = false;

					for (json cat : type["catList"]) {
						if (returnString(cat["cat"]) == cat) {
							found1 = true;

							for (json child : cat["child"]) {
								cout << returnString(child["childName"]);
								if (child.contains("currency")) {
									cout << " (" << returnString(child["currency"]) << ") ";
								}

								cout << endl;

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

		}

		if (!found0) { // If not found in list then type not found.
			cout << "Type not found." << endl;
		}
	}
}

// Outputs all elements one level below according to the index number.
// Also provides index number in the process.
// *Does not output bank accounts unless specified.
void outArray(bool isAccount = false, int type = -1, int cat = -1) {
	int i = 0;

	// If selection is account, then start from array entry 1.
	if (!isAccount) {
		i = 1;
	}

	if (type == -1) { // If type is unspecified show all types.
		menuHeading();
		for (i; i < properties["presetLists"].size(); i++) {
			cout << left << setw(5) << i << returnString(properties["presetLists"][i]["type"]) << endl;

		}

	}
	else {
		if (type < properties["presetLists"].size()) { // Only display if type is less than size of presetList
			if (cat == -1) { // If only type stated then only output list of categories.
				menuHeading();

				for (int j = 0; j < properties["presetLists"][type]["catList"].size(); j++) {
					cout << left << setw(5) << j << returnString(properties["presetLists"][type]["catList"][j]["cat"]) << endl;

				}

			}
			else { // If type and cat stated then output child.
				int j = 0;

				if (cat < properties["presetLists"][type]["catList"].size()) {
					menuHeading();

					for (int j = 0; j < properties["presetLists"][type]["catList"][cat]["child"].size(); j++) {
						cout << left << setw(5) << j << returnString(properties["presetLists"][type]["catList"][cat]["child"][j]["childName"]);
						if (properties["presetLists"][type]["catList"][cat]["child"][j].contains("currency")) {
							cout << " (" << returnString(properties["presetLists"][type]["catList"][cat]["child"][j]["currency"]) << ") ";

						}

						cout << endl;

					}

				}
				else {
					cout << "Category number invalid." << endl;
				}

			}

		}
		else {
			cout << "Type number invalid." << endl;
		}
	}

	cout << endl;
}

// For user to input all entry information.
/*
	There are 3 types of codes to be returned:
	- 0 -> Everything is good, write result to file.
	- 1 -> Everything is good, but discard results.
	- 9 -> User exit halfway through input.
*/
int entryInput() {
	// tempEntry copies from entry, to have respect to selected "fixed" fields
	ENTRY tempEntry = entry;
	// Integer for expense, income category parent and child.

	// Variables that will be used to determine json index & position
	int
		type_index = 0, // To describe type of transaction
		sourceParent_index = 0, // To describe parent
		sourceChild_index = 0, // To describe child
		// Only used in transfers
		destParent_index = 0,
		destChild_index = 0;

	bool illegal = true;

	// User input : Short Description
Title_input:
	while (true) {
		string userInput = "";

		// To cancel changes done by current section, if being called back.
		tempEntry.title.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		cout << "Transaction title? " << endl << "> ";

		getline(cin, userInput);
		USER_INPUT_STRING_RETURN else if (userInput == "-1") { return 9; }

		if (userInput == "") {
			cout << "Please insert a title." << endl;
			pause();
			continue;

		}
		else {
			tempEntry.title.value = userInput;
			tempEntry.title.isUsed = true;
			break;

		}

	}

	// User input : Type of Transaction
Type_input:
	while (true) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.transCat.isUsed = false;
		tempEntry.transChild.isUsed = false;
		tempEntry.type.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		outArray(false);
		cout << endl << left << setw(5) << "5" << "Transfer" << endl;

		cout << endl << "Type? ";
		userInput = inputNumber<int>();

		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Title_input; }

		if ((userInput == 1) || (userInput == 2) || (userInput == 5)) {
			type_index = userInput;
			break;
		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;
		}
	}

	// If transaction type is transfer
	if (type_index == 5) {
		heading("Transaction input: Transfer");
		// Transfer cases
		tempEntry.transCat.value = "(Transfer)";
		tempEntry.transChild.value = "(Transfer)";
		tempEntry.type.value = "Transfer";
		tempEntry.transCat.isUsed = true;
		tempEntry.transChild.isUsed = true;
		tempEntry.type.isUsed = true;

		//To determine source account
		// User input : Account Type
	TransferSourceAccType_input:
		while (true) {
			int userInput = 0;

			// To cancel changes done by current section, if being called back.
			tempEntry.sourceAccCat.isUsed = false;

			heading("Transaction input: Transfer -> Select Source Account");
			inputted(tempEntry);
			outArray(true, 0);

			cout << "Source Account Type? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Type_input; }

			if ((userInput < properties["presetLists"][0]["catList"].size()) && (userInput >= 0)) {
				sourceParent_index = userInput;
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		tempEntry.sourceAccCat.value = returnString(properties["presetLists"][0]["catList"][sourceParent_index]["cat"]);
		tempEntry.sourceAccCat.isUsed = true;

		// User input : Account
	TransferSourceAcc_input:
		while (true) {
			int userInput = 0;

			// To cancel changes done by current section, if being called back.
			tempEntry.sourceAccChild.isUsed = false;

			heading("Transaction input: Transfer -> Select Source Account");
			inputted(tempEntry);
			outArray(true, 0, sourceParent_index);

			cout << "Source Account Child? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransferSourceAccType_input; }

			if ((userInput < properties["presetLists"][0]["catList"][sourceParent_index]["child"].size()) && (userInput >= 0)) {
				sourceChild_index = userInput;
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		tempEntry.sourceAccChild.value = returnString(properties["presetLists"][0]["catList"][sourceParent_index]["child"][sourceChild_index]["childName"]);
		tempEntry.sourceAccChild.isUsed = true;

		// User input : Account Type
	TransferDestAccType_input:
		while (true) {
			int userInput = 0;

			// To cancel changes done by current section, if being called back.
			tempEntry.destAccCat.isUsed = false;

			heading("Transaction input: Transfer -> Select Destination Account");
			inputted(tempEntry);
			outArray(true, 0);

			cout << "Destination Account Type? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransferSourceAcc_input; }

			if ((destParent_index < properties["presetLists"][0]["catList"].size()) && (destParent_index >= 0)) {
				destParent_index = userInput;
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		tempEntry.destAccCat.value = returnString(properties["presetLists"][0]["catList"][destParent_index]["cat"]);
		tempEntry.destAccCat.isUsed = true;

		// User input : Account
	TransferDestAcc_input:
		while (true) {
			int userInput = 0;

			// To cancel changes done by current section, if being called back.
			tempEntry.destAccChild.isUsed = false;

			heading("Transaction input: Transfer -> Select Destination Account");
			inputted(tempEntry);
			outArray(true, 0, destParent_index);
			cout << "Destination Account Child? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransferDestAccType_input; }

			if ((userInput < properties["presetLists"][0]["catList"][userInput]["child"].size()) && (userInput >= 0)) {
				destChild_index = userInput;
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		tempEntry.destAccChild.value = returnString(properties["presetLists"][0]["catList"][destParent_index]["child"][destChild_index]["childName"]);
		tempEntry.destAccChild.isUsed = true;


	}
	else {
		tempEntry.type.value = returnString(properties["presetLists"][type_index]["type"]);
		tempEntry.type.isUsed = true;

		// User input : Expense / Income Parent Category
	TransCat_input:
		while (true) {
			int userInput = 0;

			// To cancel changes done by current section, if being called back.
			tempEntry.transCat.isUsed = false;

			heading("Transaction input");
			inputted(tempEntry);
			outArray(false, type_index);

			cout << "Category? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Type_input; }

			if ((userInput < properties["presetLists"][type_index]["catList"].size()) && (userInput >= 0)) {
				sourceParent_index = userInput;
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		tempEntry.transCat.value = returnString(properties["presetLists"][type_index]["catList"][sourceParent_index]["cat"]);
		tempEntry.transCat.isUsed = true;

		// User input : Expense / Income Category
	TransType_input:
		while (true) {
			int userInput = 0;

			// To cancel changes done by current section, if being called back.
			tempEntry.transChild.isUsed = false;

			heading("Transaction input");
			inputted(tempEntry);
			outArray(false, type_index, sourceParent_index);

			cout << "Category Child? ";
			userInput = inputNumber<int>(false);

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransCat_input; }

			if ((userInput < properties["presetLists"][type_index]["catList"][sourceParent_index]["child"].size()) && (userInput >= 0)) {
				sourceChild_index = userInput;
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		tempEntry.transChild.value = returnString(properties["presetLists"][type_index]["catList"][sourceParent_index]["child"][sourceChild_index]["childName"]);
		tempEntry.transChild.isUsed = true;

		// User input : Account Type
	AccCat_input:
		while (true) {
			int userInput = 0;

			// To cancel changes done by current section, if being called back.
			tempEntry.accCat.isUsed = false;

			heading("Transaction input");
			inputted(tempEntry);
			outArray(true, 0);

			cout << "Account Type? ";
			userInput = inputNumber<int>(false);

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransType_input; }

			if ((userInput < properties["presetLists"][0]["catList"].size()) && (userInput >= 0)) {
				sourceParent_index = userInput;
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		tempEntry.accCat.value = returnString(properties["presetLists"][0]["catList"][sourceParent_index]["cat"]);
		tempEntry.accCat.isUsed = true;

		// User input : Account
	AccType_input:
		while (true) {
			int userInput = 0;

			// To cancel changes done by current section, if being called back.
			tempEntry.accChild.isUsed = false;

			heading("Transaction input");
			inputted(tempEntry);
			outArray(true, 0, sourceParent_index);

			cout << "Account Child? ";
			userInput = inputNumber<int>(false);

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto AccCat_input; }

			if ((userInput < properties["presetLists"][0]["catList"][sourceParent_index]["child"].size()) && (userInput >= 0)) {
				sourceChild_index = userInput;
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		tempEntry.accChild.value = returnString(properties["presetLists"][0]["catList"][sourceParent_index]["child"][sourceChild_index]["childName"]);
		tempEntry.accChild.isUsed = true;

	}

	// Date & time input :

	// User input : Year
Year_input:
	while (true) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.year.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Year? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if ((type_index == 5) && (userInput == -1)) { goto TransferDestAcc_input; }
		else if (userInput == -1) { goto AccType_input; }

		if (userInput > 0) {
			tempEntry.year.value = userInput;
			tempEntry.year.isUsed = true;
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}

	// User input : Month
Month_input:
	while (true) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.month.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Month? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Year_input; }

		if (userInput > 0 && userInput <= 12) {
			tempEntry.month.value = userInput;
			tempEntry.month.isUsed = true;
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}

	// User input : Day
Day_input:
	while (true) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.day.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Day? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Month_input; }

		if (userInput > 0 && userInput <= 31) {
			tempEntry.day.value = userInput;
			tempEntry.day.isUsed = true;
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}

	// User input : Hour
Hour_input:
	while (true) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.hour.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Hour? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Day_input; }

		if (userInput >= 0 && userInput <= 23) {
			tempEntry.hour.value = userInput;
			tempEntry.hour.isUsed = true;
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}

	// User input : Mins
Min_input:
	while (true) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.mins.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Mins? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Hour_input; }

		if (userInput >= 0 && userInput <= 59) {
			tempEntry.mins.value = userInput;
			tempEntry.mins.isUsed = true;
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}

	// ==================================================

	// User input : Amount
Amount_input:
	while (true) {
		double userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.amount.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		line(50, '-');
		cout << "Amount? ";

		userInput = inputNumber<double>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Min_input; }

		if (userInput >= 0) {
			tempEntry.amount.value = userInput;
			tempEntry.amount.isUsed = true;
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}

	// User input : Notes (No multi-line)
Notes_input:
	while (true) {
		string userInput = "";

		// To cancel changes done by current section, if being called back.
		tempEntry.notes.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		line(50, '-');
		cout << "Notes? (Only press 'enter' when done, no multi-line support yet)" << endl;
		line(50, '-');

		getline(cin, userInput);
		USER_INPUT_STRING_RETURN else if (userInput == "-1") { goto Amount_input; }

		tempEntry.notes.value = userInput;
		tempEntry.notes.isUsed = true;
		break;
	}

	// User input : Status
Status_input:
	while (true) {
		string userInput = "";

		// To cancel changes done by current section, if being called back.
		tempEntry.status.isUsed = false;

		heading("Transaction input");
		inputted(tempEntry);
		menuHeading();
		cout << left << setw(5) << "R" << "Reconciled" << endl;
		cout << left << setw(5) << "C" << "Cleared" << endl;
		cout << left << setw(5) << "0" << "<None>" << endl;
		cout << "Status? ";

		getline(cin, userInput);
		USER_INPUT_STRING_RETURN else if (userInput == "-1") { goto Notes_input; }

		if (userInput == "R" || userInput == "r") {
			tempEntry.status.value = 'R';
			break;

		}
		else if (userInput == "C" || userInput == "c") {
			tempEntry.status.value = 'C';
			break;

		}
		else {
			tempEntry.status.value = '\0';
			break;
		}

	}
	tempEntry.status.isUsed = true;

	// System generate : Label
	time_t rawtime = time(&rawtime);
	struct tm now;
	localtime_s(&now, &rawtime);
	int thisYear = now.tm_year + 1900;
	tempEntry.label.value = "Import " + to_string(thisYear) + return_fixed_digits(now.tm_mon, 2);
	tempEntry.label.isUsed = true;

	// Review entry, then press key to return commit intent.
	while (true) {
		string userInput = "";
		entry = tempEntry;

		heading("Transaction input -> Entry Review");
		inputted(tempEntry);
		line(50, '-');
		cout << "Commit changes? (y / n / -1) : ";
		getline(cin, userInput);

		USER_INPUT_STRING_RETURN else if (userInput == "-1") { goto Status_input; }

		if ((userInput == "Y") || (userInput == "y")) {
			// 0 for "Everything fine, commit changes."
			return 0;
		}
		else if ((userInput == "N") || (userInput == "n")) {
			// 1 for "Everything fine, but discard changes."
			return 1;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;
		}
	}

}


// Function to load output file.
void fileFunc(string path = "", bool toAppend = false) {
	if (file.is_open()) {
		file.close();

	}
	heading("Select Output File");
	if (path == "") {
		cout << "File path for output file? ";
		getline(cin, outFilename);
	}

	fileCheck.open(outFilename);
	heading("Select Output File");
	if (!fileCheck) {
		cout << "Output file does not exist, create file? ";
		// TODO: outFilename get overridden no matter file status
		if (decider()) {
			// TODO: File Creation does not work.
			file.open(outFilename);
		}

	}
	else {
		// TODO: Fix logic to prioritize file-defined append action
		string intent = "\0";
		if (!toAppend) {
			cout << "Output file exists, append? (y/n/c) \nSelecting 'n' will clear the existing file. Press 'c' to cancel. " << endl;
			getline(cin, intent);
		}

		if (intent == "c") {
			outFilename = "";
		}
		else if ((intent == "y") || (toAppend == true)) {
			file.open(outFilename, ios::app);
			append = true;
		}
		else if ((intent == "n") || (toAppend == false)) {
			file.open(outFilename);
		}

	}
	fileCheck.close();

}

// Request json file path, opens it and imports it into the json struct.
void readFile() {
	heading("JSON File Import");
	cout << "Please make sure that your json file is updated to the latest format." << endl << endl;
	ifstream jsonFile;
	while (true) {
		cout << "File path for json file ? ";
		getline(cin, jsonFilename);

		if (jsonFilename == "d") {
			jsonFilename = defaultJsonFileName;
		}

		jsonFile.open(jsonFilename);

		if (!jsonFile) {
			cout << "File does not exist. " << endl;
			continue;
		}
		else {
			break;
		}

	}

	// TODO: Try-catch for read errors
	jsonFile >> properties;

	// If filepath property exist then load it as default path, and change behaviour accordingly
	if (properties.contains("outFile")) {
		if (properties["outFile"][0].contains("filePath")) {
			outFilename = returnString(properties["outFile"][0]["filePath"]);
		}
		if (properties["outFile"][0].contains("defaultAppend")) {
			append = properties["outFile"][0]["defaultAppend"];
		}

		// TODO: Loop till there is a filename
		fileFunc(outFilename, append);
	}

	cout << "File succesfully imported." << endl;

	jsonFile.close();
}


// Outputs everything stored in current entry to the output file.
void writeToFile() {
	// If user selects to append or is not first entry then will not output this line.
	if (!append) {
		file << "(1)Type,(2)Date,(3)Item or Payee,(4)Amount,(5)Parent Category,(6)Category,(7)Account Type,(8)Account,(9)Notes,(10) Label,(11) Status,(12) Split" << endl;
	}

	// There are different logics for transfers and normal transactions.
	if (entry.type.value == "Transfer") {
		// Source Account
		file << "Transfer" << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month.value << "/"
			<< setw(2) << entry.day.value << "/"
			<< entry.year.value << " "
			<< setw(2) << entry.hour.value << ":"
			<< setw(2) << entry.mins.value << ","
			<< setfill(' ');
		file << entry.title.value << ",";
		file << entry.amount.value * -1 << ",";
		file << "(Transfer)" << ",";
		file << "(Transfer)" << ",";
		file << entry.sourceAccCat.value << ",";
		file << entry.sourceAccChild.value << ",";
		file << entry.notes.value << ",";
		file << entry.label.value << ",";
		if (entry.status.value != '\0') {
			file << entry.status.value;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;
		// Destination Account
		file << "Transfer" << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month.value << "/"
			<< setw(2) << entry.day.value << "/"
			<< entry.year.value << " "
			<< setw(2) << entry.hour.value << ":"
			<< setw(2) << entry.mins.value << ","
			<< setfill(' ');
		file << entry.title.value << ",";
		file << entry.amount.value << ",";
		file << "(Transfer)" << ",";
		file << "(Transfer)" << ",";
		file << entry.destAccCat.value << ",";
		file << entry.destAccChild.value << ",";
		file << entry.notes.value << ",";
		file << entry.label.value << ",";
		if (entry.status.value != '\0') {
			file << entry.status.value;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;

	}
	else { // For normal use cases.
		file << entry.type.value << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month.value << "/"
			<< setw(2) << entry.day.value << "/"
			<< entry.year.value << " "
			<< setw(2) << entry.hour.value << ":"
			<< setw(2) << entry.mins.value << ","
			<< setfill(' ');

		file << entry.title.value << ",";
		file << entry.amount.value << ",";
		file << entry.transCat.value << ",";
		file << entry.transChild.value << ",";
		file << entry.accCat.value << ",";
		file << entry.accChild.value << ",";
		file << entry.notes.value << ",";
		file << entry.label.value << ",";
		if (entry.status.value != '\0') {
			file << entry.status.value;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;

	}
}

