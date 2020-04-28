#pragma once
#ifndef SDDS_EMPLOYEE_H 
#define SDDS_EMPLOYEE_H
#include <iostream>
using namespace std;


namespace sdds
{
	class Employee
	{
	public:
		virtual ~Employee()	{};
		virtual void setSalary(double numb) = 0;
		virtual void bonus() = 0;
		virtual bool workHours() = 0;
		virtual ostream& display(ostream& os) const = 0;
	};
}

#endif
