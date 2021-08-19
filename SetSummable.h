#ifndef SDDS_SETSUMMABLE_H
#define SDDS_SETSUMMABLE_H
#include <iostream>
#include "Set.h"

namespace sdds
{
	template <typename T, signed int N, typename K, typename V>
	class SetSummable : public Set<T, N>
	{
	public:
		V accumulate(const K& key) const
		{
			auto sum = T::getInitialValue();
			for (auto i = 0; i < this.size(); ++i)
			{
				sum = (*this)[i].sum(key, sum);
			}
			return sum;
		}
	};
}
#endif // !SDDS_SETSUMMABLE_H

