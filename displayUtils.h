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


inline string return_dt_string(ENTRY myEntry) {
	string dtString = "";

	myEntry.year.isUsed ?
		dtString += return_fixed_digits(myEntry.year.value, 4) :
		dtString += "----";

	dtString += "/";

	myEntry.month.isUsed ?
		dtString += return_fixed_digits(myEntry.month.value, 2) :
		dtString += "--";

	dtString += "/";

	myEntry.day.isUsed ?
		dtString += return_fixed_digits(myEntry.day.value, 2) :
		dtString += "--";

	dtString += " ";

	myEntry.hour.isUsed ?
		dtString += return_fixed_digits(myEntry.hour.value, 2) :
		dtString += "--";

	dtString += ":";

	myEntry.mins.isUsed ?
		dtString += return_fixed_digits(myEntry.mins.value, 2) :
		dtString += "--";

	return dtString;
}


// Returns all current inputted items in entry.
inline void show_fixed(ENTRY myEntry) {
	if (!myEntry.is_anything_locked()) {
		cout << "Nothing is locked yet." << endl;
		return;
	}

	if (myEntry.title.isFixed) {
		cout << "Title: " << myEntry.title.value << endl;

	}

	if (myEntry.type.isFixed) {
		cout << "Type: " << myEntry.type.value << endl;

	}

	if (myEntry.transCat.isFixed) {
		cout << "Category: " << myEntry.transCat.value;

		if (myEntry.transChild.isFixed) {
			cout << " -> " << myEntry.transChild.value;

		}
		else {
			cout << " -> ?";

		}

		cout << endl;

	}

	if (myEntry.sourceAccCat.isFixed) {
		cout << "Source Account: " << myEntry.sourceAccCat.value;

		if (myEntry.sourceAccChild.isFixed) {
			cout << " -> " << myEntry.sourceAccChild.value;

		}
		else {
			cout << " -> ?";

		}

		cout << endl;
	}

	if (myEntry.destAccCat.isFixed) {
		cout << "Destination Account: " << myEntry.destAccCat.value;

		if (myEntry.destAccChild.isFixed) {
			cout << " -> " << myEntry.destAccChild.value;

		}
		else {
			cout << " -> ?";

		}

		cout << endl;

	}

	if (myEntry.accCat.isFixed) {
		cout << "Account: " << myEntry.accCat.value;

		if (myEntry.accChild.isFixed) {
			cout << " -> " << myEntry.accChild.value;

		}
		else {
			cout << "-> ?";

		}
		cout << endl;

	}

	if (myEntry.is_dateTime_locked()) {
		cout << "Datetime (YYYY/MM/DD HH:MM): " << return_dt_string(myEntry) << endl;
	}

	if (myEntry.amount.isFixed) {
		cout << "Amount: " << fixed << showpoint << setprecision(2) << myEntry.amount.value << endl;

	}

	if (myEntry.status.isFixed) {
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

	if (myEntry.label.isFixed) {
		cout << "Label: " << myEntry.label.value << endl;

	}

	if (myEntry.notes.isFixed) {
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

	if (myEntry.year.isUsed || myEntry.is_dateTime_locked()) {
		cout << "Datetime (YYYY/MM/DD HH:MM): " << return_dt_string(myEntry);
		cout << endl;

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

