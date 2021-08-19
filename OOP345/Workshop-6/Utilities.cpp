#include "Utilities.h"
#include "Racecar.h"
#include <iostream>

namespace sdds
{
	Vehicle* createInstance(std::istream& in)
	{
		std::string tag;
		std::string record;
		std::getline(in, record, '\n');
		size_t comma = record.find(",");
		tag = record.substr(0, comma);
		Vehicle* obj;
		if (tag != "")
		{
			if (tag == "c" || tag == "C")
			{
				obj = new Car(in, record);
				return obj;
			}
			else if (tag == "r" || tag == "R")
			{
				obj = new Racecar(in, record);
				return obj;
			}
			else if (tag != "r" && tag != "R" && tag != "c" && tag != "C")
			{
				throw "Unrecognized record type: [" + tag + "]";
			}
			else
			{
				return nullptr;
			}
		}
		else {
			return nullptr;
		}
	}
}
