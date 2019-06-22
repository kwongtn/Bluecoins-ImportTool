#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

// Outputs a line of j length of character k.
void line(int j = 50, char k = '=', bool nextLineAtEnd = true) {
	for (int i = 0; i < j; i++) {
		cout << k;
	}
	if (nextLineAtEnd) {
		cout << endl;
	}
}

// Outputs
// --------------------------------------------------
// ID   Details
// --------------------------------------------------
void attrib() {
	line(50, '-');
	cout << left << setw(5) << "ID" << "Description" << endl;
	line(50, '-');
}

