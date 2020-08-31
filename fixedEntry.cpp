#include "entryDataStruct.h"
#include "utils.h"

const int FIXED_MENU_SIZE = 10;

ENTRY* entry;
json props;

void outArray(bool, int type = -1, int cat = -1);

void lockTransactionType() {
	heading("Lock Transaction Type");
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
			entry->type.value = returnString(props["presetLists"][userInput]["type"]);
			break;
		case 5:
			entry->type.value = "Transfer";
			entry->transCat.value = "(Transfer)";
			entry->transChild.value = "(Transfer)";
			entry->transCat.isUsed = true;
			entry->transCat.isFixed = true;
			entry->transChild.isUsed = true;
			entry->transChild.isFixed = true;
			break;
		default:
			cout << "Illegal action!" << endl;
			system("pause");
			continue;
		}

		entry->type.isUsed = true;
		entry->type.isFixed = true;
		break;
	}
}

void resetTransactionType() {
	entry->type.reset();

	entry->transCat.reset();
	entry->transChild.reset();

	entry->accCat.reset();
	entry->accChild.reset();
}

void fixedEntryMenu(json myProperties, ENTRY* myEntry) {
	entry = myEntry;
	props = myProperties;

	while (true) {
		heading("Lock entry menu");
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

		entry->is_anything_locked() ?
			menu.push_back({ 0, "[!!!] Unlock everything" }) :
			menu.push_back({ 0, "Interactive Lock, if \"enter\" without selecting anything means ignore / don't lock." });

		// Menu entry for transaction type
		entry->type.isFixed ?
			menu.push_back({ 1, "[!] Reset Transaction Type, Current: " + entry->type.value }) :
			menu.push_back({ 1, "Lock Transaction Type" });


		// Show this section for expenses and income
		if ((entry->type.value == "Expense" && entry->type.isFixed) ||
			(entry->type.value == "Income" && entry->type.isFixed)) {
			menu.push_back({ 0, "" });

			// Option to lock transaction category & child if entry type is expense & income
			if (entry->transCat.isFixed) {
				menu.push_back({ 2, "[!] Reset " + entry->type.value + " Category, Current: " + entry->transCat.value });

				entry->transChild.isFixed ?
					menu.push_back({ 21, "[!] Reset " + entry->type.value + " Category Child, Current: " + entry->transChild.value }) :
					menu.push_back({ 21, "Lock " + entry->type.value + " Category Child" });

			}
			else {
				menu.push_back({ 2, "Lock " + entry->type.value + " Category" });

			}

			// Option to lock target account category & children type
			if (entry->accCat.isFixed) {
				menu.push_back({ 3, "[!] Reset " + entry->type.value + " Account Category, Current: " + entry->accCat.value });

				entry->accChild.isFixed ?
					menu.push_back({ 31, "[!] Reset " + entry->type.value + " Account Category Child, Current: " + entry->accChild.value }) :
					menu.push_back({ 31, "Lock " + entry->type.value + " Account Category Child" });

			}
			else {
				menu.push_back({ 3, "Lock " + entry->type.value + " Account Category" });

			}

		}
		// Else show this for transfers
		else if (entry->type.value == "Transfer" && entry->type.isFixed) {
			menu.push_back({ 0, "" });

			// Option to lock source account category & children type
			if (entry->sourceAccCat.isFixed) {
				menu.push_back({ 4, "[!] Reset " + entry->type.value + " Source Account Category, Current: " + entry->sourceAccCat.value });

				entry->sourceAccChild.isFixed ?
					menu.push_back({ 41, "[!] Reset " + entry->type.value + " Source Account Category Child, Current: " + entry->sourceAccChild.value }) :
					menu.push_back({ 41, "Lock " + entry->type.value + " Source Account Category Child" });

			}
			else {
				menu.push_back({ 4, "Lock " + entry->type.value + " Source Account Category" });

			}

			// Option to lock destination account category & children type
			if (entry->destAccCat.isFixed) {
				menu.push_back({ 5, "[!] Reset " + entry->type.value + " Destination Account Category, Current: " + entry->destAccCat.value });

				entry->destAccChild.isFixed ?
					menu.push_back({ 51, "[!] Reset " + entry->type.value + " Destination Account Category Child, Current: " + entry->destAccChild.value }) :
					menu.push_back({ 51, "Lock " + entry->type.value + " Destination Account Category Child" });

			}
			else {
				menu.push_back({ 5, "Lock " + entry->type.value + " Destination Account Category" });

			}
		}

		menu.push_back({ 0, "" });

		// Date time (Interactive)
		if (entry->is_dateTime_locked()) {
			string dtString = "";

			entry->year.isFixed ?
				dtString += return_fixed_digits(entry->year.value, 4) :
				dtString += "----";

			dtString += "/";

			entry->month.isFixed ?
				dtString += return_fixed_digits(entry->month.value, 2) :
				dtString += "--";

			dtString += "/";

			entry->day.isFixed ?
				dtString += return_fixed_digits(entry->day.value, 2) :
				dtString += "--";

			dtString += " ";

			entry->hour.isFixed ?
				dtString += return_fixed_digits(entry->hour.value, 2) :
				dtString += "--";

			dtString += ":";

			entry->mins.isFixed ?
				dtString += return_fixed_digits(entry->mins.value, 2) :
				dtString += "--";

			menu.push_back({ 6, "[!] Reset Datetime, Current: " + dtString });

		}
		else {
			menu.push_back({ 6, "Lock Datetime (Interactive)" });

		}

		entry->year.isFixed ?
			menu.push_back({ 61, "[!] Reset Year, Current: " + entry->year.value }) :
			menu.push_back({ 61, "Lock Year" });

		entry->month.isFixed ?
			menu.push_back({ 62, "[!] Reset Month, Current: " + entry->month.value }) :
			menu.push_back({ 62, "Lock Month" });

		entry->day.isFixed ?
			menu.push_back({ 63, "[!] Reset Day, Current: " + entry->day.value }) :
			menu.push_back({ 63, "Lock Day" });

		entry->hour.isFixed ?
			menu.push_back({ 64, "[!] Reset Hour, Current: " + entry->hour.value }) :
			menu.push_back({ 64, "Lock Hour" });

		entry->mins.isFixed ?
			menu.push_back({ 64, "[!] Reset Minutes, Current: " + entry->mins.value }) :
			menu.push_back({ 64, "Lock Minutes" });

		entry->title.isFixed ?
			menu.push_back({ 7, "[!] Reset Title, Current: " + entry->title.value }) :
			menu.push_back({ 7, "Lock Title" });

		menu.push_back({ 0, "" });

		entry->notes.isFixed ?
			menu.push_back({ 71, "[!] Reset Notes, Current: " + entry->notes.value }) :
			menu.push_back({ 71, "Lock Notes" });

		entry->status.isFixed ?
			menu.push_back({ 8, "[!] Reset Status, Current: " + entry->status.value }) :
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
			entry->is_anything_locked() ?
				0 : // TODO: Reset everything 
				0; // TODO: Enter interactive mode
			break;

		}
		case 1: { // Transaction Type
			entry->type.isFixed ?
				resetTransactionType() :
				lockTransactionType();
			break;

		}
		case 2: { // Transaction Category ("Car")
			// Reset if transCat is fixed
			if (entry->transCat.isFixed) {
				entry->transCat.reset();
				entry->transChild.reset();
				break;
			}

			if (entry->type.value != "Transfer") {
				goto InvalidSelection;
			}
			else {
				// TODO: Do Stuff -- transCat

			}
			break;

		}
		case 21: { // Transaction Child ("Fuel")
			// Reset if transChild is fixed
			if (entry->transChild.isFixed) {
				entry->transChild.reset();
				break;
			}

			if ((entry->type.value != "Transfer") && !entry->transCat.isFixed) {
				goto InvalidSelection;
			}
			else {
				// TODO: Do Stuff -- transChild

			}
			break;

		}
		case 3: {
			// Reset if accCat is fixed
			if (entry->accCat.isFixed) {
				entry->accCat.reset();
				entry->accChild.reset();
				break;
			}

			if (entry->type.value != "Transfer") {
				goto InvalidSelection;
			}
			else {
				// TODO: Do Stuff -- transCat

			}
			break;
		}
		case 31: {
			// Reset if accCat is fixed
			if (entry->accChild.isFixed) {
				entry->accChild.reset();
				break;
			}

			if ((entry->type.value != "Transfer") && !entry->accCat.isFixed) {
				goto InvalidSelection;
			}
			else {
				// TODO: Do Stuff -- accChild

			}
			break;

		}
		case 4: {
			// Reset if sourceAccCat is fixed
			if (entry->sourceAccCat.isFixed) {
				entry->sourceAccCat.reset();
				entry->sourceAccChild.reset();
				break;
			}

			if ((entry->type.value != "Expense") || (entry->type.value != "Income")) {
				goto InvalidSelection;
			}
			else {
				// TODO: Do Stuff -- sourceAccCat

			}
			break;

		}
		case 41: {
			// Reset if sourceAccChild is fixed
			if (entry->sourceAccChild.isFixed) {
				entry->sourceAccChild.reset();
				break;
			}

			if ((entry->type.value != "Expense") || (entry->type.value != "Income")
				|| !entry->sourceAccCat.isFixed) {
				goto InvalidSelection;
			}
			else {
				// TODO: Do Stuff -- sourceAccCat

			}
			break;

		}
		case 5: {
			// Reset if destAccCat is fixed
			if (entry->destAccCat.isFixed) {
				entry->destAccCat.reset();
				entry->destAccChild.reset();
				break;
			}

			if ((entry->type.value != "Expense") || (entry->type.value != "Income")) {
				goto InvalidSelection;
			}
			else {
				// TODO: Do Stuff -- destAccCat

			}
			break;

		}
		case 51: {
			// Reset if destAccChild is fixed
			if (entry->destAccChild.isFixed) {
				entry->destAccChild.reset();
				break;
			}

			if ((entry->type.value != "Expense") || (entry->type.value != "Income")
				|| !entry->destAccChild.isFixed) {
				goto InvalidSelection;
			}
			else {
				// TODO: Do Stuff -- destAccChild

			}
			break;

		}
		case 6: { // Date-time interactive mode
			// Reset if any datetime is fixed
			if (entry->is_dateTime_locked()) {
				entry->year.reset();
				entry->month.reset();
				entry->day.reset();
				entry->hour.reset();
				entry->mins.reset();
			}
			else {
			}// TODO: Enter interactive mode
			break;

		}
		case 61: {
			entry->year.isFixed ?
				entry->year.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 62: {
			entry->month.isFixed ?
				entry->month.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 63: {
			entry->day.isFixed ?
				entry->day.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 64: {
			entry->hour.isFixed ?
				entry->hour.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 65: {
			entry->mins.isFixed ?
				entry->mins.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 7: {
			entry->title.isFixed ?
				entry->title.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 71: {
			entry->notes.isFixed ?
				entry->notes.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 8: {
			entry->status.isFixed ?
				entry->status.reset() :
				emptyVoidFunction(); // TODO: Enter interactive mode
			break;

		}
		case 9:
			return;
			break;
		InvalidSelection:
		default:
			cout << "Invalid Selection!" << endl;
			pause();
			break;
		}

	}
}