/* Name: Kairat Orozobekov
   Student ID: 104 998 190
   Email: korozobekov@myseneca.ca
   Section: NAB */

// Gift.cpp
// Gift.cpp
#include "Gift.h"
#include <iostream>
#include <cstring>
using namespace std;


namespace sdds
{
	void gifting(char* descript)
	{
		cout << "Enter gift description: ";
		cin.width(16);
		cin >> descript;
	}

	void gifting(double& cost)
	{
		cout << "Enter gift price: ";
		cin >> cost;
		if (cost<0 || cost>MAX_PRICE)
		{
			while (cost<0 || cost>MAX_PRICE)
			{
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
			while (amount < 1)
			{
				cout << "Gift units must be at least 1" << endl;
				cout << "Enter gift units: ";
				cin >> amount;
			}
		}
	}

	void gifting(Gift& wrapping)
	{
		cout << "Preparing a gift..." << endl;
		gifting(wrapping.g_description);
		gifting(wrapping.g_price);
		gifting(wrapping.g_units);
		wrap(wrapping);
	}

	void display(const Gift& info)
	{
		if (info.wrap == 0)
		{
		cout << "Gift Details:" << endl;
		cout << "Description: " << info.g_description << endl;
		cout << "Price: " << info.g_price << endl;
		cout << "Units: " << info.g_units << endl;
		cout << "Unwrapped" << endl;
		}
		else
		{
		cout << "Gift Details:" << endl;
		cout << "Description: " << info.g_description << endl;
		cout << "Price: " << info.g_price << endl;
		cout << "Units: " << info.g_units << endl;
		cout << "Wrap Layers: " << info.wrap_layers << endl;
		for (int i = 0; i < info.wrap_layers; i++)
		{
			cout << "Wrap #" << i+1 << ": " << info.wrap[i].pattern << endl;
		}
		}
	}

	bool wrap(Gift& gift)
	{
		int strlenght = 0;
		char temp_pattern[pattern];
		if (gift.wrap_layers <1)
		{	
			cout << "Wrapping gifts..." << endl;
			while (gift.wrap_layers < 1)
			{
				cout << "Enter the number of wrapping layers for the Gift: ";
				cin >> gift.wrap_layers;
				if (gift.wrap_layers < 1)
				{
					
					cout << "Layers at minimum must be 1, try again." << endl;
				}
			}
			gift.wrap = new Wrapping[gift.wrap_layers];
			for (int i = 0; i < gift.wrap_layers; i++)
			{
				cout << "Enter wrapping pattern #" << i+1 << ": ";
				cin >> temp_pattern;
				strlenght = strlen(temp_pattern) + 1;
				gift.wrap[i].pattern = new char [strlenght];
				strcpy(gift.wrap[i].pattern, temp_pattern);
			}
			return true;
		}
		else
		{
			cout << "Gift is already wrapped!" << endl;
			return false;
		}
	}

	bool unwrap(Gift& unwrapgift)
	{
		
		if (unwrapgift.wrap == 0)
		{
			cout << "Gift isn't wrapped! Can't unwrap." << endl;
			return false;
		}
		else
		{
			cout << "Gift being unwrapped." << endl;
			for (int i = 0; i < unwrapgift.wrap_layers; i++)
			{
				delete[] unwrapgift.wrap[i].pattern;
				unwrapgift.wrap[i].pattern = nullptr;
			}
			delete[] unwrapgift.wrap;
			unwrapgift.wrap = nullptr;
			unwrapgift.wrap_layers = 0;
			return true;
		}
	}
}