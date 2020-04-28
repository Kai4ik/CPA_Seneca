/* Name: Kairat Orozobekov
   Student ID: 104 998 190
   Email: korozobekov@myseneca.ca
   Section: NAB */

//Train.cpp
#pragma warning(disable : 4996)
#include "Train.h"
#include <iostream>
#include <string.h>
using namespace std;

namespace sdds
{
	
	void Train::setTrain(const char* name, int id)
	{
		 if (name == nullptr || strlen(name) < 1 || id < 1)
		{
			 id = 0;
			 Train::name[0] = '\0';
		}
		else
		{
			Train::id = id;
			Train::cargo = nullptr;
			strcpy(Train::name, name);
		}
	}


	bool Train::isEmpty() const
	{
		if (name == nullptr || strlen(name) < 1 || id < 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Train::display() const
	{
		cout << "***Train Summary***" << endl;
		if (isEmpty() == true)
		{
			cout << "This is an empty train." << endl;
		}
		else
		{
			cout << "Name: " << Train::name << " ID: " << Train::id << endl;
			if (Train::cargo != nullptr)
			{
				cout << "Cargo: " << Train::cargo->description << " Weight: " << Train::cargo->weight << endl;
			}
			else
			{
				cout << "No cargo on this train." << endl;
			}
		}
	}

	void Train::loadCargo(Cargo goods)
	{
		cargo = new Cargo;
		strcpy(cargo->description, goods.description);
		cargo->weight = goods.weight;
	}

	void Train::unloadCargo()
	{
		delete Train::cargo;
		Train::cargo = nullptr;

	}
}
