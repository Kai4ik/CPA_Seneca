#include "Restaurant.h"
#include "Reservation.h"
#include <iostream>

namespace sdds
{
	Restaurant::Restaurant(Reservation* reser[], size_t cnt)
	{
		this->res = new Reservation[cnt];
		for (unsigned i = 0; i < cnt; ++i)
		{
			this->res[i] = *reser[i];
			this->am++;
		}
	}
	Restaurant::Restaurant(const Restaurant& obj)
	{
		this->am = obj.am;
		int len = obj.am;
		this->res = new Reservation[len + 1];
		for (unsigned i = 0; i < this->am; ++i)
		{
			res[i] = obj.res[i];
		}
	}
	Restaurant::Restaurant( Restaurant&& obj)
	{
		this->am = obj.am;
		this->res = obj.res;
		obj.am = 0;
		obj.res = nullptr;
	}

	Restaurant::~Restaurant()
	{
		delete[] res;
	}

	size_t Restaurant::size() const
	{
		return this->am;
	}

	std::ostream& operator<<(std::ostream& os, const Restaurant& obj)
	{
		if (obj.am == 0)
		{
			os << "--------------------------" << std::endl << "Fancy Restaurant" << std::endl << "--------------------------" << std::endl << "The object is empty!" << std::endl << "--------------------------" << std::endl;
		}
		else
		{
			os << "--------------------------" << std::endl << "Fancy Restaurant" << std::endl << "--------------------------" << std::endl;
			for (unsigned i = 0; i < obj.size(); ++i)
			{
				os << obj.res[i];
			}
			os << "--------------------------" << std::endl;
		}
		return os;
	}
}