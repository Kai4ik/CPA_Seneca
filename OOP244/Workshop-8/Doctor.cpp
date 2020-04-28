#pragma warning(disable : 4996)
#include "Doctor.h"
#include <iostream>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

namespace sdds
{
	Doctor::Doctor()
	{
		m_type[0]= '\0';
		m_salary = 0;
		m_whours = 0;
		m_specialist = false;
	}

	Doctor::Doctor(const char* type, double salary, int hours, bool specialist)
	{
		if (salary <= 0 && hours <= 0)
		{
			m_type[0] = '\0';
			m_salary = 0;
			m_whours = 0;
			m_specialist = false;
		}
		else
		{
			strcpy(m_type, type);
			m_whours = hours;
			m_specialist = specialist;
			setSalary(salary);
		}
	}

	void Doctor::setSalary(double income)
	{
		if (this->m_specialist == true)
		{
			m_salary = income + 2000;
		}
		else
		{
			m_salary = income;
		}
	}
	bool Doctor::workHours()
	{
		if (this->m_whours > MIN_X_HOURS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Doctor::bonus()
	{
		double bonus;
		if (this->m_whours > MIN_X_HOURS)
		{
			bonus = this->m_salary / 100 * 10;
		}
		else
		{
			bonus = this->m_salary / 100 * 5;
		}
		m_salary += bonus;
	}

	ostream& Doctor::display(ostream& os) const
	{
		if (this->m_salary > 0 && this->m_whours > 0)
		{
			os << "Doctor details" << endl;
			os << "Doctor Type: " << m_type << endl;
			os << "Salary: ";
			os.setf(ios::fixed);  
			os.precision(2); 
			os << m_salary << endl;
			os << "Working Hours: " << m_whours << endl;
		}
		else
		{
			os << "Doctor is not initiated yet" << endl;
		}
		return os;
	}

	Doctor::~Doctor()	{}
}
