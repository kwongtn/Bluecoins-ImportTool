// File contains all functions for file manipulation

#include "BluecoinsImportTool.h"

// For file input
string jsonFilename;
// Request file path, opens it and imports it into the json struct.
void readFile(bool ignore = false) {
	ifstream jsonFile;
	while (true) {
		cout << "File path for json file ? ";
		if (ignore) {
			cin.ignore();
		}
		getline(cin, jsonFilename);

		// You can edit this to prevent yourself from having to retype the full path everytime.
		if (jsonFilename == "d") {
			jsonFilename = "D:\\WinLibrary\\Documents\\GIT-Code\\Bluecoins-ImportTool\\Tests\\ktn.json";
		}

		jsonFile.open(jsonFilename);

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



// For file output
ifstream fileCheck;
ofstream file;
bool append = false;
string outFilename;

void fileFunc(bool ignore = false) {
	cout << "File path for output file? ";
	if (ignore) {
		cin.ignore();
	}
	getline(cin, outFilename);

	if (outFilename == "d") {
		outFilename = "D:\\WinLibrary\\Documents\\GIT-Code\\Bluecoins-ImportTool\\Tests\\outputfile.csv";
	}

	fileCheck.open(outFilename);
	if (!fileCheck) {
		cout << "File does not exist, create file? (y/n)";
		char intent;
		cin >> intent;
		intent = tolower(intent);

		// If 'y' then create file else go back main menu
		if (intent == 'y') {
			file.open(outFilename);
		}

	} else {
		cout << "File exists, append? Selecting 'n' will clear the existing file. Press 'c' to cancel." << endl;
		char intent;
		cin >> intent;
		intent = tolower(intent);

		if (intent == 'y') {
			file.open(outFilename, ios::app);
			append = true;
		} else if (intent == 'n') {
			file.open(outFilename);
		} else {
			outFilename = "";
		}

	}
	fileCheck.close();


}

void writeToFile() {
	if (!append) {
		file << "(1)Type,(2)Date,(3)Item or Payee,(4)Amount,(5)Parent Category,(6)Category,(7)Account Type,(8)Account,(9)Notes,(10) Label,(11) Status" << endl;
	}
	if (entry.type == "Transfer") {
		// Source
		file << "Transfer" << ",";
		file << entry.month << "/" << entry.day << "/" << entry.year << " " << entry.hour << ":" << entry.mins << ",";
		file << entry.item << ",";
		file << entry.amount << ",";
		file << "(Transfer)" << ",";
		file << "(Transfer)" << ",";
		file << entry.sourceAccCat << ",";
		file << entry.sourceAccChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		file << entry.status;
		file << endl;
		// Destination
		file << "Transfer" << ",";
		file << entry.month << "/" << entry.day << "/" << entry.year << " " << entry.hour << ":" << entry.mins << ",";
		file << entry.item << ",";
		file << entry.amount << ",";
		file << "(Transfer)" << ",";
		file << "(Transfer)" << ",";
		file << entry.destAccCat << ",";
		file << entry.destAccChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		file << entry.status;
		file << endl;

	} else {
		file << entry.type << ",";
		file << entry.month << "/" << entry.day << "/" << entry.year << " " << entry.hour << ":" << entry.mins << ",";
		file << entry.item << ",";
		file << entry.amount << ",";
		file << entry.transCat << ",";
		file << entry.transChild << ",";
		file << entry.accCat << ",";
		file << entry.accChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		file << entry.status;
		file << endl;

	}
}
