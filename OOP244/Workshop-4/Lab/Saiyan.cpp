/*Name: Kairat Orozobekov
  Student ID: 104 998 190
  Email: korozobekov@myseneca.ca
  Section: NBB
  Date: 02.07.2020*/

#define _CRT_SECURE_NO_WARNINGS
#include "Saiyan.h"
#include <iostream>
#include <string.h>
using namespace std;

namespace sdds
{
	Saiyan::Saiyan()
	{
		setEmpty();
	}


	Saiyan::Saiyan(const char* string, int year, int strenght)
	{
		if (year < 2020 && strenght > 0 && string != nullptr && string[0] != '\0')
		{
			m_super = false;
			strcpy(Saiyan::m_name, string);
			m_dob = year;
			m_power = strenght;
		}
		else
		{
			setEmpty();
		}
	}


	bool Saiyan::isSuper() const
	{
		return m_super;
	}


	bool Saiyan::isValid() const
	{
		if (m_name != nullptr && m_power > 0 && m_dob < 2020 && m_name[0] != '\0' && m_dob != 0)
		{
			return true;
		}
		else { 
			return false;
		}	
	}


	void Saiyan::setEmpty()
	{
			m_name[0] = '\0';
			m_dob = 0;
			m_power = 0;
			m_super = false;
	}



	void Saiyan::display() const
	{
		if (isValid() == false)
		{
			cout << "Invalid Saiyan!" << endl;
		} 
		else
		{
				cout << m_name << endl;
				cout << "DOB: " << m_dob << " Power: " << m_power << endl;
				if (m_super == true)
				{
					cout << "Super Saiyan Ability: Super Saiyan." << endl << endl;
				}
				else
				{
					cout << "Super Saiyan Ability: Not super Saiyan." << endl << endl;
				}
		}
	}


	void Saiyan::set(const char* name, int dob, int power, bool super)
	{
		if (isValid() == true)
		{
			m_super = true;
			strcpy(Saiyan::m_name, name);
			m_dob = dob;
			m_power = power;
		}
		else if ( m_name != name && m_dob != dob && m_dob == 0)
		{
			strcpy(Saiyan::m_name, name);
			m_dob = dob;
			m_power = power;
		}
		else
		{
			setEmpty();
		}
	}

	bool Saiyan::hasLost(const Saiyan& other) const
	{
		if (Saiyan::m_power > other.m_power && isValid() == true)
		{
			return false;
		}
		else
		{
			return true;
		}	
	}
}
