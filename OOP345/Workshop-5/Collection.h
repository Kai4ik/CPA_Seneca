#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <string>
#include <stdexcept>
#include <iostream>

namespace sdds
{
	template<class T>
	class Collection
	{
		T* collections;
		std::string name_v;
		size_t length;
		void (*point)(const Collection<T>& obj, const T&);
	public:
		Collection(std::string names)
		{
			collections = nullptr;
			point = nullptr;
			name_v = names;
			length = 0;
		}
		//Collection& (const Collection& obj) = delete;
		//Collection& operator=(const Collection& obj) = delete;

		const std::string& name() const
		{
			return this->name_v;
		}

		size_t size() const
		{
			return length;
		}

		void setObserver(void (*obs)(const Collection<T>& obj, const T& ob))
		{
			point = obs;
		}

		Collection<T>& operator+=(const T& item)
		{
			bool exist = false;
			if (collections != nullptr)
			{
				for (unsigned k = 0; k < length; ++k)
				{
					if (collections[k].title() == item.title())
						exist = true;
				}
			}
			if (exist == false)
			{
				T* copy = this->collections;
				++length;
				this->collections = new T[length];
				for (unsigned i = 0; i < length-1; ++i)
					this->collections[i] = copy[i];
				this->collections[this->length-1] = item;
				if (this->point != nullptr)
					this->point(*this, item);
				delete[] copy;
			}
			
			return *this;
		}

		T& operator[](size_t idx) const
		{
			if (idx >= length)
			{
				throw std::out_of_range ("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(length) + "] items.");
			}
			else
			{
				return this->collections[idx];
			}
		}

		T* operator[](std::string tit) const
		{
			for (unsigned k = 0; k < this->size(); ++k)
			{
				if (collections[k].title() == tit)
					return &collections[k];
			}
			return nullptr;
		}

		friend std::ostream& operator<<(std::ostream& os, const Collection& obj)
		{
			for (unsigned h = 0; h < obj.size(); ++h)
			{
				os << obj[h];
			}
			return os;
		}
		~Collection()
		{
			delete[] collections;
		}
	};
}
#endif // !SDDS_COLLECTION_H