/* Student name: Kairat Orozobekov
   Student #: 104 998 190
   Student email: korozobekov@myseneca.ca
   Date submitted: 2020.06.17
   Course: OOP345, Section NEE
   I have done all the coding by myself and only copied the code that my professor provided
   to complete my workshops and assignments.
*/
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
