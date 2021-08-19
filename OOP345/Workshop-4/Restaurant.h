#ifndef SDDS_RESTAURANT_H
#define SDDS_RESTAURANT_H
#include "Reservation.h"

namespace sdds{
	class Restaurant
	{
		size_t am=0;
		Reservation* res;
	public:
		Restaurant(Reservation* res[], size_t cnt);
		Restaurant(const Restaurant& obj);
		Restaurant(Restaurant&& obj);
		~Restaurant();
		size_t size() const;
		friend std::ostream& operator<<(std::ostream& os, const Restaurant& obj);
	};
}
#endif // !SDDS_RESTAURANT_H
