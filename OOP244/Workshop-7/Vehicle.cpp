#include "Vehicle.h"
using namespace std;

namespace sdds
{
	Vehicle::Vehicle()
	{
		m_speed = 0;
		m_noOfSeats = 0;
	}

	Vehicle::Vehicle(int pace, int seats)
	{
		if (pace > MIN_SPEED && seats > 0)
		{
			m_speed = pace;
			m_noOfSeats = seats;
		}
		else
		{
			m_speed = 0;
			m_noOfSeats = 0;
		}
	}

	bool Vehicle::finetune()
	{
		if (this->m_speed > MAX_SPEED)
		{
			m_speed = MIN_SPEED;
			return true;
		}
		else
		{
			cout << "The car cannot be tuned" << endl;
			return false;
		}
	}

	ostream& Vehicle::display(ostream& out) const
	{
		if (this->m_speed >= MIN_SPEED && this->m_noOfSeats > 0)
		{
			out << "|" << m_speed << "|" << m_noOfSeats << endl;
			if (m_speed > MAX_SPEED)
			{
				out << "Car has to be finetuned for speed limit" << endl;
			}
		}
		else
		{
			out << "This Car is not initiated" << endl;
		}
		return out;
	}

	istream& Vehicle::input(istream& in)
	{
		int temp_speed = 0;
		int temp_seats = 0;
		cout << "Enter the Vehicle`s speed: ";
		in >> temp_speed;
		cout << "Enter no of seats: ";
		in >> temp_seats;
		Vehicle temp(temp_speed, temp_seats);
		*this = temp;
		return in;
	}

	ostream& operator<<(ostream& out, const Vehicle& vehic_obj)
	{
		vehic_obj.display(out);
		return out;
	}

	istream& operator>>(istream& input, Vehicle& veh_obj)
	{
		veh_obj.input(input);
		return input;
	}
}