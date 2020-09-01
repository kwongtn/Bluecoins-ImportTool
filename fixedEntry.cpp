#include "utils.h"
#include "displayUtils.h"

const int FIXED_MENU_SIZE = 10;

#include "entryDataStruct.h"
ENTRY templateEntry;
json props;

int
type_index = 0, // To describe type of transaction
accParent_index = 0, // To describe source parent / category
accChild_index = 0, // To describe source child account
// Only used in transfers
sourceParent_index = 0,
sourceChild_index = 0,
destParent_index = 0,
destChild_index = 0;

void outArray(bool, int type = -1, int cat = -1);

void lockTransactionType() {
	heading("Lock Field -> Transaction Type");
	while (true) {
		int userInput = 0;

		outArray(false);
		cout << endl << left << setw(5) << "5" << "Transfer" << endl;

		cout << endl << "Type? ";
		userInput = inputNumber<int>();

		USER_INPUT_NUMBER_RETURN_NULL else if (userInput == -1) { return; }

		switch (userInput) {
		case 1:
		case 2:
			type_index = userInput;
			templateEntry.type.value = returnString(props["presetLists"][userInput]["type"]);
			break;
		case 5:
			templateEntry.type.fix("Transfer");
			templateEntry.transCat.fix("(Transfer)");
			templateEntry.transChild.fix("(Transfer)");
			break;
		default:
			cout << "Illegal action!" << endl;
			system("pause");
			continue;
		}

		templateEntry.type.isUsed = true;
		templateEntry.type.isFixed = true;
		break;
	}
}

// Expenses & Income
void lockTransCat() {
	templateEntry.transCat.reset();
	templateEntry.transChild.reset();
}

void lockTransChild() {
	templateEntry.transChild.reset();
}

void lockAccCat() {
	templateEntry.accCat.reset();
	templateEntry.accChild.reset();
}

void lockAccChild() {
	templateEntry.accChild.reset();
}

// Transfers
void lockTransferSourceCategory() {
	templateEntry.sourceAccCat.reset();
	templateEntry.sourceAccChild.reset();
}

void lockTransferSourceChild() {
	templateEntry.sourceAccChild.reset();
}

void lockTransferDestinationCategory() {
	templateEntry.destAccCat.reset();
	templateEntry.destAccChild.reset();
}

void lockTransferDestinationChild() {
	templateEntry.destAccChild.reset();
}

