/***********************************************************************
// OOP244 Workshop 2: Dynamic Memory & Function Overloading 
// File GiftMain.cpp
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
using namespace std;
using namespace sdds;

int main() {
  int numberOfGifts = 0; 

  Gift *gift = nullptr;
  cout << "Enter number of Gifts to allocate: ";
  cin >> numberOfGifts;

  if (numberOfGifts < 1) return 1;
  gift = new Gift[numberOfGifts];
  
  for (int i = 0; i < numberOfGifts; ++i) {
    cout << "Gift #" << i + 1 << ": " << endl;
	//function allows user to input description of a gift
	gifting(gift[i].g_description);
    cin.ignore(2000,'\n');
	//function allows user to input price of a gift
	gifting(gift[i].g_price);
    cin.ignore(2000,'\n'); 
	//function allows user to input units of a gift
	gifting(gift[i].g_units);
    cin.ignore(2000, '\n');
    cout << endl;
  }

  for (int i=0; i < numberOfGifts; ++i) { 
	 cout << "Gift #"; 
	 cout << i+1 << ": " << endl;
	 //function will display information about each gift
	 display(gift[i]);
	 printf("\n");
	 
  }
  
  delete [] gift;
  gift = nullptr;
  return 0;
}