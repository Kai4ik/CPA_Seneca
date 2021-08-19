#include "Book.h"
#include <iostream>
#include <iomanip>

namespace sdds
{
	void erasing(std::string& copy)
	{
		std::string delet;
		size_t comma = copy.find(",");
		delet = copy.substr(0, comma);
		copy.erase(0, delet.size() + 1);
	}

	Book::Book()
	{
	}

	Book::Book(const std::string& strBook)
	{
		std::string copy = strBook;
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
		this->author_v = copy.substr(0, comma);
		erasing(copy);
		comma = copy.find(",");
		this->title_v = copy.substr(0, comma);
		erasing(copy);
		comma = copy.find(",");
		this->country_v = copy.substr(0, comma);
		erasing(copy);
		comma = copy.find(",");
		this->price_v = std::stod(copy.substr(0, comma));
		erasing(copy);
		comma = copy.find(",");
		this->year_v = std::stoi(copy.substr(0, comma));
		erasing(copy);
		comma = copy.find(".");
		this->desc_v = copy.substr(0, comma + 1);

		std::string first;
		std::string space;
		std::string dele;
		bool result;
		do
		{
			result = true;
			for (unsigned i = 0; i < desc_v.size(); ++i)
			{
				if (desc_v[i] == ',' && desc_v[i + 1] != ' ')
				{
					int del = desc_v.find(',');
					first = desc_v.substr(0, del + 1);
					dele = desc_v.substr(0, del);
					desc_v.erase(0, dele.size() + 1);
					first = first + " ";
					space += first;
					result = false;
				}
			}
		} while (result == false);
		space = space + desc_v;
		desc_v = space;
	}

	const std::string& Book::title() const
	{
		return this->title_v;
	}

	const size_t& Book::year() const
	{
		return this->year_v;
	}

	const std::string& Book::country() const
	{
		return this->country_v;
	}

	double& Book::price()
	{
		return price_v;
	}



	std::ostream& operator<<(std::ostream& os, const Book& obj)
	{
		os << std::setw(20) << obj.author_v << " | " << std::setw(22) << obj.title() << " | " << std::setw(5) << obj.country() << " | " << std::setw(4) << obj.year() << " | " << std::setw(6) << std::fixed << std::setprecision(2) << obj.price_v << " | " << obj.desc_v << std::endl;
		return os;
	}
}