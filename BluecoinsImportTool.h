#pragma once
// BluecoinsImportTool.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "utils.h"
#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

const int menusize = 10;
const string defaultJsonFileName = "D:\\WinLibrary\\Documents\\GIT-Code\\Bluecoins-ImportTool\\Tests\\ktn_new.json";
bool splitTransac = false;


// Used to store all properties in the json file.
json properties;

#include "./entryDataStruct.h"

// Utility functions:

// Resets all entry to initial values.
void reset() {
	if (!entry.type.isFixed) {
		entry.type.isUsed = false;
		entry.type.value = "";
	}
	if (!entry.transCat.isFixed) {
		entry.transCat.isUsed = false;
		entry.transCat.value = "";
	}
	if (!entry.transChild.isFixed) {
		entry.transChild.isUsed = false;
		entry.transChild.value = "";
	}
	if (!entry.accCat.isFixed) {
		entry.accCat.isUsed = false;
		entry.accCat.value = "";
	}
	if (!entry.accChild.isFixed) {
		entry.accChild.isUsed = false;
		entry.accChild.value = "";
	}
	if (!entry.year.isFixed) {
		entry.year.isUsed = false;
		entry.year.value = 0;
	}
	if (!entry.month.isFixed) {
		entry.month.isUsed = false;
		entry.month.value = 0;
	}
	if (!entry.day.isFixed) {
		entry.day.isUsed = false;
		entry.day.value = 0;
	}
	if (!entry.hour.isFixed) {
		entry.hour.isUsed = false;
		entry.hour.value = 0;
	}
	if (!entry.mins.isFixed) {
		entry.mins.isUsed = false;
		entry.mins.value = 0;
	}
	if (!entry.amount.isFixed) {
		entry.amount.isUsed = false;
		entry.amount.value = 0;
	}
	if (!entry.title.isFixed) {
		entry.title.isUsed = false;
		entry.title.value = "";
	}
	if (!entry.notes.isFixed) {
		entry.notes.isUsed = false;
		entry.notes.value = "";
	}
	if (!entry.status.isFixed) {
		entry.status.isUsed = false;
		entry.status.value = '\0';
	}
	if (!entry.label.isFixed) {
		entry.label.isUsed = false;
		entry.label.value = "";
	}
	if (!entry.sourceAccCat.isFixed) {
		entry.sourceAccCat.isUsed = false;
		entry.sourceAccCat.value = "";
	}
	if (!entry.sourceAccChild.isFixed) {
		entry.sourceAccChild.isUsed = false;
		entry.sourceAccChild.value = "";
	}
	if (!entry.destAccCat.isFixed) {
		entry.destAccCat.isUsed = false;
		entry.destAccCat.value = "";
	}
	if (!entry.destAccChild.isFixed) {
		entry.destAccChild.isUsed = false;
		entry.destAccChild.value = "";
	}
}

// Some arbituary introduction to the program during launch.
void introduction() {

}


