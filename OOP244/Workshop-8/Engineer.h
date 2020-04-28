#pragma once
#ifndef SDDS_ENGINEER_H
#define SDDS_ENGINEER_H
#include <iostream>
#include "Employee.h"
using namespace std;
const int MIN_HOURS = 5;
const int MAX_LEVEL = 4;

namespace sdds
{
	class Engineer : public Employee
	{
		double m_esalary;
		int m_ehours;
		int m_level;
	public:
		Engineer();
		Engineer(double eincome, int hours, int level);
		void setSalary(double esalary);
		bool workHours();
		void bonus();
		ostream& display(ostream& os) const;
		~Engineer();
	};
}
#endif