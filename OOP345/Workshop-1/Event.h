/* Student name: Kairat Orozobekov
   Student #: 104 998 190
   Student email: korozobekov@myseneca.ca
   Date submitted: 2020.05.26
   Course: OOP345, Section NEE
   I have done all the coding by myself and only copied the code that my professor provided 
   to complete my workshops and assignments. 
*/

#ifndef SDDS_EVENT_H 
#define SDDS_EVENT_H
#include <cstddef>
extern size_t g_sysClock;

namespace sdds
{
	class Event
	{
		char* descrip;
		unsigned long int time;
	public:
		Event();
		~Event();
		void display() const;
		void setDescription(char desc[]);
	};
}
#endif