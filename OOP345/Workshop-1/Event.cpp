/* Student name: Kairat Orozobekov
   Student #: 104 998 190
   Student email: korozobekov@myseneca.ca
   Date submitted: 2020.05.26
   Course: OOP345, Section NEE
   I have done all the coding by myself and only copied the code that my professor provided 
   to complete my workshops and assignments. 
*/
#include "event.h"
#include <string.h>
#include <iostream>
#include <iomanip>

namespace sdds
{

	Event::Event()
	{
		time = 0;
		this->descrip = nullptr;
	}

	Event::~Event()
	{
		if (descrip != nullptr)
		{
			delete [] descrip;
			descrip = nullptr;
		}
		
	}

	void Event::display() const
	{
		static int counter = 1;
		if (this->descrip != nullptr)
		{
			
			int hours;
			if (time < 3600)
				hours = 00;
			else
				hours = time/ 60 / 60;
			int minutes = (time - (hours * 60 * 60)) / 60;
			int sec = (time - (hours * 60 * 60)) % 60;
			std::cout << std::setw(3) << std::setfill(' ') << counter << ". " << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << sec << " -> " << descrip;
			std::cout << std::endl;
		}
		else
		{
			std::cout << std::setw(3) << std::setfill(' ') << counter << ". " << "[ No Event ]" << std::endl;
		}
		counter++;
	}

	void Event::setDescription(char* desc)
	{
		if (desc != nullptr)
		{	
			if (descrip != nullptr) {
				descrip = nullptr;
			}
			descrip = new char[strlen(desc) + 1];
			strcpy(descrip, desc);
			time = g_sysClock;
		}
		else
		{
			this->descrip = nullptr;
			time = 0;
		}
	}

}
