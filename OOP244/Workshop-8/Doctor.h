#pragma once
#ifndef SDDS_DOCTOR_H
#define SDDS_DOCTOR_H
#include <iostream>
#include "Employee.h"
using namespace std;
const int MIN_X_HOURS = 6;
const int MAX_CHAR = 20;

namespace sdds
{
	class Doctor : public Employee
	{
		char m_type [MAX_CHAR];
		double m_salary;
		int m_whours;
		bool m_specialist;
	public:
		Doctor();
		Doctor(const char* type, double salary, int hours, bool specialist = false);
		void setSalary(double income);
		bool workHours();
		void bonus();
		ostream& display(ostream& os) const;
		~Doctor();
	};
}

#endif
