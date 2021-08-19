#include "SongCollection.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>


namespace sdds
{
	void print_dash(char symb, int amount)
	{
		for (int k = 0; k < amount; ++k)
			std::cout << symb;
		std::cout << std::endl;
	}

	void without_spaces(std::string& word)
	{
		bool result = false;
		for (unsigned i = 0; i < word.size(); ++i)
		{
			if (word[i] != ' ')
			{
				result = true;
				break;
			}
		}
		if (result == true)
		{
			int f_ns = word.find_first_not_of(' ');
			int l_ns = word.find_last_not_of(' ');
			word = word.substr(f_ns, l_ns - f_ns + 1);
		}
	}

	SongCollection::SongCollection(std::string file)
	{
		Song song_obj;
		std::string stroka;
		std::ifstream in(file);
		if (in.is_open())
		{
			while (std::getline(in, stroka, '\n'))
			{
				song_obj.title = stroka.substr(0, 25);
				without_spaces(song_obj.title);
				stroka.erase(0, 25);
				song_obj.arstist = stroka.substr(0, 25);
				without_spaces(song_obj.arstist);
				stroka.erase(0, 25);
				song_obj.album = stroka.substr(0, 25);
				without_spaces(song_obj.album);
				stroka.erase(0, 25);
				song_obj.year = stroka.substr(0, 5);
				without_spaces(song_obj.year);
				stroka.erase(0, 5);
				song_obj.length = std::stoi(stroka.substr(0, 5));
				stroka.erase(0, 5);
				song_obj.m_price = std::stod(stroka.substr(0, 5));
				stroka.erase(0, 5);
				songs.push_back(song_obj);
			}
		}
	}

	std::ostream& operator<<(std::ostream& out, const Song& obj)
	{
		int min = obj.length / 60;
		int sec = obj.length - (min * 60);
		out << "| " << std::setw(20) << std::left << obj.title << " | " << std::setw(15) << obj.arstist << " | " << std::setw(20) << obj.album << " | " << std::setw(6) << std::right << obj.year << " | " << min << ":" << std::setw(2) << std::setfill('0') << sec << std::setfill(' ') << " | " << obj.m_price << " |";
		return out;
	}

	void SongCollection::display(std::ostream& out)
	{
		int amount = 0;
		auto sum = [&](Song obj)
		{
			amount += obj.length;
		};
		auto print = [=, &out](Song obj)
		{
			out << obj << std::endl;
		};
		std::for_each(songs.begin(), songs.end(), print);
		std::for_each(songs.begin(), songs.end(), sum);
		int hour = amount / 3600;
		int min = (amount - (hour * 3600)) / 60;
		int sec = amount - (min * 60) - (hour * 3600);
		print_dash('-', 88);
		out << "|" << std::setw(78) << std::right << "Total Listening Time: " << hour << ":" << min << ":" << sec << " |" << std::endl;
	}

	bool SongCollection::inCollection(std::string name) const
	{
		int n = std::count_if(songs.begin(), songs.end(), [=](Song obj)
		{
				if (obj.arstist == name)
					return true;
				else
					return false;
		});
		if (n > 0)
			return true;
		else
			return false;
	}

	void SongCollection::cleanAlbum()
	{
		auto remove = [=](Song& obj)
		{
			if (obj.album == "[None]")
				obj.album = "";
		};
		std::for_each(songs.begin(), songs.end(), remove);
	}

	void SongCollection::sort(std::string category)
	{
		if (category == "length")
		{
			std::sort(songs.begin(), songs.end(), [](Song one, Song two)
				{
					return one.length < two.length;
				});
		}
		else if (category == "title")
		{
			std::sort(songs.begin(), songs.end(), [](Song one, Song two)
				{
					return one.title < two.title;
				});
		}
		else if (category == "album")
		{
			std::sort(songs.begin(), songs.end(), [](Song one, Song two)
				{
					return one.album < two.album;
				});
		}
		else
		{
			std::cout << "Sorry, cannot sort by this value. Only 1) title 2)length 3)album" << std::endl;
		}
	}

	std::list<Song> SongCollection::getSongsForArtist(std::string fname) const
	{
		std::list<Song> artist_songs;
		auto songs_by_art = [&](Song obj)
		{
			if (obj.arstist == fname)
				artist_songs.push_back(obj);
		};
		std::for_each(songs.begin(), songs.end(), songs_by_art);
		return artist_songs;
	}
}
