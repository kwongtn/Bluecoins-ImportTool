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
	entry.type = "";
	entry.transCat = "";
	entry.transChild = "";
	entry.accCat = "";
	entry.accChild = "";
	entry.year = 0;
	entry.month = 0;
	entry.day = 0;
	entry.hour = 1000;
	entry.mins = 1000;
	entry.amount = 3.14159265359;
	entry.title = "";
	entry.notes = "";
	entry.status = '\0';
	entry.label = "";
	entry.sourceAccCat = "";
	entry.sourceAccChild = "";
	entry.destAccCat = "";
	entry.destAccChild = "";
}

// Some arbituary introduction to the program during launch.
void introduction() {

}


// Returns all current inputted items in entry.
void inputted() {
	if (entry.title != "") {
		cout << "Title: " << entry.title << endl;
	}

	if (entry.type != "") {
		cout << "Type: " << entry.type << endl;
	}

	if (entry.transCat != "") {
		cout << "Category: " << entry.transCat;

		if (entry.transChild != "") {
			cout << " -> " << entry.transChild;

		}
		else {
			cout << " -> ?";

		}

		cout << endl;

	}


	if (entry.type == "Transfer") {
		if (entry.sourceAccCat != "") {
			cout << "Source Account: " << entry.sourceAccCat;

			if (entry.sourceAccChild != "") {
				cout << " -> " << entry.sourceAccChild;

			}
			else {
				cout << " -> ?";

			}

			cout << endl;
		}

		if (entry.destAccCat != "") {
			cout << "Destination Account: " << entry.destAccCat;

			if (entry.destAccChild != "") {
				cout << " -> " << entry.destAccChild;

			}
			else {
				cout << " -> ?";

			}

			cout << endl;

		}

	}
	else {
		if (entry.accCat != "") {
			cout << "Account: " << entry.accCat;

			if (entry.accChild != "") {
				cout << " -> " << entry.accChild;

			}
			else {
				cout << "-> ?";

			}

			cout << endl;

		}

	}

	if ((entry.year != 0) &&
		(entry.month != 0) &&
		(entry.day != 0) &&
		(entry.hour != 1000) &&
		(entry.mins != 1000)
		) {
		cout << "Date (YYYY/MM/DD): "
			<< right << entry.year << "/"
			<< setfill('0') << setw(2) << entry.month << "/"
			<< setfill('0') << setw(2) << entry.day
			<< endl;

		cout << "Time (HH:MM): "
			<< setfill('0') << setw(2) << entry.hour << ":"
			<< setfill('0') << setw(2) << entry.mins
			<< endl;
		cout << setfill(' ');
	}

	if (entry.amount != 3.14159265359) {
		cout << "Amount: " << fixed << showpoint << setprecision(2) << entry.amount << endl;
	}


	if (entry.status != '\0') {
		cout << "Status: " << entry.status << endl;
	}

	if (entry.label != "") {
		cout << "Label: " << entry.label << endl;
	}

	if (entry.notes != "") {
		cout << "\nNotes:\n" << entry.notes << endl << endl;
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
	getline(cin, entry.title);

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
		entry.transCat = "(Transfer)";
		entry.transChild = "(Transfer)";
		entry.type = "Transfer";

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
		entry.sourceAccCat = returnString(properties["presetLists"][0]["catList"][j]["cat"]);

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
		entry.sourceAccChild = returnString(properties["presetLists"][0]["catList"][j]["child"][k]["childName"]);

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
		entry.destAccCat = returnString(properties["presetLists"][0]["catList"][j]["cat"]);

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
			entry.destAccChild = returnString(properties["presetLists"][0]["catList"][j]["child"][k]["childName"]);

		}

	}
	else {
		// User input : Expense / Income Parent Category
		entry.type = returnString(properties["presetLists"][i]["type"]);
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
		entry.transCat = returnString(properties["presetLists"][i]["catList"][j]["cat"]);

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
		entry.transChild = returnString(properties["presetLists"][i]["catList"][j]["child"][k]["childName"]);

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
		entry.accCat = returnString(properties["presetLists"][0]["catList"][j]["cat"]);

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
		entry.accChild = returnString(properties["presetLists"][0]["catList"][j]["child"][k]["childName"]);

	}

	// Date & time input :
	heading("Transaction input");
	inputted();
	line(50, '-');
	cout << "Date & time input: " << endl;

	// User input : Year
	cout << "Year? ";
	entry.year = inputNumber<int>(false);

	// User input : Month
	cout << "Month? ";
	entry.month = inputNumber<int>(false);

	// User input : Day
	cout << "Day? ";
	entry.day = inputNumber<int>(false);

	// User input : Hour
	cout << "Hour? ";
	entry.hour = inputNumber<int>(false);

	// User input : Mins
	cout << "Mins? ";
	entry.mins = inputNumber<int>(false);
	// ==================================================

	// User input : Amount
	heading("Transaction input");
	inputted();
	line(50, '-');
	cout << "Amount? ";
	entry.amount = inputNumber<double>(false);

	// User input : Notes (No multi-line)
	heading("Transaction input");
	inputted();
	line(50, '-');
	cout << "Notes? (Only press 'enter' when done, no multi-line support yet)" << endl;
	line(50, '-');
	getline(cin, entry.notes);

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
			entry.status = 'R';
			break;

		}
		else if (statusSelect == "C" || statusSelect == "c") {
			entry.status = 'C';
			break;

		}
		else {
			entry.status = '\0';
			break;
		}

	}

	// System generate : Label
	time_t rawtime = time(&rawtime);
	struct tm now;
	localtime_s(&now, &rawtime);
	int thisYear = now.tm_year + 1900;
	entry.label = "Import " + to_string(thisYear) + return_fixed_digits(now.tm_mon, 2);

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
	if (entry.type == "Transfer") {
		// Source Account
		file << "Transfer" << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month << "/"
			<< setw(2) << entry.day << "/"
			<< entry.year << " "
			<< setw(2) << entry.hour << ":"
			<< setw(2) << entry.mins << ","
			<< setfill(' ');
		file << entry.title << ",";
		file << entry.amount * -1 << ",";
		file << "(Transfer)" << ",";
		file << "(Transfer)" << ",";
		file << entry.sourceAccCat << ",";
		file << entry.sourceAccChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		if (entry.status != '\0') {
			file << entry.status;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;
		// Destination Account
		file << "Transfer" << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month << "/"
			<< setw(2) << entry.day << "/"
			<< entry.year << " "
			<< setw(2) << entry.hour << ":"
			<< setw(2) << entry.mins << ","
			<< setfill(' ');
		file << entry.title << ",";
		file << entry.amount << ",";
		file << "(Transfer)" << ",";
		file << "(Transfer)" << ",";
		file << entry.destAccCat << ",";
		file << entry.destAccChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		if (entry.status != '\0') {
			file << entry.status;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;

	}
	else { // For normal use cases.
		file << entry.type << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month << "/"
			<< setw(2) << entry.day << "/"
			<< entry.year << " "
			<< setw(2) << entry.hour << ":"
			<< setw(2) << entry.mins << ","
			<< setfill(' ');

		file << entry.title << ",";
		file << entry.amount << ",";
		file << entry.transCat << ",";
		file << entry.transChild << ",";
		file << entry.accCat << ",";
		file << entry.accChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		if (entry.status != '\0') {
			file << entry.status;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;

	}
}

