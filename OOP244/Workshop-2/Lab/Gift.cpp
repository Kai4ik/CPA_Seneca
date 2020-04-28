// Gift.cpp
/* Name: Kairat Orozobekov
   Student ID: 104 998 190
   Email: korozobekov@myseneca.ca
   Section: NAB */
   
#include "Gift.h"
#include <iostream>
using namespace std;


namespace sdds {
	void gifting(char* descript)
	{
		cout << "Enter gift description: ";
		cin.width(16);
		cin >> descript;
	}

	void gifting(double &cost)
	{
		cout << "Enter gift price: ";
		cin >> cost;
		if (cost<0 || cost>MAX_PRICE)
		{
			while (cost<0 || cost>MAX_PRICE) { 
			cout << "Gift price must be between 0 and " << MAX_PRICE << endl;
			cout << "Enter gift price: ";
			cin >> cost;
			}
		}
	}

	void gifting(int& amount)
	{
		cout << "Enter gift units: ";
		cin >> amount;
		if (amount < 1)
		{
			while (amount < 1) { 
			cout << "Gift units must be at least 1" << endl;
			cout << "Enter gift units: ";
			cin >> amount;
			}
		}
	}

	void display(const Gift& info)
	{
		cout << "Gift Details:" << endl;
		cout << "Description: " << info.g_description << endl;
		cout << "Price: " << info.g_price << endl;
		cout << "Units: " << info.g_units << endl;
	}
	
}
