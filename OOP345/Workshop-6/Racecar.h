#ifndef SDDS_RACECAR_H
#define SDDS_RACECAR_H
#include "Car.h"

namespace sdds
{
	class Racecar : public Car
	{
		double m_booster;
	public:
		void display(std::ostream& out) const;
		double topSpeed() const;
		Racecar(std::istream& in, std::string record);
		Racecar(){};
	};
}
#endif // !SDDS_RACECAR_H
