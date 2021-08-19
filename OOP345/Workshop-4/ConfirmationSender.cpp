#include "ConfirmationSender.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

namespace sdds
{
	ConfirmationSender::ConfirmationSender()
	{
		cres = nullptr;
	}

	ConfirmationSender::~ConfirmationSender()
	{
		if (this->cres != nullptr)
		{
			std::cout << "Fuck" << std::endl;
			delete[] cres;
		}
	}

	ConfirmationSender::ConfirmationSender(const ConfirmationSender& obj)
	{
		this->res_am = obj.res_am;
		int len = obj.res_am;
		this->cres = new const Reservation * [len];
		for (int i = 0; i < obj.res_am; ++i)
			this->cres[i] = obj.cres[i];
	}

	ConfirmationSender::ConfirmationSender(ConfirmationSender&& obj)
	{
		this->res_am = obj.res_am;
		this->cres = obj.cres;
		obj.cres = nullptr;
		obj.res_am = 0;
	}

	ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res)
	{
		// TODO: insert return statement here
		// Check if res is already in the array
		bool isIn = false;
		for (int i = 0; i < this->res_am; ++i)
			isIn = this->cres[i] == &res;	// true if already in

		if (!isIn)
		{		// if not in
			const Reservation** temp = this->cres;

			++this->res_am;		// Resize array
			this->cres = new const Reservation * [this->res_am];
			for (int i = 0; i < this->res_am - 1; ++i)
				this->cres[i] = temp[i];
			this->cres[this->res_am - 1] = &res;	// Save res address to the array

			delete[] temp;
		}

		return *this;
	}

	ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res)
	{
		// Remove the res
		bool isIn = false;
		for (int i = 0; i < this->res_am; ++i)
		{
			if (this->cres[i] == &res)
			{
				isIn = true;
				for (size_t j = i; j < this->res_am - 1; ++j)
					this->cres[j] = this->cres[j + 1];
			}
		}

		// Resize the array
		if (isIn)
		{
			const Reservation** temp = this->cres;

			--this->res_am;		// Resize array
			this->cres = new const Reservation * [this->res_am];
			for (int i = 0; i < this->res_am; ++i)
				this->cres[i] = temp[i];

			delete[] temp;
		}


		return *this;
	}


	std::ostream& operator<<(std::ostream& os, const ConfirmationSender& obj)
	{
		if (obj.cres == nullptr)
		{
			os << "--------------------------" << std::endl << "Confirmations to Send!" << std::endl << "--------------------------" << std::endl << "The object is empty!" << std::endl << "--------------------------" <<std::endl;
		}
		else
		{
			os << "--------------------------" << std::endl << "Confirmations to Send!" << std::endl << "--------------------------" << std::endl;
			for (auto i = 0; i < obj.res_am; ++i)
			{
				os << *obj.cres[i];
			}
		}
		return os;
	}

}