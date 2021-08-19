// Name: Kairat Orozobekov
// Seneca Student ID: 104 998 190
// Seneca email: korozobekov@myseneca.ca
// Date of completion: 07.16.20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef  SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <string>

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

#endif // ! SDDS_UTILITIES_H
