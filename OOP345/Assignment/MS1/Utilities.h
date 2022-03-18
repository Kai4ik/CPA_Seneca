#ifndef  UTILITIES_H
#define UTILITIES_H
#include <string>

//class that helps to parse input files and provides basic functionality for all objects in the assembly line

class Utilities
{
	size_t um_widthField = 1;
	static char m_delimiter;
public:
	void setFieldWidth(size_t newWidth);
	size_t getFieldWidth() const;
	static void setDelimiter(char newDelimiter);
	static char getDelimiter();
	std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
};

#endif // ! UTILITIES_H
