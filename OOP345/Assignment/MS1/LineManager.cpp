// Name: Kairat Orozobekov
// Seneca Student ID: 104 998 190
// Seneca email: korozobekov@myseneca.ca
// Date of completion: 08.01.20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

//  This helper function responsible for finding first function in the assembly line. 
// 1) We create empty vector of worksttion pointers and then fill it with all stations that are next stations for another station     
// 2) Then we iterate through this vector and via usage of count algorithm find position of station which is not next station for any of other stations                                  
// 3) We return this position

int find_first_stat(std::vector<Workstation*> AL)
{
	std::vector<Workstation*> obj;
	for (unsigned i = 0; i < AL.size(); ++i)
	{
		if (AL[i]->getNextStation() != nullptr)
			obj.push_back(AL[i]->getNextStation());
	}

	int first_station = 0;
	for (unsigned i = 0; i < AL.size(); ++i)
	{
		bool exist = std::count(obj.begin(), obj.end(), AL[i]) > 0 ? true : false;
		if (!exist)
			first_station = i;
	}
	return first_station;
}

//custom constructor that copies workstation objects from given parameter into assembly line vector, fills "ToBeFilled" queue with orders from given parameter and sets next station for each object of assembly line (via reading file which passed as a string)
LineManager::LineManager(const std::string& record, std::vector<Workstation*>& workst_obj, std::vector<CustomerOrder>& custord_obj) 
{
	std::ifstream file(record);
	if (!file)
		throw std::string("Unable to open [") + record + "] file.";
	this->AssemblyLine = workst_obj;
	std::string obj;
	while (!file.eof())
	{
		std::getline(file, obj, '|');
		for (unsigned i = 0; i < workst_obj.size(); ++i)
		{
			if (obj == workst_obj[i]->getItemName() && !file.eof())
			{
				std::getline(file, obj, '\n');
				std::for_each(workst_obj.begin(), workst_obj.end(), [&](Workstation* stat) { if (obj == stat->getItemName()) this->AssemblyLine[i]->setNextStation(*stat); });
				break;
			}
		}
	}
	this->m_cntCustomerOrder = custord_obj.size();
	for (unsigned i = 0; i < custord_obj.size(); ++i)
		this->toBeFilled.push_back(std::move(custord_obj[i]));
	file.close();
}

//function that performs 1 cycle of operations on the line by moving one order from "ToBeFilled" queue (if not empty) on starting station of assembly line (should be determined). Then runs 1 cycle of station's process. After that moves orders down the line. If order is completed, it should be moved to "Completed" queue. Function stops when all orders all filled.
bool LineManager::run(std::ostream& os)
{
	static int iter = 0;
	os << "Line Manager Iteration: " << ++iter << std::endl;

	if (this->toBeFilled.size() > 0)
	{
	 	*this->AssemblyLine[find_first_stat(this->AssemblyLine)] += std::move(this->toBeFilled.front());
		this->toBeFilled.pop_front();
	}
	std::for_each(this->AssemblyLine.begin(), this->AssemblyLine.end(), [&](Workstation* obj) { obj->runProcess(os); });
	std::for_each(this->AssemblyLine.begin(), this->AssemblyLine.end(), [&](Workstation* obj) { obj->moveOrder(); });
	CustomerOrder temp;
	std::for_each(this->AssemblyLine.begin(), this->AssemblyLine.end(), [&](Workstation* obj) { if (obj->getIfCompleted(temp)) Completed.push_front(std::move(temp)); });
	return this->m_cntCustomerOrder == this->Completed.size() ? true : false;
}

//displays all stations on the assesmbly line in the order they were received from client
void LineManager::displayStations() const
{
	std::for_each(this->AssemblyLine.begin(), this->AssemblyLine.end(), [](Workstation* obj) {obj->display(std::cout); });
}

//displays all stations on the assesmbly line in the order they are linked
void LineManager::displayStationsSorted() const
{
	std::vector <Workstation*> ors;
	ors.push_back(this->AssemblyLine[find_first_stat(this->AssemblyLine)]);
	while (this->AssemblyLine.size() != ors.size())
		ors.push_back(ors.back()->getNextStation());
	std::for_each(ors.begin(), ors.end(), [](Workstation* obj) { obj->display(std::cout); });
}

//displays all complted orders
void LineManager::displayCompletedOrders(std::ostream& os) const
{
	for (int i = Completed.size() - 1; i >= 0; --i)
		Completed[i].display(os);
}


