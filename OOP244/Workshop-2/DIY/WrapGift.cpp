/***********************************************************************
// OOP244 Workshop 2: Dynamic Memory & Function Overloading
// File WrapGift.cpp
// Version 1.0
// Date	2020/01/05
// Author Michael Huang
// Description
// Tests Gift module and provides a set of TODOs to complete
// which the main focuses are dynamic memory allocation
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// 
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include <iostream>
#include "Gift.h"
#include "Gift.h" // intentional
using namespace std;
using namespace sdds;

void initWrap(Gift& g) {
  g.wrap = nullptr;
  g.wrap_layers = 0;
}

ostream& line(int len, char ch) {
	for (int i = 0; i < len; i++, cout << ch);
	return cout;
}
ostream& number(int num) {
	cout << num;
	for (int i = 0; i < 9; i++) {
		cout << " - " << num;
	}
	return cout;
}

int main() {

  Gift g1, g2; // Unwrapped Gifts

  cout << "Preparing an empty Gift to be wrapped and display it" << endl;
  line(64, '-') << endl; number(1) << endl;
  gifting(g1.g_description);
  gifting(g1.g_price);
  gifting(g1.g_units);
  initWrap(g1); cout << endl;
  display(g1);

  cout << "\nAttempting to wrap the previous Gift: " << g1.g_description << endl;
  line(64, '-') << endl; number(2) << endl;
  if (wrap(g1)) cout << "Success!" << endl; else cout << "Wrapping failure!" << endl;

  cout << "\nAttempting to rewrap the previous Gift: " << g1.g_description << endl;
  line(64, '-') << endl; number(3) << endl;
  if (!wrap(g1)) cout << "Success2!" << endl; else cout << "Already wrapped failure!" << endl;

  cout << "\nAttempting to unwrap the previous Gift: " << g1.g_description << endl;
  line(64, '-') << endl; number(4) << endl;
  if (unwrap(g1)) cout << "Success3!" << endl; else cout << "Unwrapping failure!" << endl;

  cout << "\nAttempting to un-unwrap the previous Gift: " << g1.g_description << endl;
  line(64, '-') << endl; number(5) << endl;
  if (!unwrap(g1)) cout << "Success4!" << endl; else cout << "Already unwrapped failure!" << endl;

  cout << "\nPrepare another empty Gift via the combined function and display it" << endl;
  line(64, '-') << endl; number(6) << endl;
  initWrap(g2);
  gifting(g2); cout << endl;
  display(g2);

  cout << "\nEnd of main" << endl;
  unwrap(g2); // Unwrap in the end
  return 0;
}
