// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <algorithm>
#include <memory>
#include "List.h"
#include "Element.h"
#include "Utilities.h"

using namespace std;

namespace sdds
{
	List<Product> mergeRaw(const List<Description>& desc, const List<Price>& price)
	{
		List<Product> priceList;
		for (size_t k = 0; k < desc.size(); ++k)
		{
			for (size_t l = 0; l < price.size(); ++l)
			{
				if (desc[k].code == price[l].code)
				{
					Product* prod = new Product(desc[k].desc, price[l].price);
					prod->validate();
					priceList += prod;
					delete prod;
					prod = nullptr;
				}
			}
		}

		return priceList;
	}

	List<Product> mergeSmart(const List<Description>& desc, const List<Price>& price)
	{
		List<Product> priceList;
		for (size_t k = 0; k < desc.size(); ++k)
		{
			for (size_t l = 0; l < price.size(); ++l)
			{
				if (desc[k].code == price[l].code)
				{
					std::unique_ptr<Product>prod{ new Product(desc[k].desc, price[l].price) };
					prod->validate();
					priceList += prod;
				}
			}
		}

		return priceList;
	}
}