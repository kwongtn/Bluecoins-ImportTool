#pragma once

#include "entryDataStruct.h"

inline std::string return_fixed_digits(int number, int digits = 2) {
	std::string temp = "";
	for (int i = 0; i < digits; i++) {
		if (number < pow(10, i)) {
			temp = temp + "0";
		}
	}
	temp += std::to_string(number);

	return temp;
}


// Returns all current inputted items in entry.
inline void show_fixed(ENTRY myEntry) {
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
// Displays all current inputted items in entry.
inline void show_inputted(ENTRY myEntry) {
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

