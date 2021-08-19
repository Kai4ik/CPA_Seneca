#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <string>

namespace sdds
{
	class Book
	{
		std::string author_v;
		std::string title_v;
		std::string country_v;
		size_t year_v;
		double price_v;
		std::string desc_v;
	public:
		Book();
		Book(const std::string& strBook);
		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();
		friend std::ostream& operator<<(std::ostream& os, const Book& obj);
		template<typename T>
		void fixSpelling(T spellchecker)
		{
			spellchecker(desc_v);
		}
	};
}
#endif // !SDDS_BOOK_H

