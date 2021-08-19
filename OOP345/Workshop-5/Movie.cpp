#include "Movie.h"
#include <iostream>
#include <iomanip>

namespace sdds
{
	void merasing(std::string& copy)
	{
		std::string delet;
		size_t comma = copy.find(",");
		delet = copy.substr(0, comma);
		copy.erase(0, delet.size() + 1);
	}

	sdds::Movie::Movie(const std::string& strMovie)
	{
		std::string copy = strMovie;
		std::string delet;
		bool res;
		int occur = 0;
		do
		{
			bool del = false;
			for (unsigned i = 0; i < copy.size(); ++i)
			{
				if ((copy[i] == ' ' && copy[i + 1] == ' ') || (copy[i] == ',' && copy[i + 1] == ' '))
				{
					occur = i;
					del = true;
					break;
				}
			}
			if (del == true)
				copy.erase(occur + 1, 1);
			del = false;
			for (unsigned i = 0; i < copy.size(); ++i)
			{
				if (copy[i] == ' ' && copy[i + 1] == ',')
				{
					occur = i;
					del = true;
					break;
				}
			}
			if (del == true)
				copy.erase(occur, 1);
			res = true;
			for (unsigned i = 0; i < copy.size(); ++i)
			{
				if ((copy[i] == ' ' && copy[i + 1] == ' ') || (copy[i] == ',' && copy[i + 1] == ' '))
				{
					res = false;
				}
			}
		} while (res == false);
		size_t comma = copy.find(",");
		this->title_v = copy.substr(0, comma);
		for (int i = 0; i < 6; ++i)
		{
			if(title_v[i] == ' ')
			{
				std::cout << title_v << std::endl;
				this->title_v.erase(0, 1);
				if (title_v[i] != ' ')
					break;
			}
		}
		merasing(copy);
		comma = copy.find(",");
		this->year = std::stoi(copy.substr(0, comma));
		merasing(copy);
		comma = copy.find(".");
		this->desc = copy.substr(0, comma + 1);

		std::string first;
		std::string space;
		std::string dele;
		bool result;
		do
		{
			result = true;
			for (unsigned i = 0; i < desc.size(); ++i)
			{
				if (desc[i] == ',' && desc[i + 1] != ' ')
				{
					int del = desc.find(',');
					first = desc.substr(0, del + 1);
					dele = desc.substr(0, del);
					desc.erase(0, dele.size() + 1);
					first = first + " ";
					space += first;
					result = false;
				}
			}
		} while (result == false);
		space = space + desc;
		desc = space;
	}

	const std::string& sdds::Movie::title() const
	{
		return this->title_v;
	}

	std::ostream& operator<<(std::ostream& os, const Movie& obj)
	{
		os << std::setw(40) << obj.title_v << " | "<< std::setw(4) << obj.year << " | " << obj.desc << std::endl;
		return os;
	}
}
