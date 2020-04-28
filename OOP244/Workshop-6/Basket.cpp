#include "Basket.h"
#include <string.h>
#include <string>
#include <iomanip>
#define _CRT_SECURE_NO_WARNINGS

namespace sdds
{

	Basket::Basket()
	{
		m_qty = 0;
		m_price = 0;
		m_fruitName = nullptr;
	}

	Basket::Basket(const char* fname, int famount, double fprice)
	{
		if (famount > 0 && fprice > 0 && fname != nullptr)
		{
			setQty(famount);
			setPrice(fprice);
			setName(fname);
		}
		else
		{
			m_qty = 0;
			m_price = 0;
			m_fruitName = nullptr;
		}
	}

	Basket::Basket(const Basket& bask2)
	{
		m_qty = bask2.m_qty;
		m_price = bask2.m_price;
		m_fruitName = new char[strlen(bask2.m_fruitName) + 1];
		strcpy(m_fruitName, bask2.m_fruitName);
	}

	Basket::~Basket()
	{
		delete[] m_fruitName;

	}

	void Basket::setName(const char* ftype)
	{
		m_fruitName = new char[strlen(ftype) + 1];
		strcpy(m_fruitName, ftype);
	}

	void Basket::setQty(int fquant)
	{
		m_qty = fquant;
	}

	void Basket::setPrice(double fpric)
	{
		m_price = fpric;
	}

	bool Basket::isempty() const
	{
		bool result;
		if (m_fruitName != nullptr && m_qty > 0 && m_price>0)
		{
			result = false;
		}
		else
		{
			result = true;
		}
		return result;
	}

	bool Basket::addPrice(double addamount)
	{
		if (addamount > 0)
		{
			m_price += addamount;
		}
		return this;
	}

	Basket& Basket::operator=(const Basket& bask_obj)
	{
		if (this != &bask_obj)
		{
			m_qty = bask_obj.m_qty;
			m_price = bask_obj.m_price;
			delete[] m_fruitName;
			m_fruitName = new char[strlen(bask_obj.m_fruitName) + 1];
			strcpy(m_fruitName, bask_obj.m_fruitName);
		}
		return *this;
	}

	bool Basket::operator==(const Basket& anoth_obj)
	{
		if (this->m_qty == anoth_obj.m_qty && this->m_price == anoth_obj.m_price && strcmp(this->m_fruitName, anoth_obj.m_fruitName) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Basket::operator!=(const Basket& anoth_obj)
	{
		if (this->m_qty == anoth_obj.m_qty && this->m_price == anoth_obj.m_price && strcmp(this->m_fruitName, anoth_obj.m_fruitName) == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	ostream& Basket::display(ostream& out) const
	{
		if (isempty() == true)
		{
			cout << "The Basket has not yet been filled" << endl;
		}
		else
		{
			out << "Basket Details" << endl;
			out << "Name: " << m_fruitName << endl;
			out << "Quantity: " << m_qty << endl;
			out << "Price: " << setw(6) << fixed << setprecision(2) << m_price << endl;
		}
		return out;
	}


	ostream& operator<<(ostream& output, const Basket& bas_obj)
	{
		bas_obj.display(output);
		return output;
	}
}