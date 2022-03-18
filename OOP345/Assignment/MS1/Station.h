#ifndef STATION_H
#define STATION_H
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
	Station(){};
	Station(const std::string& station_obj);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& out, bool full) const;
};

#endif // !STATION_H