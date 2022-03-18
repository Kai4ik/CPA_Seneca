#ifndef WORKSTATION_H
#define WORKSTATION_H
#include "Station.h"
#include "CustomerOrder.h"
#include <deque>
#include <string>

//class that simulates station on the assembly line and inherited from "Station" class

class Workstation : public Station
{
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation;
public:
	Workstation(const std::string& record);
	Workstation(Workstation& obj) = delete;
	Workstation(Workstation&& obj) = delete;
	Workstation& operator=(Workstation&& obj) = delete;
	Workstation& operator=(const Workstation& obj) = delete;
	void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Workstation& obj);
	Workstation* getNextStation()const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream&);
	Workstation& operator+=(CustomerOrder&& obj);
};
#endif // !WORKSTATION_H
