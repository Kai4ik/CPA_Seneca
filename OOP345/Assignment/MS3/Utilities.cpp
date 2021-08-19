// Name: Kairat Orozobekov
// Seneca Student ID: 104 998 190
// Seneca email: korozobekov@myseneca.ca
// Date of completion: 08.01.20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"
#include <iostream> 

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t newWidth)  { um_widthField = newWidth; }

size_t Utilities::getFieldWidth() const    {  return um_widthField; }

void Utilities::setDelimiter(char newDelimiter)  { m_delimiter = newDelimiter; }

char Utilities::getDelimiter()   {  return m_delimiter; }

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	std::string token;
	size_t len = str.find(this->getDelimiter(), next_pos + 1);
	token = str.substr(next_pos + 1, len - next_pos - 1);
	next_pos = len;
	if (token.size() > 0)
	{
		more = true;
		if (token.size() > this->getFieldWidth())
			this->setFieldWidth(token.size());
	}
	else
		more = false;
	return token;
}