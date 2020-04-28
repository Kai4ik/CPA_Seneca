//Train.cpp
/* Name: Kairat Orozobekov
   Student ID: 104 998 190
   Email: korozobekov@myseneca.ca
   Section: NAB */

#include "Train.h"
#include <iostream>
#include <iomanip>
#include <cstring>
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
				cout << fixed << setprecision(2);
				cout << "Cargo: " << cargo->getDescrip() << " Weight: " << cargo->get_weight() << endl;
			}
			else
			{
				cout << "No cargo on this train." << endl;
			}
		}
	}


	//function to load cargo
	void Train::loadCargo(Cargo& goods)
	{
		cargo = new Cargo;
		cargo->setDescript(goods.getDescrip());
		cargo->setWeight(goods.get_weight());
	}


	//function to unload cargo
	void Train::unloadCargo()
	{
		delete Train::cargo;
		Train::cargo = nullptr;
	}

	 
	//function to increase weight of cargo
	bool Train::increaseCargo(double numb)
	{
		if (Train::cargo == nullptr || cargo->get_weight() == MAX_WEIGHT)
		{
			return false;
		}
		else
		{
			if (numb + cargo->get_weight() < MAX_WEIGHT)
			{
				Train::cargo->setWeight(numb + cargo->get_weight());
				return true;
			}
			else
			{
				Train::cargo->setWeight(MAX_WEIGHT);
				return true;
			}
		}
	}


	//function to decrease weight of cargo
	bool Train::decreaseCargo(double decline)
	{
		if (Train::cargo == nullptr || cargo->get_weight() == MIN_WEIGHT)
		{
			return false;
		}
		else
		{
			if (cargo->get_weight() - decline  > MIN_WEIGHT)
			{
				Train::cargo->setWeight(cargo->get_weight() - decline);
				return true;
			}
			else
			{
				Train::cargo->setWeight(MIN_WEIGHT);
				return true;
			}
		}
	}


	bool Train::swapCargo(Train& refer)
	{
		if (cargo == nullptr || refer.cargo == nullptr)
		{
			return false;
		}
		else
		{
			Cargo* third = cargo;
			cargo = refer.cargo;
			refer.cargo = third;
			return true;
		}
	}


	//function which checks values
	void Cargo::init(const char* desc, double weight2)
	{
		if (weight2 >= MIN_WEIGHT && weight2 <=MAX_WEIGHT)
		{
			setWeight(weight2);
		}
 		else
		{
			setWeight(MIN_WEIGHT);
		}
		if (strlen(desc) <= MAX_DESC + 1)
		{
			setDescript(desc);
		}
		else
		{
			setDescript("\0");
		}
	}

	//two getter functions
	const char* Cargo::getDescrip() const
	{
		return description;
	}

	double Cargo::get_weight() const
	{
		return weight;
	}

	//two setter functions
	void Cargo::setDescript(const char* desc)
	{
		strcpy(Cargo::description, desc);
	}


	void Cargo::setWeight(double weight66)
	{
		Cargo::weight = weight66;
	}
}

