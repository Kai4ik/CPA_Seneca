#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H
#include "Station.h"
#include <string>

struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;
	Item(){};
	Item(const std::string& src) : m_itemName(src){};
};

class CustomerOrder
{
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	Item** m_lstItem;
	static size_t m_widthField;
public:
	CustomerOrder();
	CustomerOrder(std::string& record);
	CustomerOrder(CustomerOrder& obj);
	CustomerOrder(CustomerOrder&& obj) noexcept;
	~CustomerOrder();
	CustomerOrder& operator=(CustomerOrder&& copy_obj) noexcept;
	CustomerOrder& operator=(const CustomerOrder& obj) = delete;
	bool isItemFilled(const std::string& itemName);
	bool isOrderFilled() const;
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& out) const;
};
#endif // !CUSTOMERORDER_H


