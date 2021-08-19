#include "Racecar.h"

namespace sdds
{

	void rerasing(std::string& copy)
	{
		std::string delet;
		size_t comma = copy.find_last_of(",");
		delet = copy.substr(0, comma);
		copy.erase(0, delet.size() + 1);
	}

	void Racecar::display(std::ostream& out) const
	{
		Car::display(out);
		out << "*";
	}

	double Racecar::topSpeed() const
	{
		double boost_pace = Car::topSpeed() + (Car::topSpeed() * this->m_booster);
		return boost_pace;
	}

	Racecar::Racecar(std::istream& in, std::string record) : Car(in, record)
	{
		rerasing(record);
		this->m_booster = std::stod(record.substr(0));
		std::cout << this->m_booster << std::endl;
	}
}