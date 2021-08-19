#include "TimedEvents.h"
#include <chrono>
#include <iostream>
#include <iomanip>

namespace sdds
{
	int TimedEvents::record_counter = 0;

	sdds::TimedEvents::TimedEvents()
	{
		record_counter = 0;
	}

	int TimedEvents::getRecorder()
	{
		return record_counter;
	}

	TimedEvents::~TimedEvents()
	{
		record_counter = 0;
	}

	void TimedEvents::startClock()
	{
		start_time = std::chrono::steady_clock::now();
	}

	void TimedEvents::stopClock()
	{
		end_time = std::chrono::steady_clock::now();
	}

	void TimedEvents::recordEvent(const char* name)
	{
		if (name != nullptr)
		{
			this->ev_descrip[getRecorder()].event_name = name;
			this->ev_descrip[getRecorder()].time_units = "nanoseconds";
			this->ev_descrip[getRecorder()].duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
			record_counter++;
		}
	}

	std::ostream& operator<<(std::ostream& os, const TimedEvents& obj)
	{
		os << "--------------------------" << std::endl;
		os << "Execution Times:" << std::endl;
		os << "--------------------------" << std::endl;
		for (short k = 0; k < TimedEvents::getRecorder(); k++)
		{
			os << std::setw(20) << std::left << obj.ev_descrip[k].event_name << std::setw(12) << std::right << obj.ev_descrip[k].duration.count() << " " << obj.ev_descrip[k].time_units << std::endl;
		}
		os << "--------------------------" << std::endl;
		return os;
	}
}
