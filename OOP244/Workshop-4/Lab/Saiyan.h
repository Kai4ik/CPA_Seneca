/*Name: Kairat Orozobekov
  Student ID: 104 998 190
  Email: korozobekov@myseneca.ca
  Section: NBB
  Date: 02.07.2020*/

#pragma once
#ifndef SDDS_SAIYAN_H__
#define SDDS_SAIYAN_H__

namespace sdds
{
	const int MAX_NAME = 30;
	class Saiyan

	{	
		char m_name[MAX_NAME+1];
		int m_dob;
		int m_power;
		bool m_super;
	public:
		Saiyan();
		Saiyan(const char* string, int year, int strenght);
		bool isSuper() const;
		bool isValid() const;
		void setEmpty();
		void display() const;
		void set(const char* name, int dob, int power, bool super = false);
		bool hasLost(const Saiyan& other) const;
	};
}
#endif // !SDDS_SAIYAN_H__