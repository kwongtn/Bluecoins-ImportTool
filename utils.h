#pragma once

#include "includeHeaders.h"

inline void line(int j = 50, char k = '=', bool nextLineAtEnd = true) {
	for (int i = 0; i < j; i++) {
		cout << k;
	}
	if (nextLineAtEnd) {
		cout << endl;
	}
}

inline void pause() {
	cout << endl;
	system("pause");
}

inline void clearScreen() {
	system("cls");
}

inline void heading(std::string additional = "") {
	system("cls");
	cout << "############################################################" << endl;
	cout << "##      Bluecoins Import Tool v2.0-beta by KwongTN       ###" << endl;
	cout << "############################################################" << endl << endl;

	if (additional != "") {
		cout << additional << endl;
		cout << "-------------------------------------------------------------" << endl;
	}
}

inline std::string returnString(json i) {
	return i;
}

// Outputs the following in the console
// --------------------------------------------------
// ID   Details
// --------------------------------------------------
inline void menuHeading() {
	line(50, '-');
	cout << "ID   " << "Description" << endl;
	line(50, '-');
}

inline int menuGen(json rowNames) {
	int j = 0;
	for (int i = 0; i < rowNames.size(); i++) {
		cout << i << "\t" << returnString(rowNames[i]) << endl;
		j++;
	}
	cout << endl;
	return j;
}


inline int menuGen(json rowNames, std::string myOutput) {
	int j = 0;
	for (int i = 0; i < rowNames.size(); i++) {
		cout << i << "\t" << returnString(rowNames[i][myOutput]) << endl;
		j++;
	}
	cout << endl;
	return j;
}

inline int menuGen(json rowNames, std::string myOutput, std::string determiner) {
	int j = 0;
	for (int i = 0; i < rowNames.size(); i++) {
		if (rowNames[i][determiner]) {
			cout << i << "\t" << returnString(rowNames[i][myOutput]) << endl;
			j++;
		}
	}
	cout << endl;
	return j;
}


inline bool decider(std::string custString = "Your selection (y / n): ") {
	bool x = true;
	std::string selection;
	while (true) {
		cout << custString;
		try {
			getline(cin, selection);
			if (selection == "y" || selection == "Y") {
				x = true;
				break;
			}
			else if (selection == "n" || selection == "N") {
				x = false;
				break;
			}
			else {
				throw "Error";
			}
			if (cin.fail() || selection != "y" || selection != "Y" || selection != "n" || selection != "N") {
				throw "Error";
			}
		}
		catch (...) {
			cout << "Please enter a valid character." << endl;

		}
	}
	return x;

}

// Whether an array of values contain a key
inline bool arrayContains(json myJSON, std::string element) {
	if (myJSON.size() == 0) {
		return false;
	}
	for (int i = 0; i < myJSON.size(); i++) {
		if (myJSON[i].contains(element)) {
			return true;
		}
	}

	return false;
}

// Whether a vector contains a value
template <typename T1>
inline bool vectorContains(std::vector<T1> myVector, T1 against) {
	try {
		if (myVector.size() == 0) {
			return false;
		}
		for (int i = 0; i < myVector.size(); i++) {
			if (myVector[i] == against) {
				return true;
			}
		}
		return false;

	}
	catch (...) {
		return false;
	}
}

#pragma warning( push )
#pragma warning( disable : 4244)
template <typename T1>
inline T1 inputNumber(bool prompter = true, bool forceInput = true) {
	const char* dataType = typeid(T1).name();
	T1 value = 0;
	std::string myString = "";

	while (true) {
		cin.clear();
		if (prompter) {
			cout << "\n> ";
		}
		getline(cin, myString);

		if (myString == "" && !forceInput) {
			return -1000;
		}

		try
		{
			if (*dataType == 'i') {
				value = std::stoi(myString);
			}
			else if (*dataType == 'd') {
				value = std::stod(myString);
			}
			else if (*dataType == 'f') {
				value = std::stof(myString);
			}
			else {
				throw;
			}
			break;
		}
		catch (std::invalid_argument const& e)
		{
			cout << "Bad input: std::invalid_argument thrown. Please re-input." << '\n';
			!prompter ? prompter = !prompter : prompter;
			continue;
		}
		catch (std::out_of_range const& e)
		{
			cout << "Integer overflow: std::out_of_range thrown. Please re-input." << '\n';
			!prompter ? prompter = !prompter : prompter;
			continue;
		}
		catch (...) {
			cout << "Unknown data type. If you see this this is a bug.";
		}

	}
	cin.clear();
	return value;
}
#pragma warning( pop ) 

inline std::string random_string(size_t length = rand() + 1) {
	srand((unsigned int)time(NULL));
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

inline std::string return_current_time_and_date()
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}


inline void emptyVoidFunction() {};
