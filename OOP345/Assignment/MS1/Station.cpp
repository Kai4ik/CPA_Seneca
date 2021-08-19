// Name: Kairat Orozobekov
// Seneca Student ID: 104 998 190
// Seneca email: korozobekov@myseneca.ca
// Date of completion: 08.01.20
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>

size_t Station::m_widthField = 0;
int Station::id_generator = 0;

Station::Station(const std::string& station_obj)
{
	bool more = false;
	Utilities obj;
	size_t fp = -1;
	this->item_name = obj.extractToken(station_obj, fp, more);
	this->serial_numb = std::stoi(obj.extractToken(station_obj, fp, more));
	this->cur_item_numb = std::stoi(obj.extractToken(station_obj, fp, more));
	if (this->m_widthField < obj.getFieldWidth())
		this->m_widthField = obj.getFieldWidth();
	this->desc = obj.extractToken(station_obj, fp, more);
	this->id = ++this->id_generator;
}

const std::string& Station::getItemName() const   { return this->item_name; }

unsigned int Station::getQuantity() const   {  return this->cur_item_numb; }

void Station::updateQuantity()
{
	if (this->getQuantity() > 0)
		this->cur_item_numb -= 1;
}

unsigned int Station::getNextSerialNumber() { return this->serial_numb++; }

void Station::display(std::ostream& out, bool full) const
{
	out << "[" << std::setw(3) << std::setfill('0') << this->id << std::setfill(' ') << "] Item: " << std::setw(this->m_widthField) << std::left << this->getItemName() << std::right << " [" << std::setw(6) << std::setfill('0') << this->serial_numb << "]" << std::right;
	if (full == true)
		out << " Quantity: " << std::setw(this->m_widthField) << std::setfill(' ') << std::left << this->getQuantity() << std::right << " Description: " << this->desc;
	out << std::endl;
}