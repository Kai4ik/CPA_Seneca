#pragma once
#ifndef SDDS_VEHICLE_H 
#define SDDS_VEHICLE_H

#include <iostream>
using namespace std;


namespace sdds
{
	const int MIN_SPEED = 100;
	const int MAX_SPEED = 140;
	class Vehicle
	{
		int m_speed;
		int m_noOfSeats;
	public:
		Vehicle();
		Vehicle(int pace, int seats);
		bool finetune();
		ostream& display(ostream& out) const;
		istream& input(istream& in);
	};
	ostream& operator<<(ostream& out,const Vehicle& vehic_obj);
	istream& operator>>(istream& input, Vehicle& veh_obj);
}
#endif