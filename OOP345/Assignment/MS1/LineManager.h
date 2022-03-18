#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include <vector>
#include <deque>
#include <string>
#include "Workstation.h"
#include "CustomerOrder.h"

class LineManager
{
	std::vector<Workstation*> AssemblyLine;
	std::deque<CustomerOrder> toBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
public:
	LineManager(){this->m_cntCustomerOrder = 0;};
	LineManager(const std::string& record, std::vector<Workstation*>& workst_obj, std::vector<CustomerOrder>& custord_obj);
	bool run(std::ostream& os);
	void displayStations()const;
	void displayStationsSorted() const;
	void displayCompletedOrders(std::ostream& os) const;
};
#endif // !LINEMANAGER_H
