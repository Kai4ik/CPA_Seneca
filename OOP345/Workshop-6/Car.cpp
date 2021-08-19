#include "Car.h"
#include <typeinfo>
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

	Car::Car(std::istream& out, std::string record)
	{
		bool res;
		int occur = 0;
		do
		{
			bool del = false;
			for (unsigned i = 0; i < record.size(); ++i)
			{
				if ((record[i] == ' ' && record[i + 1] == ' ') || (record[i] == ',' && record[i + 1] == ' '))
				{
					occur = i;
					del = true;
					break;
				}
			}
			if (del == true)
				record.erase(occur + 1, 1);
			del = false;
			for (unsigned i = 0; i < record.size(); ++i)
			{
				if (record[i] == ' ' && record[i + 1] == ',')
				{
					occur = i;
					del = true;
					break;
				}
			}
			if (del == true)
				record.erase(occur, 1);
			res = true;
			for (unsigned i = 0; i < record.size(); ++i)
			{
				if ((record[i] == ' ' && record[i + 1] == ' ') || (record[i] == ',' && record[i + 1] == ' '))
				{
					res = false;
				}
			}
		} while (res == false);
		std::string tag;
		size_t comma = record.find(",");
		tag = record.substr(0, comma);
		erasing(record);
		for (int i = 0; i < tag.size(); ++i)
		{
			if (tag[i] == ' ')
			{
				tag.erase(tag[i], 1);
			}
		}
		if (tag == "c" || tag == "C")
		{
			std::cout << record << std::endl;
			comma = record.find(",");
			this->maker = record.substr(0, comma);
			erasing(record);
			comma = record.find(",");
			this->cond = record.substr(0, comma);
			erasing(record);
			comma = record.find(",");
			std::string nan = record.substr(0, comma);
			try
			{
				this->speed = std::stoi(record.substr(0, comma));
			}
			catch (const std::invalid_argument& ia)
			{
				this->speed = 0;
				std::cerr << "Invalid Record!" << std::endl;
			}


			if (this->cond.empty() == true || this->cond == "")
			{
				this->cond = "n";
			}

			try
			{
				if (cond != "n" && cond != "u" && cond != "b")
				{
					throw "Invalid Record!";
				}
			}
			catch (const char* mess)
			{
				std::cerr << "Invalid Record!" << std::endl;
			}
		}
	}

	std::string Car::condition() const
	{
		std::string condition;
		if (this->cond == "n")
		{
			condition = "new";
		}
		else if (this->cond == "u")
		{
			condition = "used";
		}
		else if (this->cond == "b")
		{
			condition = "broken";
		}
		return condition;
	}

	double Car::topSpeed() const
	{
		return speed;
	}


	void Car::display(std::ostream& out) const
	{
		out << "| " << std::setw(10) << this->maker << " | " << std::setw(6) << std::left << this->condition() << " | " << std::setw(6)<< std::fixed << std::setprecision(2) << this->topSpeed() << " | ";
	}
}
