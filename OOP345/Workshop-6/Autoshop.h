#ifndef SDDS_AUTOSHOP_H
#define SDDS_AUTOSHOP_H
#include "Vehicle.h"
#include <vector>
#include <list>
#include <functional>

namespace sdds
{
	class Autoshop
	{
		std::vector<Vehicle*> m_vehicles;
	public:
		Autoshop& operator +=(Vehicle* thevehicle);
		~Autoshop();
		void display(std::ostream& out) const;
		template <typename T>
		void select(T test, std::list<const Vehicle*>& vehicle)
		{
			for (unsigned i = 0; i < this->m_vehicles.size(); ++i)
			{
				if (test(m_vehicles[i]) == true)
				{
					vehicle.push_back(m_vehicles[i]);
				}
			}
		}
	};
}
#endif // !SDDD_AUTOSHOP_H
