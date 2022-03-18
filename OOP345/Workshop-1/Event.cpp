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
