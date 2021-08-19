#include "RecordSet.h"
#include <fstream>
#include <iostream>
#include <cstring>

namespace sdds
{
	RecordSet::RecordSet()
	{
		n_file = nullptr;
		counter = 0;
	}

	RecordSet::RecordSet(const char* name)
	{
		this->n_file = nullptr;
		std::string str;
		std::ifstream in(name);
		if (in.is_open())
		{
			while (std::getline(in, str, ' '))
			{
				counter++;
			}
			n_file = new std::string[counter+1];
			in.close();
			in.open(name);
			for (size_t i = 0; i < this->counter; i++)
			{
				std::getline(in, n_file[i], ' ');
			}
		}
	}

	RecordSet::RecordSet(const RecordSet& copy_obj)
	{
		this->n_file = nullptr;
		*this = copy_obj;
	}

	RecordSet::RecordSet(RecordSet&& move_obj)
	{
		this->n_file = nullptr;
		*this = std::move(move_obj);
	}

	RecordSet& RecordSet::operator=(const RecordSet& copy_obj)
	{
		if (this != &copy_obj)
		{
			delete[] this->n_file;
			this->counter = copy_obj.counter;
			n_file = new std::string[counter];
			for (size_t i = 0; i < counter; i++)
			{
				this->n_file[i] = copy_obj.n_file[i];
			}
		}
		return *this;
	}

	RecordSet& RecordSet::operator=(RecordSet&& move_obj)
	{
		if (this->n_file != nullptr)
			delete[] this->n_file;
		if (this != &move_obj)
		{
			this->n_file = move_obj.n_file;
			this->counter = move_obj.counter;
			move_obj.counter = 0;
			move_obj.n_file = nullptr;
		}
		return *this;
	}

	RecordSet::~RecordSet()
	{
		delete[] n_file;
		n_file = nullptr;
	}

	size_t RecordSet::size() const
	{
		return counter;
	}

	std::string RecordSet::getRecord(size_t index) const
	{
		std::string record;
		for (unsigned int i = 0; i < this->counter; i++)
		{
			if (i == index)
			{
				record = n_file[i];
			}
		}
		return record;
	}
}