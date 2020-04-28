/* Name: Kairat Orozobekov
   Student ID: 104 998 190
   Email: korozobekov@myseneca.ca
   Section: NAB */

// Gift.h
// Gift.h
#pragma once
#ifndef SDDS_GIFT_H 
#define SDDS_GIFT_H

namespace sdds
{
	const int MAX_DESC = 15;
	const double MAX_PRICE = 999.99;
	const int pattern = 20;


	struct Wrapping
	{
		char* pattern;
	};


	struct Gift
	{
		char g_description[MAX_DESC + 1];
		double g_price;
		int g_units;
		Wrapping *wrap;
		int wrap_layers;
	};

	


	void gifting(char* descript);
	void gifting(double& cost);
	void gifting(int& amount);
	void gifting(Gift& wrapping);
	void display(const Gift& info);
	bool unwrap(Gift& unwrapgift);
	bool wrap(Gift& gift);
}


#endif
