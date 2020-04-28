#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

namespace sdds
{
	class Basket
	{
		char* m_fruitName;
		int m_qty;
		double m_price;
	public:
		Basket();
		Basket(const char* fname, int famount, double fprice);
		Basket(const Basket& bask2);
		~Basket();
		void setName(const char* ftype);
		void setQty(int fquant);
		void setPrice(double fpric);
		bool isempty() const;
		bool addPrice(double addamount);
		Basket& operator=(const Basket& bask_obj);
		bool operator==(const Basket& anobj);
		bool operator!=(const Basket& anobj);
		ostream& display(ostream& out) const;
	};
	ostream& operator<<(ostream& output, const Basket& bas_obj);
}