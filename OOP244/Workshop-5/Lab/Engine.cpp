/**********************************************************
 * Name: Kairat Orozobekov
 * Student ID: 104 998 190
 * Seneca email: korozobekov@myseneca.ca
 * Section: NBB
 **********************************************************/

#include "Engine.h"
#include <iostream>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

namespace sdds
{
	Engine::Engine()
	{
		setEmp();
	}

	Engine::Engine(const char* tengine,double cap)
	{
		if (tengine != nullptr || size > 0)
		{
			size = cap;
			strcpy(type, tengine);
		}
		
	}

	double sdds::Engine::get() const
	{
		return size;
	}

	void sdds::Engine::display() const
	{
	
		cout << size << " liters - " << type << endl;
	}


	void Engine::setEmp()
	{
			size = 0;
			type[0] = '\0';
	}
}
