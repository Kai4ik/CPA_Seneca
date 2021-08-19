// Name: Kairat Orozobekov
// Seneca Student ID: 104 998 190
// Seneca email: korozobekov@myseneca.ca
// Date of completion: 08.01.20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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
	bool runt(std::ostream& os);
	void displayStations()const;
	void displayStationsSorted() const;
	void displayCompletedOrders(std::ostream& os) const;
};
#endif // !LINEMANAGER_H
