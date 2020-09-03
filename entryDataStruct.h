#pragma once

#include "includeHeaders.h"

// Datatype for datarow

// Used to store current entry before writing into file.
struct ENTRY {
	template <typename T1>
	struct DATA_ROW {
		T1 value;
		bool isUsed = false;
		bool isFixed = false;
		int fixedIndex = -1;

		// Resets the value to the default of that datatype
		void reset() {
			T1 tempValue{};
			value = {};
			isUsed = false;
			isFixed = false;
			fixedIndex = -1;
		}

		void set(T1 userInput) {
			value = userInput;
			isUsed = true;
		}

		void set(T1 userInput, int index) {
			fixedIndex = index;
			set(userInput);
		}

		void fix(T1 userInput) {
			value = userInput;
			isUsed = true;
			isFixed = true;
		}

		void fix(T1 userInput, int index) {
			fixedIndex = index;
			fix(userInput);
		}

		// Resets value, isUsed
		void reset_input() {
			if (!isFixed) {
				T1 tempValue{};
				value = {};
				isUsed = false;
				fixedIndex = -1;

			}
		}

	};
	// Transaction type
	DATA_ROW<string> type;

	/* Transaction parent category & children type, e.g. Car -> Fuel
	- If type is "Transfer", both of these are "(Transfer)"
	*/
	DATA_ROW<string> transCat, transChild;

	// Account parent category & children type, only used for non-transfers
	// E.g. Bank -> RHB Bank
	DATA_ROW<string> accCat, accChild;

	// Date data declarations
	DATA_ROW<unsigned short int> year, month, day, hour, mins;

	// Transaction amount
	DATA_ROW<double> amount;

	// Transaction title
	DATA_ROW<string> title;

	// Transaction notes
	DATA_ROW<string> notes;

	// Transaction label
	DATA_ROW<string> label;

	// Transaction status
	DATA_ROW<char> status;

	// Special variables for transfers
	DATA_ROW<string> sourceAccCat, sourceAccChild, destAccCat, destAccChild;

	// If there is even one field locked it will return true
	bool is_anything_locked() {
		if (type.isFixed) return true;
		if (transCat.isFixed) return true;
		if (transChild.isFixed) return true;
		if (accCat.isFixed) return true;
		if (accChild.isFixed) return true;
		if (year.isFixed) return true;
		if (month.isFixed) return true;
		if (day.isFixed) return true;
		if (hour.isFixed) return true;
		if (mins.isFixed) return true;
		if (amount.isFixed) return true;
		if (title.isFixed) return true;
		if (notes.isFixed) return true;
		if (label.isFixed) return true;
		if (status.isFixed) return true;
		if (sourceAccCat.isFixed) return true;
		if (sourceAccChild.isFixed) return true;
		if (destAccCat.isFixed) return true;
		if (destAccChild.isFixed) return true;

		return false;

	}

	bool is_dateTime_locked() {
		if (year.isFixed) return true;
		if (month.isFixed) return true;
		if (day.isFixed) return true;
		if (hour.isFixed) return true;
		if (mins.isFixed) return true;

		return false;
	}
};

