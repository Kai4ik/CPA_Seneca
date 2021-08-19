#ifndef PAIR_SDDS_H
#define PAIR_SDDS_H
#include <iostream>

namespace sdds
{
	template <typename K, typename V>
	class Pair
	{
		K key;
		V value;
	public:
		Pair() : key(), value() {};
		Pair(const K& keyc, const V& valuec) : key(keyc), value(valuec) {};
		const K& getkey() const {return this->key;};
		const V& getvalue() const {return this->value;};
		virtual void display(std::ostream& os) const
		{
			std::cout << this->getkey() << " : " << this->getvalue() << std::endl;
		};
	};
	template <typename K, typename V>
	std::ostream& operator<<(std::ostream& os, const Pair<K, V>& pair)
	{
		pair.display(os);
		return os;
	};
}
#endif // !PAIR_SDDS_H
