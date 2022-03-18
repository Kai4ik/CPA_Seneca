#pragma once
#ifndef SDDS_ENGINE_H
#define SDDS_ENGINE_H
namespace sdds
{
	//const int maxname = 30;
	class Engine
	{
		double size;
		char type[31];
	public:
		Engine();
		Engine(const char* tengine,double cap );
		double get() const;
		void display() const;
		void setEmp();
	};
}
#endif