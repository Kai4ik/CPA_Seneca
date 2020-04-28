/***********************************************************************
// OOP244 Workshop 3: Classes & Privacy
// File TrainTester2.cpp
// Version 1.0
// Date	2020/01/19
// Author Michael Huang
// Description
// Tests updated Train module
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

  Cargo c1, c2;
  c1.init("Boxes", -5000); 
  c2.init("Flowers", 5000);
  Train t1, t2;

  cout << "\nSet each Train to a non empty state, load cargo and display" << endl;
  line(64, '-') << endl; number(1) << endl;
  t1.setTrain("Birthday Train", 1);
  t2.setTrain("Choo Choo Train", 2);
  t1.loadCargo(c1); 
  t1.display(); 
  cout << endl; 
  t2.display();

  cout << "\nIncrease cargo weight in a train and display" << endl;
  line(64, '-') << endl; number(2) << endl;
  if (t1.increaseCargo(50)) cout << "t1 cargo was correctly increased" << endl;
  if (t1.increaseCargo(999)) cout << "t1 cargo was correctly increased to MAX_WEIGHT" << endl;
  if (!t1.increaseCargo(999)) cout << "t1 cargo was correctly not increased" << endl;
  cout << endl; 
  t1.display();

  cout << "\nDecrease cargo weight in a train with no cargo and display" << endl;
  line(64, '-') << endl; number(3) << endl;
  if (!t2.decreaseCargo(25)) cout << "t2 doesn't have cargo was correctly not touched" << endl;
  t2.loadCargo(c2);
  if (!t2.decreaseCargo(25)) cout << "t2 after loading cargo was correctly not decreased below MIN_WEIGHT" << endl;
  t2.increaseCargo(50); 
  if (t2.decreaseCargo(10)) cout << "t2 decreased weight correctly" << endl;
  cout << endl; 
  t2.display();

  cout << "\nSwap cargo between train t1 and t2" << endl;
  line(64, '-') << endl; number(4) << endl;
  t1.swapCargo(t2);
  t1.display(); 
  cout << endl; 
  t2.display();

  cout << "\nUnload Cargo from each Train and attempt to swap" << endl;
  line(64, '-') << endl; number(5) << endl;
  t1.unloadCargo(); 
  t2.unloadCargo(); 
  if (!t1.swapCargo(t2)) cout << "correctly did not attempt to swap train without cargo" << endl;
  cout << endl;  
  t1.display(); 
  cout << endl; 
  t2.display();

  return 0;
}
