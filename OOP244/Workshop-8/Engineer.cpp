#include "Engineer.h"
#include <iostream>
using namespace std;

namespace sdds
{
	Engineer::Engineer()
	{
		m_esalary = 0;
		m_ehours = 0;
		m_level = 0;
	}

	Engineer::Engineer(double eincome, int hours, int level)
	{
		if (eincome > 0 && hours > 0 && level > 0)
		{
			m_level = level;
			m_ehours = hours;
			setSalary(eincome);
		}
		else
		{
			m_esalary = 0;
			m_ehours = 0;
			m_level = 0;
		}
	}

	void Engineer::setSalary(double esalary)
	{
		if (this->m_level == MAX_LEVEL)
		{
			m_esalary = esalary + 3000;
		}
		else
		{
			m_esalary = esalary;
		}
	}

	bool Engineer::workHours()
	{

		if (this-> m_ehours > MIN_HOURS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Engineer::bonus()
	{
		double bonus;
		if (this->m_ehours > MIN_HOURS&& this->m_level == MAX_LEVEL)
		{
			bonus = this->m_esalary / 100 * 10;
		}
		else
		{
			bonus = this->m_esalary / 100 * 5;
		}
		m_esalary += bonus;
	}

	ostream& Engineer::display(ostream& os) const
	{
		if (this->m_esalary > 0 && this->m_ehours > 0)
		{
			os << "Engineer details" << endl;
			os << "level: " << m_level << endl;
			os << "Salary: ";
			os.setf(ios::fixed);
			os.precision(2); 
			os << m_esalary << endl;
			os << "Working Hours: " << m_ehours << endl;
		}
		else
		{
			os << "Engineer is not initiated yet" << endl;
		}
		return os;
	}

	Engineer::~Engineer()	{}
}


