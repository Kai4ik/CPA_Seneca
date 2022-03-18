#include "Workstation.h"
#include <iostream>

Workstation::Workstation(const std::string& record) :Workstation::Station(record) { m_pNextStation = nullptr; }

//fucntion that fills first order in the queue if it's not empty
void Workstation::runProcess(std::ostream& os)
{
	if (this->m_orders.empty() != true)
		this->m_pNextStation != nullptr ? m_orders.front().fillItem(*this, os) : this->m_orders[this->m_orders.size() - 1].fillItem(*this, os);
}

//function responsible for moving first order in the queue to the next station on line (if order does not require filling)
bool Workstation::moveOrder()
{
	if ( this->m_orders.empty() != true && this->m_orders.front().isItemFilled(this->getItemName()) && this->m_pNextStation != nullptr)
	{
		*this->m_pNextStation += std::move(this->m_orders.front());
		this->m_orders.pop_front();
		return true;
	}
	return false;
}

//function that sets next station for current station. Next station passed as a parameter
void Workstation::setNextStation(Workstation& obj) { this->m_pNextStation = &obj; }

Workstation* Workstation::getNextStation() const { return this->m_pNextStation;}

//function checks if order at the front of the queue is completed or no. If yes, it removes that order, places it in the parameter
bool Workstation::getIfCompleted(CustomerOrder& order)
{
	// IMPORTANT: order of this conditions should be exactly like this. First it should check if queue is empty and just then if order is filled. Otherwise if queue is empty, it's gonna request for first order which does not exist, which will lead to error
	if (!this->m_orders.empty() && this->m_orders.front().isOrderFilled() == true)
	{
		order = std::move(this->m_orders.front());
		this->m_orders.pop_front();
		return true;
	}
	return false;
}

void Workstation::display(std::ostream& os)
{
	os << this->getItemName() << " --> ";
	this->m_pNextStation == nullptr ? os << "END OF LINE" << std::endl : os << this->m_pNextStation->getItemName() << std::endl;
}

//operator overloa that helps to move parameter onto the back of order's queue
Workstation& Workstation::operator+=(CustomerOrder&& obj)
{
	this->m_orders.push_back(std::move(obj));
	return *this;
}
