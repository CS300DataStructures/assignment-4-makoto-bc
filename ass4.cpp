// assignment-4
// Makoto Emura
// 10/24/2020
// Linked list string

#include <iostream>
#include "SLLString.h"

using namespace std;

int main() {
	SLLString str("Hello world!");
	auto newStr = new SLLString;

	newStr = &str;
	*newStr += SLLString(" CS@BC");
	(*newStr)[6] = 'W';

	cout << *newStr << endl; // Hello World! CS@BC
	cout << newStr->length() << endl; //18

	int loc = newStr->findSubstring(SLLString("World"));
	cout << loc << endl; // 6

	newStr->erase('l'); //erase the letter l.
	cout << *newStr << endl; // Heo Word! CS@BC

	newStr->erase('C');
	cout << *newStr << endl; // Heo Word! S@B

	return 0;
}
