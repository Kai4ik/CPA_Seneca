// OOP244 Workshop 8: virtual functions
// File: EmployeeTester.cpp
// Version: 1.0
// Date: 03/11/2020
// Author: Nargis Khan
// Description:
// Tests the Employee and its derived classes via virtual functions
/////////////////////////////////////////////
// -----------------------------------------------------------
// Name Date Reason
// Nargis
/////////////////////////////////////////////////////////////////
#include<iostream>
#include "Doctor.h"
#include "Engineer.h"

using namespace std;
using namespace sdds;

int main()
{

    cout << "---------------------------------------------------------" << endl;
    cout << "*** checking Doctor & Engineer default constructor **** " << endl;
    Doctor d1;
    Engineer e1;
    d1.display(cout);
    e1.display(cout) << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "*** checking Doctor & Engineer parameterized constr (valid) *** " << endl;
    Employee* emp[4];

    emp[0] = new Doctor("General", 10100.00, 6);
    emp[1] = new Doctor("Specialist", 10100.00, 10, true);
    emp[2] = new Engineer(5595.00, 5, 1);
    emp[3] = new Engineer(5595.00, 8, 4);

    for (int i = 0; i < 4; ++i)
        emp[i]->display(cout) << endl;

    cout << "----------------------------------------------------------" << endl;

    cout << "*** checking bonus on current salary of Doctor ***" << endl;

    emp[0]->bonus();
    emp[1]->bonus();
    emp[0]->display(cout) << endl;
    emp[1]->display(cout) << endl;

    cout << "----------------------------------------------------------" << endl;
    cout << "*** checking bonus on current salary of Engineer ***" << endl;
    emp[2]->bonus();
    emp[2]->display(cout) << endl;;
    emp[3]->bonus();
    emp[3]->display(cout) << endl;
    // Cleaning up the memory
    for (int i = 0; i < 4; ++i)
        delete emp[i];
    return 0;
}

/*
---------------------------------------------------------
*** checking Doctor & Engineer default constructor ****
Doctor is not initiated yet
Engineer is not initiated yet
----------------------------------------------------------
*** checking Doctor & Engineer parameterized constr (valid) ***
Doctor details
Doctor Type: General
Salary: 10100.00
Working Hours: 6
Doctor details
Doctor Type: Specialist
Salary: 12100.00
Working Hours: 10
Engineer details
level: 1
Salary: 5595.00
Working hours: 5
Engineer details
level: 4
Salary: 8595.00
Working hours: 8
----------------------------------------------------------
*** checking bonus on current salary of Doctor ***
Doctor details
Doctor Type: General
Salary: 10605.00
Working Hours: 6
Doctor details
Doctor Type: Specialist
Salary: 13310.00
Working Hours: 10
----------------------------------------------------------
*** checking bonus on current salary of Engineer ***
Engineer details
level: 1
Salary: 5874.75
Working hours: 5
Engineer details
level: 4
Salary: 9454.50
Working hours: 8
*/