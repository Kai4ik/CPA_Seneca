#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>
#include <algorithm>
#include <iostream>

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder(std::string& record)
{
	bool more = false;
	Utilities obj;
	size_t fp = -1;
	this->m_name = obj.extractToken(record, fp, more);
	this->m_product = obj.extractToken(record, fp, more);
	this->m_cntItem = std::count(record.begin()+fp, record.end(), obj.getDelimiter());
	m_lstItem = new Item* [m_cntItem];
	for (unsigned i=0; i<this->m_cntItem; ++i) {
		this->m_lstItem[i] = new Item(obj.extractToken(record, fp, more));
	}
	if (this->m_widthField < obj.getFieldWidth())
		this->m_widthField = obj.getFieldWidth();
}

CustomerOrder::CustomerOrder()
{
	this->m_lstItem = nullptr;
	this->m_cntItem = 0;
}


CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept
{
	this->m_lstItem = nullptr;
	*this = std::move(obj);
}

CustomerOrder::~CustomerOrder()
{
	if (this->m_lstItem != nullptr)
	{
		for (unsigned i = 0; i < this->m_cntItem; ++i)
		{
			delete this->m_lstItem[i];
			this->m_lstItem[i] = nullptr;
		}
		delete[] this->m_lstItem;
		this->m_lstItem = nullptr;
	}
}


CustomerOrder& CustomerOrder::operator=(CustomerOrder&& copy_obj) noexcept
{
	if (this != &copy_obj)
	{
		if (this->m_lstItem != nullptr)
		{
			for (unsigned i = 0; i < this->m_cntItem; ++i)
				delete this->m_lstItem[i];
			delete[] this->m_lstItem;
		}
		this->m_name = copy_obj.m_name;
		this->m_product = copy_obj.m_product;
		this->m_widthField = copy_obj.m_widthField;
		this->m_cntItem = copy_obj.m_cntItem;
		this->m_lstItem = copy_obj.m_lstItem;
		copy_obj.m_lstItem = nullptr;
		copy_obj.m_cntItem = 0;
		copy_obj.m_name = "";
		copy_obj.m_product = "";
	}
	return *this;
}

CustomerOrder::CustomerOrder(CustomerOrder& obj)
{
	throw "Copying is prohibitted !";
}

bool CustomerOrder::isItemFilled(const std::string& itemName)
{
	for (unsigned i = 0; i < this->m_cntItem; ++i)
	{
		if (this->m_lstItem[i]->m_itemName == itemName)
			return this->m_lstItem[i]->m_isFilled;
	}
	return true;
}

bool CustomerOrder::isOrderFilled() const
{
	unsigned filled_items = 0;
	for (unsigned i = 0; i < this->m_cntItem; ++i)
	{
		if (this->m_lstItem[i]->m_isFilled == true)
			filled_items++;
	}
	return (filled_items == this->m_cntItem ? true : false);
}

void CustomerOrder::fillItem(Station& station, std::ostream& os)
{
	for (unsigned i = 0; i < this->m_cntItem; ++i)
	{
		if (this->m_lstItem[i]->m_itemName == station.getItemName())
		{
			if (station.getQuantity() >= 1)
			{
				station.updateQuantity();
				this->m_lstItem[i]->m_isFilled = true;
				this->m_lstItem[i]->m_serialNumber = 1;
				os << "    Filled " << this->m_name << ", " << this->m_product << " [" << station.getItemName() << "]" << std::endl;
			}
			else
			{
				os << "    Unable to fill " << this->m_name << ", " << this->m_product << " [" << station.getItemName() << "]" << std::endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& out) const
{
	out << this->m_name << " - " << this->m_product << std::endl;
	for (unsigned i = 0; i < this->m_cntItem; ++i)
	{
		out << "[" << std::setw(6) << std::setfill('0') << this->m_lstItem[i]->m_serialNumber << "] " << std::left << std::setfill(' ') << std::setw(this->m_widthField) << this->m_lstItem[i]->m_itemName << " - " << std::right << (this->m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << std::endl;
	}
}
