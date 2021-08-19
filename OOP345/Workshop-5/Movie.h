#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
#include <string>

namespace sdds
{
	class Movie
	{
		std::string title_v;
		int year;
		std::string desc;
	public:
		Movie(){};
		Movie(const std::string& strMovie);
		const std::string& title() const;
		friend std::ostream& operator<<(std::ostream& os, const Movie& obj);
		template<typename T>
		void fixSpelling(T spellchecker)
		{
			spellchecker(title());
			spellchecker(desc);
		}
		
	};
}
#endif // !SDDS_MOVIE_H
