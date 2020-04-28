/***********************************************************************
// OOP244 Workshop 3: Classes & Privacy
// File TrainTester.cpp
// Version 1.0
// Date	2020/01/19
// Author Michael Huang
// Description
// Tests Train module
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// 
/////////////////////////////////////////////////////////////////
***********************************************************************/

#include <iostream>
#include "Train.h"
#include "Train.h" // intentional
using namespace std;
using namespace sdds;

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

  sdds::Cargo c1{ "Boxes", 55.55 }; 
  sdds::Cargo c2{ "Flowers", 66.666 }; 
  sdds::Cargo c3{ "Ore", 77.7777 };

  cout << "Create a Train and attempt to set it (empty state)" << endl;
  line(64, '-') << endl; number(1) << endl;
  sdds::Train t1; 
  t1.setTrain(nullptr, 1);
  sdds::Train t2; 
  t2.setTrain("", 1);
  sdds::Train t3; 
  t3.setTrain("Birthday Train", -5);
  if (t1.isEmpty() && t2.isEmpty() && t3.isEmpty())
    cout << "Success! Each Train is in empty state" << endl;

  cout << "\nDisplay an empty Train" << endl;
  line(64, '-') << endl; number(2) << endl;
  t1.display();

  cout << "\nSet each Train to a non empty state" << endl;
  line(64, '-') << endl; number(3) << endl;
  t1.setTrain("Birthday Train", 1);
  t2.setTrain("Choo Choo Train", 2);
  t3.setTrain("Hype Train", 3);
  
  if (!t1.isEmpty() && !t2.isEmpty() && !t3.isEmpty())
    cout << "Success! Each Train is in non empty state" << endl;

  cout << "\nDisplay each non empty Train" << endl;
  line(64, '-') << endl; number(4) << endl;
  t1.display(); cout << endl; 
  t2.display(); cout << endl; 
  t3.display(); cout << endl; 

  cout << "\nLoad Cargo onto a Train and Display" << endl;
  line(64, '-') << endl; number(5) << endl;
  t1.loadCargo(c1); 
  t2.loadCargo(c2); 
  t3.loadCargo(c3);
  t1.display(); cout << endl; 
  t2.display(); cout << endl; 
  t3.display(); cout << endl; 

  cout << "\nUnload Cargo from each Train and Display" << endl;
  line(64, '-') << endl; number(6) << endl;
  t1.unloadCargo(); 
  t2.unloadCargo(); 
  t3.unloadCargo();
  t1.display(); cout << endl; 
  t2.display(); cout << endl; 
  t3.display(); cout << endl; 

  return 0;
}
