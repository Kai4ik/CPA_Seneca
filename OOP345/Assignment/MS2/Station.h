// Name: Kairat Orozobekov
// Seneca Student ID: 104 998 190
// Seneca email: korozobekov@myseneca.ca
// Date of completion: 07.16.20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef  SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

class Station
{
	int id;
	int cur_item_numb;
	int serial_numb;
	std::string desc;
	std::string item_name;
	static size_t m_widthField;
	static int id_generator;
public:
	Station(const std::string& station_obj);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& out, bool full) const;
};

#endif // ! SDDS_STATION_H

