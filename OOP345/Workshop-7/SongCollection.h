#ifndef SDDS_SONGCOLLECTION_H
#define SDDS_SONGCOLLECTION_H
#include <string>
#include <vector>
#include <list>

namespace sdds
{
	struct Song
	{
		std::string arstist;
		std::string title;
		std::string album;
		double m_price;
		std::string year;
		int length;
		friend std::ostream& operator<<(std::ostream& out, const Song& obj);
	};

	class SongCollection
	{
		std::vector<Song>songs;
	public:
		SongCollection(std::string file);
		void display(std::ostream& out);
		bool inCollection(std::string name) const;
		void cleanAlbum();
		void sort(std::string category);
		std::list<Song> getSongsForArtist(std::string fname) const;
	};
}

#endif // !SDDS_SONGCOLLECTION_H
