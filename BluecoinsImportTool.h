#pragma once
// BluecoinsImportTool.h : Include file for standard system include files,
// or project specific include files.

#include "utils.h"
#include "displayUtils.h"
#include "./entryDataStruct.h"
ENTRY entry;


const string defaultJsonFileName = "D:\\WinLibrary\\Documents\\GIT-Code\\Bluecoins-ImportTool\\Tests\\ktn_new.json";
bool splitTransac = false,
usedSplit = false;

// Global variables related with file output.
ifstream fileCheck;
ofstream file;
bool append = false;
bool writebackChanges = false;
string outFilename = "",
jsonFilename = "";

// Used to store all properties in the json file.
json properties;


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


	// pause();
}

// Outputs all properties and their respective values.
void outAllProperties() {
	heading("Output all fields");

	// If filepath property exist then load it as default path, and change behaviour accordingly
	cout << "Current output path : " << outFilename << endl;
	if (properties.contains("outFile")) {
		if (properties["outFile"].contains("filePath")) {
			cout << "JSON-Defined output path : " << returnString(properties["outFile"]["filePath"]) << endl;
		}
		if (properties["outFile"].contains("advFormat")) {
			cout << "Advanced file type : " << properties["outFile"]["advFormat"] << endl;
		}
		if (properties["outFile"].contains("defaultAppend")) {
			cout << "    Default is append : " << properties["outFile"]["defaultAppend"] << endl;
		}
		if (properties["outFile"].contains("writebackChanges")) {
			cout << "    Write-back changes : " << properties["outFile"]["writebackChanges"] << endl;
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
				if (child.contains("bluecoinsBal")) {
					line(10, ' ', false);
					cout << "Bluecoins Balance: " << child["bluecoinsBal"] << endl;
				}
				if (child.contains("targetBal")) {
					line(10, ' ', false);
					cout << "Target Balance: " << child["targetBal"] << endl;
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

/*
	For user to input all entry information.
	There are 3 types of codes to be returned:
	- 0 -> Everything is good, write result to file.
	- 1 -> Everything is good, but discard results.
	- 9 -> User exit halfway through input.
*/
int entryInput(ENTRY entryTemplate) {
	// tempEntry copies from template, to have respect to selected "fixed" fields
	ENTRY tempEntry = entryTemplate;

	int type_index = 0; // To describe type of transaction
	if (tempEntry.type.isFixed) {
		type_index = tempEntry.type.fixedIndex;
	}

	// User input : Short Description
Title_input:
	while (!tempEntry.title.isFixed) {
		string userInput = "";

		// To cancel changes done by current section, if being called back.
		tempEntry.title.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		cout << "Transaction title? " << endl << "> ";

		getline(cin, userInput);
		USER_INPUT_STRING_RETURN else if (userInput == "-1") { return 9; }

		if (userInput == "") {
			cout << "Please insert a title." << endl;
			pause();
			continue;

		}
		else {
			tempEntry.title.set(userInput);
			break;

		}

	}

	// User input : Type of Transaction
Type_input:
	while (!tempEntry.type.isFixed) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.transCat.reset_input();
		tempEntry.transChild.reset_input();
		tempEntry.type.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		outArray(false);
		if (!splitTransac) { cout << endl << left << setw(5) << "5" << "Transfer" << endl; }

		cout << endl << "Type? ";
		userInput = inputNumber<int>();

		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Title_input; }

		if ((userInput == 1) || (userInput == 2) || ((userInput == 5) && !splitTransac)) {
			type_index = userInput;
			break;
		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;
		}
	}

	// If transaction type is transfer -- split transactions never come here
	if ((type_index == 5) && !splitTransac) {
		heading("Transaction input: Transfer");
		// Transfer cases
		if (!tempEntry.type.isFixed) {
			tempEntry.transCat.set("(Transfer)");
			tempEntry.transChild.set("(Transfer)");
			tempEntry.type.set("Transfer");

		}

		// To determine source account
		// User input : Account Type
	TransferSourceAccType_input:
		while (!tempEntry.sourceAccCat.isFixed) {
			int userInput = -1;

			// To cancel changes done by current section, if being called back.
			tempEntry.sourceAccCat.reset_input();

			heading("Transaction input: Transfer -> Select Source Account");
			show_inputted(tempEntry);
			outArray(true, 0);

			cout << "Source Account Type? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Type_input; }

			if ((userInput < properties["presetLists"][0]["catList"].size()) && (userInput >= 0)) {
				tempEntry.sourceAccCat.set(
					returnString(properties["presetLists"][0]["catList"][userInput]["cat"]),
					userInput);
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}

		// User input : Account
	TransferSourceAcc_input:
		while (!tempEntry.sourceAccChild.isFixed) {
			int userInput = -1;
			int parentIndex = tempEntry.sourceAccCat.fixedIndex;

			// To cancel changes done by current section, if being called back.
			tempEntry.sourceAccChild.reset_input();

			heading("Transaction input: Transfer -> Select Source Account");
			show_inputted(tempEntry);
			outArray(true, 0, parentIndex);

			cout << "Source Account Child? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransferSourceAccType_input; }

			if ((userInput < properties["presetLists"][0]["catList"][parentIndex]["child"].size()) && (userInput >= 0)) {
				tempEntry.sourceAccChild.set(
					returnString(properties["presetLists"][0]["catList"][parentIndex]["child"][userInput]["childName"]),
					userInput);
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}

		// User input : Account Type
	TransferDestAccType_input:
		while (!tempEntry.destAccCat.isFixed) {
			int userInput = -1;

			// To cancel changes done by current section, if being called back.
			tempEntry.destAccCat.reset_input();

			heading("Transaction input: Transfer -> Select Destination Account");
			show_inputted(tempEntry);
			outArray(true, 0);

			cout << "Destination Account Type? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransferSourceAcc_input; }

			if ((userInput < properties["presetLists"][0]["catList"].size()) && (userInput >= 0)) {
				tempEntry.destAccCat.set(
					returnString(properties["presetLists"][0]["catList"][userInput]["cat"]),
					userInput);
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}

		// User input : Account
	TransferDestAcc_input:
		while (!tempEntry.destAccChild.isFixed) {
			int userInput = -1;
			int parentIndex = tempEntry.destAccCat.fixedIndex;

			// To cancel changes done by current section, if being called back.
			tempEntry.destAccChild.reset_input();

			heading("Transaction input: Transfer -> Select Destination Account");
			show_inputted(tempEntry);
			outArray(true, 0, parentIndex);
			cout << "Destination Account Child? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransferDestAccType_input; }

			if ((userInput < properties["presetLists"][0]["catList"][parentIndex]["child"].size()) && (userInput >= 0)) {
				tempEntry.destAccChild.set(
					returnString(properties["presetLists"][0]["catList"][parentIndex]["child"][userInput]["childName"]),
					userInput);
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}

	}
	else {
		if (!tempEntry.type.isFixed) {
			splitTransac ?
				tempEntry.type.fix(returnString(properties["presetLists"][type_index]["type"]), type_index) :
				tempEntry.type.set(returnString(properties["presetLists"][type_index]["type"]));

		}

		// User input : Expense / Income Parent Category
	TransCat_input:
		while (!tempEntry.transCat.isFixed) {
			int userInput = -1;

			// To cancel changes done by current section, if being called back.
			tempEntry.transCat.reset_input();

			heading("Transaction input");
			show_inputted(tempEntry);
			outArray(false, type_index);

			cout << "Category? ";
			userInput = inputNumber<int>();

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Type_input; }

			if ((userInput < properties["presetLists"][type_index]["catList"].size()) && (userInput >= 0)) {
				tempEntry.transCat.set(
					returnString(properties["presetLists"][type_index]["catList"][userInput]["cat"]),
					userInput);
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}

		// User input : Expense / Income Category
	TransType_input:
		while (!tempEntry.transChild.isFixed) {
			int userInput = -1;
			int parentIndex = tempEntry.transCat.fixedIndex;

			// To cancel changes done by current section, if being called back.
			tempEntry.transChild.reset_input();

			heading("Transaction input");
			show_inputted(tempEntry);
			outArray(false, type_index, parentIndex);

			cout << "Category Child? ";
			userInput = inputNumber<int>(false);

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransCat_input; }

			if ((userInput < properties["presetLists"][type_index]["catList"][parentIndex]["child"].size()) && (userInput >= 0)) {
				tempEntry.transChild.set(
					returnString(properties["presetLists"][type_index]["catList"][parentIndex]["child"][userInput]["childName"]),
					userInput);
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}

		// User input : Account Type
	AccCat_input:
		while (!tempEntry.accCat.isFixed) {
			int userInput = -1;

			// To cancel changes done by current section, if being called back.
			tempEntry.accCat.reset_input();

			heading("Transaction input");
			show_inputted(tempEntry);
			outArray(true, 0);

			cout << "Account Type? ";
			userInput = inputNumber<int>(false);

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto TransType_input; }

			if ((userInput < properties["presetLists"][0]["catList"].size()) && (userInput >= 0)) {
				tempEntry.accCat.set(
					returnString(properties["presetLists"][0]["catList"][userInput]["cat"]),
					userInput);
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}

		// User input : Account
	AccType_input:
		while (!tempEntry.accChild.isFixed) {
			int userInput = 0;
			int parentIndex = tempEntry.accCat.fixedIndex;

			// To cancel changes done by current section, if being called back.
			tempEntry.accChild.reset_input();

			heading("Transaction input");
			show_inputted(tempEntry);
			outArray(true, 0, parentIndex);

			cout << "Account Child? ";
			userInput = inputNumber<int>(false);

			USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto AccCat_input; }

			if ((userInput < properties["presetLists"][0]["catList"][parentIndex]["child"].size()) && (userInput >= 0)) {
				tempEntry.accChild.set(returnString(properties["presetLists"][0]["catList"][parentIndex]["child"][userInput]["childName"]));
				break;
			}
			else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}

	}

	// Date & time input :

	// User input : Year
Year_input:
	while (!tempEntry.year.isFixed) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.year.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Year? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if ((type_index == 5) && (userInput == -1)) { goto TransferDestAcc_input; }
		else if (userInput == -1) { goto AccType_input; }

	if (userInput > 0) {
		splitTransac ?
			tempEntry.year.fix(userInput) :
			tempEntry.year.set(userInput);
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
	while (!tempEntry.month.isFixed) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.month.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Month? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Year_input; }

		if (userInput > 0 && userInput <= 12) {
			splitTransac ?
				tempEntry.month.fix(userInput) :
				tempEntry.month.set(userInput);
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
	while (!tempEntry.day.isFixed) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.day.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Day? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Month_input; }

		if (userInput > 0 && userInput <= 31) {
			splitTransac ?
				tempEntry.day.fix(userInput) :
				tempEntry.day.set(userInput);
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
	while (!tempEntry.hour.isFixed) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.hour.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Hour? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Day_input; }

		if (userInput >= 0 && userInput <= 23) {
			splitTransac ?
				tempEntry.hour.fix(userInput) :
				tempEntry.hour.set(userInput);
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
	while (!tempEntry.mins.isFixed) {
		int userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.mins.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		line(50, '-');
		cout << "Date & time input: " << endl;
		cout << "Mins? ";

		userInput = inputNumber<int>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Hour_input; }

		if (userInput >= 0 && userInput <= 59) {
			splitTransac ?
				tempEntry.mins.fix(userInput) :
				tempEntry.mins.set(userInput);
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
	while (!tempEntry.amount.isFixed) {
		double userInput = 0;

		// To cancel changes done by current section, if being called back.
		tempEntry.amount.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		line(50, '-');
		cout << "Amount? ";

		userInput = inputNumber<double>(false);
		USER_INPUT_NUMBER_RETURN else if (userInput == -1) { goto Min_input; }

		tempEntry.amount.set(userInput);
		break;

	}

	// User input : Notes (No multi-line)
Notes_input:
	while (!tempEntry.notes.isFixed) {
		string userInput = "";

		// To cancel changes done by current section, if being called back.
		tempEntry.notes.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		line(50, '-');
		cout << "Notes? (Only press 'enter' when done, no multi-line support yet)" << endl;
		line(50, '-');

		getline(cin, userInput);
		USER_INPUT_STRING_RETURN else if (userInput == "-1") { goto Amount_input; }

		tempEntry.notes.set(userInput);
		break;
	}

	// User input : Status
Status_input:
	while (!tempEntry.status.isFixed) {
		string userInput = "";

		// To cancel changes done by current section, if being called back.
		tempEntry.status.reset_input();

		heading("Transaction input");
		show_inputted(tempEntry);
		menuHeading();
		cout << left << setw(5) << "R" << "Reconciled" << endl;
		cout << left << setw(5) << "C" << "Cleared" << endl;
		cout << left << setw(5) << "0" << "<None>" << endl;
		cout << "Status? ";

		getline(cin, userInput);
		USER_INPUT_STRING_RETURN else if (userInput == "-1") { goto Notes_input; }

		if (userInput == "R" || userInput == "r") {
			splitTransac ?
				tempEntry.status.fix('R') :
				tempEntry.status.set('R');
			break;

		}
		else if (userInput == "C" || userInput == "c") {
			splitTransac ?
				tempEntry.status.fix('C') :
				tempEntry.status.set('C');
			break;

		}
		else {
			splitTransac ?
				tempEntry.status.fix('\0') :
				tempEntry.status.set('\0');
			break;
		}

	}

	// System generate : Label
	time_t rawtime = time(&rawtime);
	struct tm now;
	localtime_s(&now, &rawtime);
	int thisYear = now.tm_year + 1900;
	tempEntry.label.set("Import " + to_string(thisYear) + return_fixed_digits(now.tm_mon, 2));

	// Review entry, then press key to return commit intent.
	while (true) {
		string userInput = "";
		entry = tempEntry;

		heading("Transaction input -> Entry Review");
		show_inputted(tempEntry);
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
			file.open(outFilename, ios::trunc);
			append = false;

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

	try {
		jsonFile >> properties;

	}
	catch (...) {
		cout << "JSON File Read Error. Please check using linters to make sure that the JSON is in correct form." << endl
			<< "The program will now exit.";
		pause();
		exit(1);
	}

	// If filepath property exist then load it as default path, and change behaviour accordingly
	if (properties.contains("outFile")) {
		if (properties["outFile"].contains("filePath")) {
			outFilename = returnString(properties["outFile"]["filePath"]);
		}
		if (properties["outFile"].contains("defaultAppend")) {
			append = properties["outFile"]["defaultAppend"];
		}
		if (properties["outFile"].contains("writebackChanges")) {
			writebackChanges = properties["outFile"]["writebackChanges"];
			if (!properties["outFile"].contains("writebackJSONSpacing")) {
				properties["outFile"]["writebackJSONSpacing"] = 4;
			}
		}


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

		// If accounts have currentBal defined then deduct it
		if (properties["presetLists"][0]["catList"][entry.sourceAccCat.fixedIndex]["child"][entry.sourceAccChild.fixedIndex].contains("bluecoinsBal")) {
			double sourceCurrentBalance = properties["presetLists"][0]["catList"][entry.sourceAccCat.fixedIndex]["child"][entry.sourceAccChild.fixedIndex]["bluecoinsBal"],
				destCurrentBalance = properties["presetLists"][0]["catList"][entry.destAccCat.fixedIndex]["child"][entry.destAccChild.fixedIndex]["bluecoinsBal"];

			sourceCurrentBalance -= entry.amount.value;
			destCurrentBalance += entry.amount.value;

			properties["presetLists"][0]["catList"][entry.sourceAccCat.fixedIndex]["child"][entry.sourceAccChild.fixedIndex]["bluecoinsBal"] = sourceCurrentBalance;
			destCurrentBalance = properties["presetLists"][0]["catList"][entry.destAccCat.fixedIndex]["child"][entry.destAccChild.fixedIndex]["bluecoinsBal"] = destCurrentBalance;

			// Write changes into json file
			if (writebackChanges) {
				ofstream jsonOutput;
				jsonOutput.open(jsonFilename);

				jsonOutput << properties.dump(properties["outFile"]["writebackJSONSpacing"]);

				jsonOutput.close();
			}

			if (properties["presetLists"][0]["catList"][entry.sourceAccCat.fixedIndex]["child"][entry.sourceAccChild.fixedIndex]["bluecoinsBal"] == properties["presetLists"][0]["catList"][entry.sourceAccCat.fixedIndex]["child"][entry.sourceAccChild.fixedIndex]["targetBal"]) {
				cout << "Hurray! Target and bluecoins balance are now the same for: " << endl
					<< properties["presetLists"][0]["catList"][entry.sourceAccCat.fixedIndex]["cat"] << " -> "
					<< properties["presetLists"][0]["catList"][entry.sourceAccCat.fixedIndex]["child"][entry.sourceAccChild.fixedIndex]["childName"] << endl
					<< "at " << sourceCurrentBalance << endl << endl;
				pause();
			}
			if (properties["presetLists"][0]["catList"][entry.destAccCat.fixedIndex]["child"][entry.destAccChild.fixedIndex]["bluecoinsBal"] == properties["presetLists"][0]["catList"][entry.destAccCat.fixedIndex]["child"][entry.destAccChild.fixedIndex]["targetBal"]) {
				cout << "Hurray! Target and bluecoins balance are now the same for: " << endl
					<< properties["presetLists"][0]["catList"][entry.destAccCat.fixedIndex]["cat"] << " -> "
					<< properties["presetLists"][0]["catList"][entry.destAccCat.fixedIndex]["child"][entry.destAccChild.fixedIndex]["childName"] << endl
					<< "at " << destCurrentBalance << endl << endl;
				pause();
			}
		}

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

		// If accounts have currentBal defined then deduct it
		if (properties["presetLists"][0]["catList"][entry.accCat.fixedIndex]["child"][entry.accChild.fixedIndex].contains("bluecoinsBal")) {
			double currentBalance = properties["presetLists"][0]["catList"][entry.accCat.fixedIndex]["child"][entry.accChild.fixedIndex]["bluecoinsBal"];

			if (entry.type.value == "Expense") {
				currentBalance -= entry.amount.value;

			}
			else if (entry.type.value == "Income") {
				currentBalance += entry.amount.value;

			}
			else {
				throw new string("Error");
			}

			properties["presetLists"][0]["catList"][entry.accCat.fixedIndex]["child"][entry.accChild.fixedIndex]["bluecoinsBal"] = currentBalance;

			// Write changes into json file
			if (writebackChanges) {
				ofstream jsonOutput;
				jsonOutput.open(jsonFilename);

				jsonOutput << properties.dump(properties["outFile"]["writebackJSONSpacing"]);

				jsonOutput.close();
			}

			if (properties["presetLists"][0]["catList"][entry.accCat.fixedIndex]["child"][entry.accChild.fixedIndex]["bluecoinsBal"] == properties["presetLists"][0]["catList"][entry.accCat.fixedIndex]["child"][entry.accChild.fixedIndex]["targetBal"]) {
				cout << "Hurray! Target and bluecoins balance are now the same for: " << endl
					<< properties["presetLists"][0]["catList"][entry.accCat.fixedIndex]["cat"] << " -> "
					<< properties["presetLists"][0]["catList"][entry.accCat.fixedIndex]["child"][entry.accChild.fixedIndex]["childName"] << endl
					<< "at " << currentBalance << endl << endl;
				pause();
			}
		}


	}
}

// Synchronize fixed stuff between 2 entries, prioritizing source 1
ENTRY syncFixed(ENTRY source1, ENTRY source2) {
	ENTRY result;

	source1.type.isFixed ?
		result.type.fix(source1.type.value, source1.type.fixedIndex) :
		result.type.fix(source2.type.value, source2.type.fixedIndex);

	source1.transCat.isFixed ?
		result.transCat.fix(source1.transCat.value, source1.transCat.fixedIndex) :
		result.transCat.fix(source2.transCat.value, source2.transCat.fixedIndex);

	source1.transChild.isFixed ?
		result.transChild.fix(source1.transChild.value, source1.transChild.fixedIndex) :
		result.transChild.fix(source2.transChild.value, source2.transChild.fixedIndex);

	source1.accCat.isFixed ?
		result.accCat.fix(source1.accCat.value, source1.accCat.fixedIndex) :
		result.accCat.fix(source2.accCat.value, source2.accCat.fixedIndex);

	source1.accChild.isFixed ?
		result.accChild.fix(source1.accChild.value, source1.accChild.fixedIndex) :
		result.accChild.fix(source2.accChild.value, source2.accChild.fixedIndex);

	source1.year.isFixed ?
		result.year.fix(source1.year.value, source1.year.fixedIndex) :
		result.year.fix(source2.year.value, source2.year.fixedIndex);

	source1.month.isFixed ?
		result.month.fix(source1.month.value, source1.month.fixedIndex) :
		result.month.fix(source2.month.value, source2.month.fixedIndex);

	source1.day.isFixed ?
		result.day.fix(source1.day.value, source1.day.fixedIndex) :
		result.day.fix(source2.day.value, source2.day.fixedIndex);

	source1.hour.isFixed ?
		result.hour.fix(source1.hour.value, source1.hour.fixedIndex) :
		result.hour.fix(source2.hour.value, source2.hour.fixedIndex);

	source1.mins.isFixed ?
		result.mins.fix(source1.mins.value, source1.mins.fixedIndex) :
		result.mins.fix(source2.mins.value, source2.mins.fixedIndex);

	source1.amount.isFixed ?
		result.amount.fix(source1.amount.value, source1.amount.fixedIndex) :
		result.amount.fix(source2.amount.value, source2.amount.fixedIndex);

	source1.title.isFixed ?
		result.title.fix(source1.title.value, source1.title.fixedIndex) :
		result.title.fix(source2.title.value, source2.title.fixedIndex);

	source1.notes.isFixed ?
		result.notes.fix(source1.notes.value, source1.notes.fixedIndex) :
		result.notes.fix(source2.notes.value, source2.notes.fixedIndex);

	source1.label.isFixed ?
		result.label.fix(source1.label.value, source1.label.fixedIndex) :
		result.label.fix(source2.label.value, source2.label.fixedIndex);

	source1.status.isFixed ?
		result.status.fix(source1.status.value, source1.status.fixedIndex) :
		result.status.fix(source2.status.value, source2.status.fixedIndex);

	source1.sourceAccCat.isFixed ?
		result.sourceAccCat.fix(source1.sourceAccCat.value, source1.sourceAccCat.fixedIndex) :
		result.sourceAccCat.fix(source2.sourceAccCat.value, source2.sourceAccCat.fixedIndex);

	source1.sourceAccChild.isFixed ?
		result.sourceAccChild.fix(source1.sourceAccChild.value, source1.sourceAccChild.fixedIndex) :
		result.sourceAccChild.fix(source2.sourceAccChild.value, source2.sourceAccChild.fixedIndex);

	source1.destAccCat.isFixed ?
		result.destAccCat.fix(source1.destAccCat.value, source1.destAccCat.fixedIndex) :
		result.destAccCat.fix(source2.destAccCat.value, source2.destAccCat.fixedIndex);

	source1.destAccChild.isFixed ?
		result.destAccChild.fix(source1.destAccChild.value, source1.destAccChild.fixedIndex) :
		result.destAccChild.fix(source2.destAccChild.value, source2.destAccChild.fixedIndex);

	return result;
}