// Returns all current inputted items in entry.
void inputted() {
	if (entry.title.isUsed) {
		cout << "Title: " << entry.title.value << endl;

	}

	if (entry.type.isUsed) {
		cout << "Type: " << entry.type.value << endl;

	}

	if (entry.transCat.isUsed) {
		cout << "Category: " << entry.transCat.value;

		if (entry.transChild.isUsed) {
			cout << " -> " << entry.transChild.value;

		}
		else {
			cout << " -> ?";

		}

		cout << endl;

	}


	if (entry.type.isUsed) {
		if (entry.sourceAccCat.isUsed) {
			cout << "Source Account: " << entry.sourceAccCat.value;

			if (entry.sourceAccChild.isUsed) {
				cout << " -> " << entry.sourceAccChild.value;

			}
			else {
				cout << " -> ?";

			}

			cout << endl;
		}

		if (entry.destAccCat.isUsed) {
			cout << "Destination Account: " << entry.destAccCat.value;

			if (entry.destAccChild.isUsed) {
				cout << " -> " << entry.destAccChild.value;

			}
			else {
				cout << " -> ?";

			}

			cout << endl;

		}

	}
	else {
		if (entry.accCat.isUsed) {
			cout << "Account: " << entry.accCat.value;

			if (entry.accChild.isUsed) {
				cout << " -> " << entry.accChild.value;

			}
			else {
				cout << "-> ?";

			}

			cout << endl;

		}

	}

	if ((entry.year.isUsed) &&
		(entry.month.isUsed) &&
		(entry.day.isUsed) &&
		(entry.hour.isUsed) &&
		(entry.mins.isUsed)
		) {
		cout << "Date (YYYY/MM/DD): "
			<< right << entry.year.value << "/"
			<< setfill('0') << setw(2) << entry.month.value << "/"
			<< setfill('0') << setw(2) << entry.day.value
			<< endl;

		cout << "Time (HH:MM): "
			<< setfill('0') << setw(2) << entry.hour.value << ":"
			<< setfill('0') << setw(2) << entry.mins.value
			<< endl;
		cout << setfill(' ');

	}

	if (entry.amount.isUsed) {
		cout << "Amount: " << fixed << showpoint << setprecision(2) << entry.amount.value << endl;

	}


	if (entry.status.isUsed) {
		cout << "Status: " << entry.status.value << endl;

	}

	if (entry.label.isUsed) {
		cout << "Label: " << entry.label.value << endl;

	}

	if (entry.notes.isUsed) {
		cout << "\nNotes:\n" << entry.notes.value << endl << endl;

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
bool entryInput() {
	// Integer for expense, income category parent and child.
	int
		i = 0, // To describe type of transaction
		j = 0, // To describe parent
		k = 0; // To describe child

	bool illegal = true;

	// User input : Short Description
	heading("Transaction input");
	inputted();
	cout << "Transaction title? " << endl << "> ";
	getline(cin, entry.title.value);
	entry.title.isUsed = true;

	// User input : Type of Transaction
	while (true) {
		heading("Transaction input");
		inputted();
		outArray(false);
		cout << endl << left << setw(5) << "5" << "Transfer" << endl;

		cout << endl << "Type? ";
		i = inputNumber<int>();

		if ((i == 1) || (i == 2) || (i == 5)) {
			break;
		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;
		}
	}

	// If transaction type is transfer
	if (i == 5) {
		heading("Transaction input: Transfer");
		// Transfer cases
		entry.transCat.value = "(Transfer)";
		entry.transChild.value = "(Transfer)";
		entry.type.value = "Transfer";
		entry.transCat.isUsed = true;
		entry.transChild.isUsed = true;
		entry.type.isUsed = true;


		//To determine source account
		// User input : Account Type
		while (true) {
			heading("Transaction input: Transfer -> Select Source Account");
			inputted();
			outArray(true, 0);

			cout << "Source Account Type? ";
			j = inputNumber<int>();

			if ((j < properties["presetLists"][0]["catList"].size()) && (j >= 0)) {
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		entry.sourceAccCat.value = returnString(properties["presetLists"][0]["catList"][j]["cat"]);
		entry.sourceAccCat.isUsed = true;

		// User input : Account
		while (true) {
			heading("Transaction input: Transfer -> Select Source Account");
			inputted();
			outArray(true, 0, j);

			cout << "Source Account Child? ";
			k = inputNumber<int>();

			if ((k < properties["presetLists"][0]["catList"][j]["child"].size()) && (k >= 0)) {
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		entry.sourceAccChild.value = returnString(properties["presetLists"][0]["catList"][j]["child"][k]["childName"]);
		entry.sourceAccChild.isUsed = true;

		// To determine destination account.
		j = 0;
		k = 0;
		// User input : Account Type
		while (true) {
			heading("Transaction input: Transfer -> Select Destination Account");
			inputted();
			outArray(true, 0);

			cout << "Destination Account Type? ";
			j = inputNumber<int>();

			if ((j < properties["presetLists"][0]["catList"].size()) && (j >= 0)) {
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		entry.destAccCat.value = returnString(properties["presetLists"][0]["catList"][j]["cat"]);
		entry.destAccCat.isUsed = true;

		// User input : Account
		while (true) {
			heading("Transaction input: Transfer -> Select Destination Account");
			inputted();
			outArray(true, 0, j);
			cout << "Destination Account Child? ";
			k = inputNumber<int>();

			if ((k < properties["presetLists"][0]["catList"][j]["child"].size()) && (k >= 0)) {
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		entry.destAccChild.value = returnString(properties["presetLists"][0]["catList"][j]["child"][k]["childName"]);
		entry.destAccChild.isUsed = true;


	}
	else {
		// User input : Expense / Income Parent Category
		entry.type.value = returnString(properties["presetLists"][i]["type"]);
		entry.type.isUsed = true;

		while (true) {
			heading("Transaction input");
			inputted();
			outArray(false, i);

			cout << "Category? ";
			j = inputNumber<int>();

			if ((j < properties["presetLists"][i]["catList"].size()) && (j >= 0)) {
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		entry.transCat.value = returnString(properties["presetLists"][i]["catList"][j]["cat"]);
		entry.transCat.value = true;

		// User input : Expense / Income Category
		while (true) {
			heading("Transaction input");
			inputted();
			outArray(false, i, j);

			cout << "Category Child? ";
			k = inputNumber<int>(false);

			if ((k < properties["presetLists"][i]["catList"][j]["child"].size()) && (k >= 0)) {
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		entry.transChild.value = returnString(properties["presetLists"][i]["catList"][j]["child"][k]["childName"]);
		entry.transChild.isUsed = true;

		// User input : Account Type
		while (true) {
			heading("Transaction input");
			inputted();
			outArray(true, 0);

			cout << "Account Type? ";
			j = inputNumber<int>(false);

			if ((j < properties["presetLists"][0]["catList"].size()) && (j >= 0)) {
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		entry.accCat.value = returnString(properties["presetLists"][0]["catList"][j]["cat"]);
		entry.accCat.isUsed = true;

		// User input : Account
		while (true) {
			heading("Transaction input");
			inputted();
			outArray(true, 0, j);

			cout << "Account Child? ";
			k = inputNumber<int>(false);

			if ((k < properties["presetLists"][0]["catList"][j]["child"].size()) && (k >= 0)) {
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		entry.accChild.value = returnString(properties["presetLists"][0]["catList"][j]["child"][k]["childName"]);
		entry.accChild.isUsed = true;

	}

	// Date & time input :
	heading("Transaction input");
	inputted();
	line(50, '-');
	cout << "Date & time input: " << endl;

	// User input : Year
	cout << "Year? ";
	entry.year.value = inputNumber<int>(false);
	entry.year.isUsed = true;

	// User input : Month
	cout << "Month? ";
	entry.month.value = inputNumber<int>(false);
	entry.month.isUsed = true;

	// User input : Day
	cout << "Day? ";
	entry.day.value = inputNumber<int>(false);
	entry.day.isUsed = true;

	// User input : Hour
	cout << "Hour? ";
	entry.hour.value = inputNumber<int>(false);
	entry.hour.isUsed = true;

	// User input : Mins
	cout << "Mins? ";
	entry.mins.value = inputNumber<int>(false);
	entry.mins.isUsed = true;

	// ==================================================

	// User input : Amount
	heading("Transaction input");
	inputted();
	line(50, '-');
	cout << "Amount? ";
	entry.amount.value = inputNumber<double>(false);
	entry.amount.isUsed = true;

	// User input : Notes (No multi-line)
	heading("Transaction input");
	inputted();
	line(50, '-');
	cout << "Notes? (Only press 'enter' when done, no multi-line support yet)" << endl;
	line(50, '-');
	getline(cin, entry.notes.value);
	entry.notes.isUsed = true;

	// User input : Status
	while (true) {
		heading("Transaction input");
		inputted();
		menuHeading();
		string statusSelect = "\0";
		cout << left << setw(5) << "R" << "Reconciled" << endl;
		cout << left << setw(5) << "C" << "Cleared" << endl;
		cout << left << setw(5) << "0" << "<None>" << endl;
		cout << "Status? ";
		getline(cin, statusSelect);

		if (statusSelect == "R" || statusSelect == "r") {
			entry.status.value = 'R';
			break;

		}
		else if (statusSelect == "C" || statusSelect == "c") {
			entry.status.value = 'C';
			break;

		}
		else {
			entry.status.value = '\0';
			break;
		}

	}
	entry.status.isUsed = true;

	// System generate : Label
	time_t rawtime = time(&rawtime);
	struct tm now;
	localtime_s(&now, &rawtime);
	int thisYear = now.tm_year + 1900;
	entry.label.value = "Import " + to_string(thisYear) + return_fixed_digits(now.tm_mon, 2);
	entry.label.isUsed = true;

	// Review entry, then press key to return commit intent.
	while (true) {
		heading("Transaction input -> Entry Review");
		inputted();
		line(50, '-');
		cout << "Commit changes? ";
		if (decider()) {
			return true;
		}
		else {
			return false;
		}
	}
}

// Global variables related with file output.
ifstream fileCheck;
ofstream file;
bool append = false;
string outFilename = "",
jsonFilename = "";

// Function to load output file.
void fileFunc(string path = "", bool toAppend = false) {
	heading("Select Output File");
	if (path == "") {
		cout << "File path for output file? ";
		getline(cin, outFilename);
	}

	fileCheck.open(outFilename);
	heading("Select Output File");
	if (!fileCheck) {
		cout << "Output file does not exist, create file? ";
		if (decider()) {
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

