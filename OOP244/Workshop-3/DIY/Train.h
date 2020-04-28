/* Name: Kairat Orozobekov
   Student ID: 104 998 190
   Email: korozobekov@myseneca.ca
   Section: NAB */

 // Train.h
#ifndef SDDS_TRAIN_H 
#define SDDS_TRAIN_H
using namespace std;


namespace sdds
{
	const int MAX_NAME = 30;
	const int MAX_DESC = 20;
	const double MAX_WEIGHT = 700.555;
	const double MIN_WEIGHT = 40.444;

	class Cargo
	{
		char description[MAX_DESC];
		double weight;
	public:
		void setDescript(const char* desc);
		void setWeight(double weight66);
		double get_weight() const;
		const char* getDescrip() const;
		void init(const char* desc, double weight);
	};

	class Train
	{
	private:
		char name[MAX_NAME];
		int id;
		Cargo* cargo;
	public:
		void setTrain(const char* name, int id);
		bool isEmpty() const;
		void display() const;
		void loadCargo(Cargo& goods);
		void unloadCargo();
		bool increaseCargo(double numb);
		bool decreaseCargo(double decline);
		bool swapCargo(Train& refer);
	};
}
#endif