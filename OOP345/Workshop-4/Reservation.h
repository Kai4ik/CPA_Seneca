#ifndef SDDS_RESERVATION_H
#define SDDS_RESERVATION_H
#include <string>

namespace sdds
{
	class Reservation
	{
		std::string res_id;
		std::string name;
		std::string email;
		short guests;
		unsigned short day;
		unsigned short hour;
	public:
		Reservation();
		Reservation(const std::string& reser);
		friend std::ostream& operator<<(std::ostream& os, const Reservation& obj);
	};
}
#endif // !SDDS_RESERVATION_H
