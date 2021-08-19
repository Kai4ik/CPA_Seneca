#ifndef SET_SDDS_H
#define SET_SDDS_H
#include <cstddef>

namespace sdds
{
template <typename T, signed int N>
class Set
	{
	T arr[N];
	size_t added_elem = 0;
public:
	size_t size() const {return added_elem;};
	const T& operator[](size_t idx) const {return arr[idx];};
	void operator+=(const T& item)
	{
		if (added_elem < N)
		{
			arr[added_elem] = item;
			added_elem++;
		}
	};
	};

}


#endif // !SET_SDDS_H
