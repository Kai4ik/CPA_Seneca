#ifndef SDDS_CONFIRMATIONSENDER_H
#define SDDS_CONFIRMATIONSENDER_H
#include "Reservation.h"
#include <vector>

namespace sdds
{
	class ConfirmationSender
	{
		const Reservation** cres;
		int res_am=0;
	public:
		ConfirmationSender();
		~ConfirmationSender();
		ConfirmationSender(const ConfirmationSender& obj);
		ConfirmationSender(ConfirmationSender&& obj);
		ConfirmationSender& operator+=(const Reservation& res);
		ConfirmationSender& operator-=(const Reservation& res);
		friend std::ostream& operator<<(std::ostream& os, const ConfirmationSender& obj);
	};
}
#endif // !SDDS_CONFIRMATIONSENDER_H

