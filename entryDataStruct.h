#pragma once

#include "./utils.h"

// Used to store current entry before writing into file.
struct ENTRY {
	string type = "";			// Transaction category.
	string transCat = "";		// Transaction parent.
	string transChild = "";		// Transaction child.
	string accCat = "";			// Account category.
	string accChild = "";		// Account child.
	unsigned short int		// Date & time.
		year = 0,
		month = 0,
		day = 0,
		hour = 1000,
		mins = 1000;
	double amount = 3.14159265359;
	string title = "";			// Title of transaction.
	string notes = "";
	char status = '\0';
	string label = "";

	// Special variables for transfers
	string sourceAccCat = "";
	string sourceAccChild = "";
	string destAccCat = "";
	string destAccChild = "";
};
ENTRY entry;