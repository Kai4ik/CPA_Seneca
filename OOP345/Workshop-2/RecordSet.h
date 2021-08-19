#ifndef SDDS_RECORDSET_H
#define SDDS_RECORDSET_H
#include <string>

namespace sdds
{
	class RecordSet
	{
		std::string* n_file;
		size_t counter=0;
	public:
		RecordSet();
		RecordSet(const char* name);
		RecordSet(const RecordSet& copy_obj);
		RecordSet(RecordSet&& move_obj);
		RecordSet& operator=(const RecordSet& copy_obj);
		RecordSet& operator=(RecordSet&& move_obj);
		~RecordSet();
		size_t size() const;
		std::string getRecord(size_t index) const;
	};
}
#endif // !SDDS_RECORDSET_H