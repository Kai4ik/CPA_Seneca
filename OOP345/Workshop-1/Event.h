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