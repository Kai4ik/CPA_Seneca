#pragma once
#ifndef SDDS_CAR_H 
#define SDDS_CAR_H

#include <iostream>
#include "Vehicle.h"
using namespace std;

namespace sdds
{
	const int MAX_CHAR = 20;
	const int MIN_YEAR = 2000;

	class Car : private Vehicle
	{
		char m_carType[MAX_CHAR+1];
		int m_regYear;
	public:
		Car();
		Car(const char* type, int reg_year, int pace, int numb_seats);
		void finetune();
		ostream& display(ostream& out)  const;
		istream& input(istream& in);
	};
	ostream& operator<<(ostream& out, const Car& car_obj);
	istream& operator>>(istream& input, Car& car_obj);
}
#endif