#include "Car.h"
#include <string.h>
using namespace std;

namespace sdds { 

	Car::Car() 
	{
		m_regYear = 0;
		m_carType[0] = '\0';
	}
	Car::Car(const char* type, int reg_year, int pace, int numb_seats) : Vehicle(pace, numb_seats)
	{
		m_regYear = reg_year;
		strcpy(m_carType, type);
	}

	void Car::finetune()
	{
		if (m_regYear < MIN_YEAR)
		{
			cout << "Car cannot be tuned and has to be scraped" << endl;
		}
		else
		{
			if (Vehicle::finetune() == true)
			{
				cout << "This car is finely tuned to default speed" << endl;
			}
		}
	}

	ostream& Car::display(ostream& out) const
	{
		if (m_carType[0] == '\0' || m_regYear < 2000)
		{
			out << "Car is not initiated yet" << endl;
		}
		else { 
			out.width(20);
			out.setf(ios::left);
			out << m_carType;
			out << m_regYear;
			Vehicle::display(out);
		}
		return out;
	}

	istream& Car::input(istream& in)
	{
		char temp_arr[MAX_CHAR+1];
		cout << "Enter the car type: ";
		in.getline(temp_arr, MAX_CHAR+1);
		int reg_year = 0;
		cout << "Enter the car registration year: ";
		in >> reg_year;
		m_regYear = reg_year;
		strcpy(m_carType, temp_arr);
		Vehicle::input(in);
		return in;
	}

	ostream& operator<<(ostream& out, const Car& car_obj)
	{
		car_obj.display(out);
		return out;
	}

	istream& operator>>(istream& input, Car& car_obj)
	{
		car_obj.input(input);
		return input;
	}

}