// Common
void lockYear() {
	while (true) {
		templateEntry.year.reset();
		int userInput = 0;

		heading("Transaction input");
		show_fixed(templateEntry);
		line(50, '-');
		cout << "Year? ";

		userInput = inputNumber<int>(false, false);

		// -100000 is the value returned if there are no inputs
		if (userInput == -100000) return;

		if (userInput >= 1) {
			templateEntry.year.fix(userInput);
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}
}

void lockMonth() {
	while (true) {
		templateEntry.month.reset();
		int userInput = 0;

		heading("Transaction input");
		show_fixed(templateEntry);
		line(50, '-');
		cout << "Month? ";

		userInput = inputNumber<int>(false, false);

		// -100000 is the value returned if there are no inputs
		if (userInput == -100000) return;

		if (userInput >= 1 && userInput <= 12) {
			templateEntry.month.fix(userInput);
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}
}

void lockDay() {
	while (true) {
		templateEntry.day.reset();
		int userInput = 0;

		heading("Transaction input");
		show_fixed(templateEntry);
		line(50, '-');
		cout << "Day? ";

		userInput = inputNumber<int>(false, false);

		// -100000 is the value returned if there are no inputs
		if (userInput == -100000) return;

		if (userInput > 0 && userInput <= 31) {
			templateEntry.day.fix(userInput);
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}
}

void lockHour() {
	while (true) {
		templateEntry.hour.reset();
		int userInput = 0;

		heading("Transaction input");
		show_fixed(templateEntry);
		line(50, '-');
		cout << "Hour? ";

		userInput = inputNumber<int>(false, false);

		// -100000 is the value returned if there are no inputs
		if (userInput == -100000) return;

		if (userInput >= 0 && userInput <= 23) {
			templateEntry.hour.fix(userInput);
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}
}

void lockMins() {
	while (true) {
		templateEntry.mins.reset();
		int userInput = 0;

		heading("Transaction input");
		show_fixed(templateEntry);
		line(50, '-');
		cout << "Mins? ";

		userInput = inputNumber<int>(false, false);

		// -100000 is the value returned if there are no inputs
		if (userInput == -100000) return;

		if (userInput >= 0 && userInput <= 59) {
			templateEntry.mins.fix(userInput);
			break;

		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;

		}

	}
}

void dtInteractive() {
	templateEntry.year.reset();
	templateEntry.month.reset();
	templateEntry.day.reset();
	templateEntry.hour.reset();
	templateEntry.mins.reset();
	lockYear();
	lockMonth();
	lockDay();
	lockHour();
	lockMins();
}

void lockTitle() {
	while (true) {
		templateEntry.title.reset();
		string userInput = "";

		heading("Transaction input");
		show_fixed(templateEntry);
		line(50, '-');
		cout << "Transaction title? " << endl << "> ";

		getline(cin, userInput);

		if (userInput == "") {
			cout << "Please insert a title." << endl;
			pause();
			continue;

		}
		else {
			templateEntry.title.fix(userInput);
			break;

		}

	}
}

void lockNotes() {
	templateEntry.notes.reset();

	heading("Lock Field -> Notes");
	show_fixed(templateEntry);
	line(50, '-');
	cout << "Notes? (Only press 'enter' when done, no multi-line support yet)" << endl;
	line(50, '-');

	string userInput;
	getline(cin, userInput);

	templateEntry.notes.fix(userInput);
}

void lockStatus() {
	while (true) {
		templateEntry.status.reset_input();
		string userInput = "";

		heading("Transaction input");
		show_fixed(templateEntry);
		menuHeading();
		cout << left << setw(5) << "R" << "Reconciled" << endl;
		cout << left << setw(5) << "C" << "Cleared" << endl;
		cout << left << setw(5) << "0" << "<None>" << endl;
		cout << "Status? ";

		getline(cin, userInput);

		if (userInput == "R" || userInput == "r") {
			templateEntry.status.set('R');
			break;

		}
		else if (userInput == "C" || userInput == "c") {
			templateEntry.status.set('C');
			break;

		}
		else if (userInput == "0") {
			templateEntry.status.set('\0');
			break;
		}
		else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;
		}
	}
}

// Option 0
void resetAll() {
	ENTRY newEntry;
	templateEntry = newEntry;

}

void interactiveMode() {
	cout << "Interactive Mode";
	// TODO: Interactive Mode
}


ENTRY fixedEntryMenu(json myProperties, ENTRY entryTemplate) {
	templateEntry = entryTemplate;
	props = myProperties;

	while (true) {
		heading("Lock Field Menu");
		show_fixed(templateEntry);
		int selection = 0;

		struct MENU {
			int count = 0;
			string content = "";
		};

		/*
		0.  Prompted, if "enter" without selecting anything means ignore / don't lock
		1.  type
				-> If changed between expenses&income with transfers, transCat, transChild, accCat, accChild, sourceAccCat, sourceAccChild, destAccCat, destAccChild resets

		-- Only show for non-transfers --
		2.  transCat
				-> If transCat resets transChild resets too
		21. transChild
				-> Will show only after selecting transCat
		3.  accCat
				->
		31. accChild
				-> Will only show after selecting accCat
		----

		-- Only show for transfers --
		4. sourceAccCat
				->
		41. sourceAccChild
				-> Will only show after selecting sourceAccCat
		5. destAccCat
				->
		51. destAccChild
				-> Will only show after selecting destAccCat
		----

		6.  Input
				-> Function to input datetime one by one, subfunction of "0"
		61. year
		62. month
		63. day
		64. hour
		65. mins

		7. title
		71. notes
		8. status
		*/

		// Define menus
		vector<MENU> menu;

		templateEntry.is_anything_locked() ?
			menu.push_back({ 0, "[!!!] Unlock everything" }) :
			menu.push_back({ 0, "Interactive Lock, if \"enter\" without selecting anything means ignore / don't lock." });

		// Menu entry for transaction type
		templateEntry.type.isFixed ?
			menu.push_back({ 1, "[!] Reset Transaction Type, Current: " + templateEntry.type.value }) :
			menu.push_back({ 1, "Lock Transaction Type" });


		// Show this section for expenses and income
		if ((templateEntry.type.value == "Expense" && templateEntry.type.isFixed) ||
			(templateEntry.type.value == "Income" && templateEntry.type.isFixed)) {
			menu.push_back({ 0, "" });

			// Option to lock transaction category & child if entry type is expense & income
			if (templateEntry.transCat.isFixed) {
				menu.push_back({ 2, "[!] Reset " + templateEntry.type.value + " Category, Current: " + templateEntry.transCat.value });

				templateEntry.transChild.isFixed ?
					menu.push_back({ 21, "[!] Reset " + templateEntry.type.value + " Category Child, Current: " + templateEntry.transChild.value }) :
					menu.push_back({ 21, "Lock " + templateEntry.type.value + " Category Child" });

			}
			else {
				menu.push_back({ 2, "Lock " + templateEntry.type.value + " Category" });

			}

			// Option to lock target account category & children type
			if (templateEntry.accCat.isFixed) {
				menu.push_back({ 3, "[!] Reset " + templateEntry.type.value + " Account Category, Current: " + templateEntry.accCat.value });

				templateEntry.accChild.isFixed ?
					menu.push_back({ 31, "[!] Reset " + templateEntry.type.value + " Account Category Child, Current: " + templateEntry.accChild.value }) :
					menu.push_back({ 31, "Lock " + templateEntry.type.value + " Account Category Child" });

			}
			else {
				menu.push_back({ 3, "Lock " + templateEntry.type.value + " Account Category" });

			}

		}
		// Else show this for transfers
		else if (templateEntry.type.value == "Transfer" && templateEntry.type.isFixed) {
			menu.push_back({ 0, "" });

			// Option to lock source account category & children type
			if (templateEntry.sourceAccCat.isFixed) {
				menu.push_back({ 4, "[!] Reset " + templateEntry.type.value + " Source Account Category, Current: " + templateEntry.sourceAccCat.value });

				templateEntry.sourceAccChild.isFixed ?
					menu.push_back({ 41, "[!] Reset " + templateEntry.type.value + " Source Account Category Child, Current: " + templateEntry.sourceAccChild.value }) :
					menu.push_back({ 41, "Lock " + templateEntry.type.value + " Source Account Category Child" });

			}
			else {
				menu.push_back({ 4, "Lock " + templateEntry.type.value + " Source Account Category" });

			}

			// Option to lock destination account category & children type
			if (templateEntry.destAccCat.isFixed) {
				menu.push_back({ 5, "[!] Reset " + templateEntry.type.value + " Destination Account Category, Current: " + templateEntry.destAccCat.value });

				templateEntry.destAccChild.isFixed ?
					menu.push_back({ 51, "[!] Reset " + templateEntry.type.value + " Destination Account Category Child, Current: " + templateEntry.destAccChild.value }) :
					menu.push_back({ 51, "Lock " + templateEntry.type.value + " Destination Account Category Child" });

			}
			else {
				menu.push_back({ 5, "Lock " + templateEntry.type.value + " Destination Account Category" });

			}
		}

		menu.push_back({ 0, "" });

		// Date time (Interactive)
		templateEntry.is_dateTime_locked() ?
			menu.push_back({ 6, "[!] Reset Datetime, Current: " + return_dt_string(templateEntry) }) :
			menu.push_back({ 6, "Lock Datetime (Interactive)" });

		templateEntry.year.isFixed ?
			menu.push_back({ 61, 
				"[!] Reset Year, Current: " + return_fixed_digits(templateEntry.year.value, 4) }) :
			menu.push_back({ 61, "Lock Year" });

		templateEntry.month.isFixed ?
			menu.push_back({ 62, 
				"[!] Reset Month, Current: " + return_fixed_digits(templateEntry.month.value, 2) }) :
			menu.push_back({ 62, "Lock Month" });

		templateEntry.day.isFixed ?
			menu.push_back({ 63, 
				"[!] Reset Day, Current: " + return_fixed_digits(templateEntry.day.value) }) :
			menu.push_back({ 63, "Lock Day" });

		templateEntry.hour.isFixed ?
			menu.push_back({ 64, 
				"[!] Reset Hour, Current: " + return_fixed_digits(templateEntry.hour.value) }) :
			menu.push_back({ 64, "Lock Hour" });

		templateEntry.mins.isFixed ?
			menu.push_back({ 65, 
				"[!] Reset Minutes, Current: " + return_fixed_digits(templateEntry.mins.value) }) :
			menu.push_back({ 65, "Lock Minutes" });

		templateEntry.title.isFixed ?
			menu.push_back({ 7, "[!] Reset Title, Current: " + templateEntry.title.value }) :
			menu.push_back({ 7, "Lock Title" });

		menu.push_back({ 0, "" });

		templateEntry.notes.isFixed ?
			menu.push_back({ 71, "[!] Reset Notes, Current: " + templateEntry.notes.value }) :
			menu.push_back({ 71, "Lock Notes" });

		templateEntry.status.isFixed ?
			menu.push_back({ 8, "[!] Reset Status, Current: " + templateEntry.status.value }) :
			menu.push_back({ 8, "Lock Status" });

		menu.push_back({ 0, "" });

		menu.push_back({ 9, "Exit to Main Menu" });


		// Output menu.
		menuHeading();
		for (int j = 0; j < menu.size(); j++) {
			if (menu[j].content != "") {
				cout << left << setw(5) << menu[j].count << menu[j].content;
			}
			cout << endl;
		}

		selection = inputNumber<int>();

		switch (selection)
		{
		case 0: { // Interactive Mode
			templateEntry.is_anything_locked() ?
				resetAll() : // Reset everything 
				interactiveMode(); // TODO: Enter interactive mode
			break;

		}

		case 1: { // Transaction Type
			if (templateEntry.type.isFixed) {
				templateEntry.type.reset();

				templateEntry.transCat.reset();
				templateEntry.transChild.reset();

				templateEntry.accCat.reset();
				templateEntry.accChild.reset();

			}
			else {
				lockTransactionType();
			}
			break;

		}
		case 2: { // Transaction Category ("Car")
			// Reset if transCat is fixed
			if (templateEntry.transCat.isFixed) {
				templateEntry.transCat.reset();
				templateEntry.transChild.reset();
				break;
			}

			if (templateEntry.type.value != "Transfer") {
				goto InvalidSelection;
			}
			else {
				lockTransCat();

			}
			break;

		}
		case 21: { // Transaction Child ("Fuel")
			// Reset if transChild is fixed
			if (templateEntry.transChild.isFixed) {
				templateEntry.transChild.reset();
				break;
			}

			if ((templateEntry.type.value != "Transfer") || !templateEntry.transCat.isFixed) {
				goto InvalidSelection;
			}
			else {
				lockTransChild();

			}
			break;

		}
		case 3: {
			// Reset if accCat is fixed
			if (templateEntry.accCat.isFixed) {
				templateEntry.accCat.reset();
				templateEntry.accChild.reset();
				break;
			}

			if (templateEntry.type.value != "Transfer") {
				goto InvalidSelection;
			}
			else {
				lockAccCat();

			}
			break;
		}
		case 31: {
			// Reset if accCat is fixed
			if (templateEntry.accChild.isFixed) {
				templateEntry.accChild.reset();
				break;
			}

			if ((templateEntry.type.value != "Transfer") || !templateEntry.accCat.isFixed) {
				goto InvalidSelection;
			}
			else {
				lockAccChild();

			}
			break;

		}
		case 4: {
			// Reset if sourceAccCat is fixed
			if (templateEntry.sourceAccCat.isFixed) {
				templateEntry.sourceAccCat.reset();
				templateEntry.sourceAccChild.reset();
				break;
			}

			if ((templateEntry.type.value != "Expense") && (templateEntry.type.value != "Income")) {
				goto InvalidSelection;
			}
			else {
				lockTransferSourceCategory();

			}
			break;

		}
		case 41: {
			// Reset if sourceAccChild is fixed
			if (templateEntry.sourceAccChild.isFixed) {
				templateEntry.sourceAccChild.reset();
				break;
			}

			if (((templateEntry.type.value != "Expense") && (templateEntry.type.value != "Income"))
				|| !templateEntry.sourceAccCat.isFixed) {
				goto InvalidSelection;
			}
			else {
				lockTransferSourceChild();

			}
			break;

		}
		case 5: {
			// Reset if destAccCat is fixed
			if (templateEntry.destAccCat.isFixed) {
				templateEntry.destAccCat.reset();
				templateEntry.destAccChild.reset();
				break;
			}

			if ((templateEntry.type.value != "Expense") && (templateEntry.type.value != "Income")) {
				goto InvalidSelection;
			}
			else {
				lockTransferDestinationCategory();

			}
			break;

		}
		case 51: {
			// Reset if destAccChild is fixed
			if (templateEntry.destAccChild.isFixed) {
				templateEntry.destAccChild.reset();
				break;
			}

			if (((templateEntry.type.value != "Expense") && (templateEntry.type.value != "Income"))
				|| !templateEntry.destAccChild.isFixed) {
				goto InvalidSelection;
			}
			else {
				lockTransferDestinationChild();

			}
			break;

		}
		case 6: { // Date-time interactive mode
			// Reset if any datetime is fixed
			if (templateEntry.is_dateTime_locked()) {
				templateEntry.year.reset();
				templateEntry.month.reset();
				templateEntry.day.reset();
				templateEntry.hour.reset();
				templateEntry.mins.reset();
			}
			else {
				dtInteractive();
			}
			break;

		}
		case 61: { // Lock year
			templateEntry.year.isFixed ?
				templateEntry.year.reset() :
				lockYear();
			break;

		}
		case 62: { // Lock month
			templateEntry.month.isFixed ?
				templateEntry.month.reset() :
				lockMonth();
			break;

		}
		case 63: { // Lock day
			templateEntry.day.isFixed ?
				templateEntry.day.reset() :
				lockDay();
			break;

		}
		case 64: { // Lock hour
			templateEntry.hour.isFixed ?
				templateEntry.hour.reset() :
				lockHour();
			break;

		}
		case 65: { // Lock mins
			templateEntry.mins.isFixed ?
				templateEntry.mins.reset() :
				lockMins();
			break;

		}
		case 7: { // Lock title
			templateEntry.title.isFixed ?
				templateEntry.title.reset() :
				lockTitle();
			break;

		}
		case 71: { // Lock notes
			templateEntry.notes.isFixed ?
				templateEntry.notes.reset() :
				lockNotes();
			break;

		}
		case 8: {
			templateEntry.status.isFixed ?
				templateEntry.status.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 9:
			return templateEntry;
			break;
		InvalidSelection:
		default:
			cout << "Invalid Selection!" << endl;
			pause();
			break;
		}
		pause();
	}

}