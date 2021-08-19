#ifndef SDDS_TIMEDEVENTS_H
#define SDDS_TIMEDEVENTS_H
#include <chrono>
#include <string>

namespace sdds
{
	typedef std::chrono::steady_clock::time_point time_t;
	typedef std::chrono::steady_clock::duration durat_time;
	constexpr short MAX_RECORDS = 7;

	class TimedEvents
	{
		static int record_counter;
		time_t start_time;
		time_t end_time;
		struct
		{
			std::string event_name;
			std::string time_units;
			durat_time duration;
		} ev_descrip[MAX_RECORDS];

	public:
		TimedEvents();
		~TimedEvents();
		static int getRecorder();
		void startClock();
		void stopClock();
		void recordEvent(const char* name);
		friend std::ostream& operator<<(std::ostream& os, const TimedEvents& obj);
	};
}
#endif // !SDDS_TIMEDEVENTS_H