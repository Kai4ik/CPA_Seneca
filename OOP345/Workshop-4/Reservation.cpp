/* Student name: Kairat Orozobekov
   Student #: 104 998 190
   Student email: korozobekov@myseneca.ca
   Date submitted: 2020.06.17
   Course: OOP345, Section NEE
   I have done all the coding by myself and only copied the code that my professor provided
   to complete my workshops and assignments.
*/

#include "Reservation.h"
#include <iostream>
#include <iomanip>

namespace sdds
{
	//function which erases part of string till defined delimiter
	void erasing(std::string& copy, char delim)
	{
		std::string delet;
		size_t comma = copy.find(delim);
		delet = copy.substr(0, comma);
		copy.erase(0, delet.size() + 1);
	}

	Reservation::Reservation()
	{
		name = "";
		email = "";
		day = 0;
		hour = 0;
		guests = 0;
		res_id[0] = '\0';
	}

	Reservation::Reservation(const std::string& reser)
	{
		std::string copy = reser;
		bool res;
		do
		{
			for (unsigned i = 0; i < copy.size(); ++i)
			{
				if (copy[i] == ' ')
				{
					copy.erase(copy.find(' '), 1);
					break;
				}
			}
			res = true;
			for (unsigned i = 0; i < copy.size(); ++i)
			{
				if (copy[i] == ' ')
				{
					res = false;
				}
			}
		} while (res == false);
		size_t colon = copy.find(":");
		res_id = copy.substr(0, colon);
		erasing(copy, ':');
		size_t comma = copy.find(",");
		name = copy.substr(0, comma);
		erasing(copy, ',');
		comma = copy.find(",");
		email = copy.substr(0, comma);
		erasing(copy,',');
		guests = std::stoi(copy.substr(0, comma));
		erasing(copy,',');
		day = std::stoi(copy.substr(0, comma));
		erasing(copy,',');
		hour = std::stoi(copy.substr(0, comma));
	}

	std::ostream& operator<<(std::ostream& os, const Reservation& obj)
	{
		os << "Reservation " << obj.res_id << ": " << std::setw(10) << std::right << obj.name << "  " << std::setw(20) << std::left << "<" + obj.email + ">";
		if (obj.hour >= 6 && obj.hour <= 9)
		{
			os << "    Breakfast ";
		}
		else if (obj.hour >= 11 && obj.hour <= 15)
		{
			os << "    Lunch ";
		}
		else if (obj.hour >= 17 && obj.hour <= 21)
		{
			os << "    Dinner ";
		}
		else
		{
			os << "    Drinks ";
		}
		os << "on day " << obj.day << " @ " << obj.hour << ":00 for " << obj.guests << " people." << std::endl;
		return os;
	}
}
