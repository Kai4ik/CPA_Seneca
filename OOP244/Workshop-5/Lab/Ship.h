#include "Engine.h"
#ifndef SDDS_SHIP_H
#define SDDS_SHIP_H
namespace sdds
{
	class Ship
	{
		Engine engine[10];
		char sh_type[7];
		int numb;
		//	float distance;
	public:
		Ship();
		Ship(const char* type1, Engine* engines, int lenght);
		void setEmpty();
		bool empty() const;
		Ship& operator+=(Engine e);
		float calculatePower() const;
		void display() const;
	};
		bool operator==(const Ship& sh1, const Ship& sh2);
		bool operator<(const Ship&, double);
	
}
#endif
