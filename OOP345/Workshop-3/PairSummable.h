#ifndef PAIRSUMMABLE_SDDS_H
#define PAIRSUMMABLE_SDDS_H
#include <iostream>
#include <iomanip>
#include <string>
#include "Pair.h"

namespace sdds
{
	template <typename K, typename V>
	class PairSummable : public Pair<K, V>
	{
		static V init_val;
		static size_t min_width;
	public:
		static const V& getInitialValue()
		{
			return init_val;
		};
		PairSummable(){};
		PairSummable(const K& key, const V& value) : Pair<K,V>(key, value)
		{
			if (min_width < key.size())
				min_width = key.size();
		};
		V sum(const K& key, const V& value) const
		{
			V obj;
			if (this->getkey() == key)
			{
				obj = this->getvalue()+ value;
			}
			else
			{
				obj = value;
			}
			return obj;
		};
		void display(std::ostream& os) const
		{
			std::cout << std::left << std::setw(min_width);
			//using Pair<K, V>display;
			Pair<K, V>::display(os);
			std::cout << std::right;
		}
	};

	template <typename K, typename V>
	size_t PairSummable<K, V>::min_width = 0;

	template<>
	std::string PairSummable <std::string, std::string>::init_val= std::string("");
	

	template<>
	int PairSummable<std::string, int>::init_val = 0;


	template<>
	std::string PairSummable<std::string, std::string>::sum(const std::string& key, const std::string& value) const
	{
		std::string conc;
		if (key == this->getkey())
		{
			conc = value + "," + Pair<std::string, std::string>::getvalue();
		}
		else
		{
			conc = value;
		}
		return conc;
	}
	
}
#endif // !PAIRSUMMABLE_SDDS_H