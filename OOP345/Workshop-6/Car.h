#ifndef SDDS_CAR_H
#define SDDS_CAR_H
#include "Vehicle.h"
#include <string>

namespace sdds
{
	class Car : public Vehicle
	{
		float speed;
		std::string maker;
		std::string cond;
	public:
		Car(){};
		Car(std::istream& out, std::string record);
		std::string condition() const;
		double topSpeed() const;
		void display(std::ostream&) const;
	};
}

#endif // !SDDS_CAR_H
