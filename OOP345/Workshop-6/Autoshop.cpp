#include "Autoshop.h"
#include <iostream>
#include <typeinfo>

namespace sdds
{
	Autoshop& sdds::Autoshop::operator+=(Vehicle* thevehicle)
	{
		bool IsIn= false;
		if (this->m_vehicles.size() > 0)
		{
			for (unsigned i = 0; i < this->m_vehicles.size(); ++i)
			{
				if (this->m_vehicles[i] == thevehicle)
					IsIn = true;
			}
		}
		if (IsIn == false)
		{	
			this->m_vehicles.push_back(thevehicle);
		}
		return *this;
	}

	Autoshop::~Autoshop()
	{
		for (unsigned i = 0; i < this->m_vehicles.size(); ++i)
		{
			delete[] m_vehicles[i];
			m_vehicles[i] = nullptr;
		}
	}

	void Autoshop::display(std::ostream& out) const
	{
		out << "--------------------------------" << std::endl;
		out << "| Cars in the autoshop!        |" << std::endl;
		out << "--------------------------------" << std::endl;
		for (unsigned i = 0; i < this->m_vehicles.size(); ++i)
		{
			this->m_vehicles[i]->display(out);
		}
	}
}