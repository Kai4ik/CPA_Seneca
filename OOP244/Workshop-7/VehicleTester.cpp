// OOP244 Workshop 7: Inheritance
// File: VehicleTester.cpp
// Version: 1.0
// Date: 02/28/2020
// Author: Nargis Khan
// Description:
// This file tests lab section of your workshop
/////////////////////////////////////////////
// -----------------------------------------------------------
// Name            Date            Reason
// Nargis Khan
/////////////////////////////////////////////////////////////////

#include <iostream>
#include "Vehicle.h"
#include "Car.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
using namespace sdds;

int main()
{
    cout << "---------------------------------------------" << endl;
    cout << "*** Checking Car default constructor ***" << endl;
    Car c1;
    c1.display(cout);

    cout << "------------------------------------------------" << endl;
    cout << "*** Checking Car 4 arg constructor (invalid ***)" << endl;
    Car c2("", 2016, 100, 5);
    Car c3("SUV", 1999, -120, 8);
    Car c4("sports", 1998, 110, 0);
    c2.display(cout);
    c3.display(cout);
    c4.display(cout);
    cout << "-----------------------------------------------" << endl;

    cout << "*** Checking Car 4 arg constructor (valid) ***" << endl;
    Car c5("SEDAN", 2016, 120, 5);
    Car c6("SUV", 2018, 110, 8);
    Car c7("SPORTS", 2020, 130, 2);
    c5.display(cout);
    c6.display(cout);
    c7.display(cout);
    cout << "---------------------------------------------------" << endl;

    cout << "*** Checking custom input and output operator ***" << endl;
    cin >> c1;
    cin.ignore(2000, '\n');
    cout << c1;
    cout << "---------------------------------------------------" << endl;

    cout << "*** Checking Car finetune ***" << endl;
    c1.finetune();
    cout << c1;
    cout << "----------------------------------------------------" << endl;

    cout << "*** Checking Car finetune for nonempty car ***" << endl;
    cin >> c4;
    c4.finetune();
    cout << c4;

    return 0;
}
/* Execution sample:
---------------------------------------------
*** Checking Car default constructor ***
Car is not initiated yet
------------------------------------------------
*** Checking Car 4 arg constructor (invalid ***)
Car is not initiated yet
Car is not initiated yet
Car is not initiated yet
-----------------------------------------------
*** Checking Car 4 arg constructor (valid) ***
SEDAN               2016|120|5
SUV                 2018|110|8
SPORTS              2020|130|2
---------------------------------------------------
*** Checking custom input and output operator ***
Enter the car type: sedan
Enter the car registration year: 2019
Enter the Vehicle`s speed: 150
Enter no of seats: 5
sedan               2019|150|5
Car has to be fine tuned for speed limit
---------------------------------------------------
*** Checking Car finetune ***
This car is finely tuned to default speed
sedan               2019|100|5
----------------------------------------------------
*** Checking Car finetune for nonempty car ***
Enter the car type: sports
Enter the car registration year: 1999
Enter the Vehicle`s speed: 120
Enter no of seats: 2
Car cannot be tuned and has to be scraped
Car is not initiated yet
*/