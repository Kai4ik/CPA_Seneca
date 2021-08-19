#include "SpellChecker.h"
#include <iostream>
#include <fstream>

namespace sdds
{
	SpellChecker::SpellChecker(const char* file)
	{
		std::ifstream in(file);
		if (in.is_open() == false)
			throw "Bad file name!";
		else
		{
			if (in.is_open())
			{
				for (size_t i = 0; i < 5; i++)
				{
					in >> m_badWords[i];
					in >> m_goodWords[i];
				}
			}
		}
	}
	void SpellChecker::operator()(std::string& text) const
	{
		size_t find;
		for (int i = 0; i < 5; ++i)
		{
			 while((find = text.find(m_badWords[i])) != std::string::npos)
			 {
				text.replace(find, m_badWords[i].length(), m_goodWords[i]);
			 }
		}
	}
}