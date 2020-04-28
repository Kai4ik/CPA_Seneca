#pragma once
using namespace std;
#include <iostream>
#include <string.h>
#include <string>

namespace sdds
{
	const int MAX = 15;
	//template which represents type of NUmbers held in the NumbersBox
	template<typename type>
	class NumbersBox
	{
		char name[MAX+1];
		int size;
		type* items;
	public:
		NumbersBox();
		NumbersBox(int n_size, const char* n_name);
		~NumbersBox();
		type& operator[](int i);
		NumbersBox<type>& operator*=(const NumbersBox<type>& other_obj);
		NumbersBox<type>& operator+=(type num);
		ostream& display(ostream& os) const;
	};
	template<typename type>
	ostream& operator<<(ostream& out, NumbersBox<type>& box);

	//no-argument constructor which sets NumbersBox object to a safe empty state
	template<typename type>
	inline NumbersBox<type>::NumbersBox()
	{
		name[0] = '\0';
		size = 0;
		items = nullptr;
	}

	template<typename type>
	inline NumbersBox<type>::NumbersBox(int n_size, const char* n_name)
	{
		if (n_name != nullptr && n_size > 0)
		{
			size = n_size;
			strcpy(name, n_name);
			items = new type[n_size];
		}
		else
		{
			name[0] = '\0';
			size = 0;
			items = nullptr;
		}
	}

	template<typename type>
	inline NumbersBox<type>::~NumbersBox()
	{
		delete[] items;
	}

	//operator overload which allows access to the Box's items via the passed index
	template<typename type>
	inline type& NumbersBox<type>::operator[](int i)
	{
		return items[i];
	}

	template<typename type>
	inline NumbersBox<type>& NumbersBox<type>::operator*=(const NumbersBox<type>& other_obj)
	{
		if (this->size == other_obj.size)
		{
			for (int i = 0; i < this->size; i++)
			{
				items[i] = items[i] * other_obj.items[i];
			}
		}
		return *this;
	}

	template<typename type>
	inline NumbersBox<type>& NumbersBox<type>::operator+=(type num)
	{
		type* temp_arr = new type[size+1];
		for (int i = 0; i < size; i++)
		{
			temp_arr[i] = items[i];
		}
		temp_arr[size] = num;
		delete [] items;
		items = temp_arr;
		size++;
		return *this;
	}

	template<typename type>
	inline ostream& NumbersBox<type>::display(ostream& os) const
	{
		if (name == nullptr || size == 0)
		{
			os << "Empty Box" << endl;
			return os;
		}
		else
		{
			os << "Box name: " << this->name << endl;
			for (int i = 0; i < size; i++)
			{
				os << items[i];
				if (i != size - 1)
				{
					os << ", ";
				}
			}
			os << endl;
			return os;
		}
	}

	template<typename type>
	ostream& operator<<(ostream& out, NumbersBox<type>& box)
	{
		box.display(out);
		return out;
	}

}