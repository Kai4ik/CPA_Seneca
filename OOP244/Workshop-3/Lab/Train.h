// Train.h
#ifndef SDDS_TRAIN_H 
#define SDDS_TRAIN_H
using namespace std;


namespace sdds
{
	const int MAX_NAME = 30;
	const int MAX_DESC = 20;

	struct Cargo
	{
		char description[MAX_DESC];
		double weight;
	};

	class Train
	{
	private:
		char name[MAX_NAME];
		int id;
		Cargo* cargo;
	public :
		void setTrain(const char* name, int id);
		bool isEmpty() const;
		void display() const;
		void loadCargo(Cargo goods);
		void unloadCargo();
	};
}
#endif