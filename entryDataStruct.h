#pragma once

#include "./utils.h"

// Used to store current entry before writing into file.
struct ENTRY {
	template <typename T1>
	struct DATA_ROW {
		T1 value;
		bool isUsed = false;
		bool isFixed = false;
	};

	// Transaction type
	DATA_ROW<string> type;

	// Transaction parent category & children type
	DATA_ROW<string> transCat, transChild;

	// Account parent category & children type
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

};
ENTRY entry;