/***********************************************************************
// OOP244 Workshop 9: Templates
// File NumbersBoxTester.cpp
// Version 1.0
// Date	2020/3/20
// Author	Hong Zhan (Michael) Huang
// Description
// Tests the Calculator template and its functions
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
// Michael
/////////////////////////////////////////////////////////////////
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include "NumbersBox.h"
using namespace std;
using namespace sdds;

ostream& line(int len, char ch)
{
    for (int i = 0; i < len; i++, cout << ch);
    return cout;
}
ostream& number(int num)
{
    cout << num;
    for (int i = 0; i < 9; i++)
    {
        cout << " - " << num;
    }
    return cout;
}

int main()
{

    cout << "Create an int and double NumbersBox" << endl;
    line(64, '-') << endl;
    number(1) << endl;
    NumbersBox<int> intbox(3, "Int Box");
    NumbersBox<double> doublebox(3, "Double Box");

    cout << "Populate intbox and doublebox and display" << endl;
    line(64, '-') << endl;
    number(2) << endl;
    intbox[0] = 22;
    intbox[1] = 33;
    intbox[2] = 44;
    doublebox[0] = 1.5;
    doublebox[1] = 2.5;
    doublebox[2] = 3.5;
    cout << intbox << endl;
    cout << doublebox << endl;

    cout << "Perform *= operation on intboxs, first of not matching sizes then matching sizes" << endl;
    line(64, '-') << endl;
    number(3) << endl;
    NumbersBox<int> bigintbox(5, "big int box");
    intbox *= bigintbox;
    cout << intbox << endl;

    intbox *= intbox;
    cout << intbox << endl;

    cout << "Perform *= operation on doubleboxs, first of not matching sizes then matching sizes" << endl;
    line(64, '-') << endl;
    number(4) << endl;
    NumbersBox<double> emptydoublebox;
    cout << emptydoublebox << endl;
    doublebox *= emptydoublebox;
    cout << doublebox << endl;
    doublebox *= doublebox;
    cout << doublebox << endl;

   cout << "Perform += on intbox and doublebox and add a new item to it" << endl;
    line(64, '-') << endl;
    number(5) << endl;
    intbox += 999;
    doublebox += 999.999;
    cout << intbox << endl;
    cout << doublebox << endl;

    return 0;
}

/* EXPECTED OUTPUT
Create an int and double NumbersBox
----------------------------------------------------------------
1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1 - 1
Populate intbox and doublebox and display
----------------------------------------------------------------
2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2 - 2
Box name: Int Box
22, 33, 44
Box name: Double Box
1.5, 2.5, 3.5
Perform *= operation on intboxs, first of not matching sizes then matching sizes
----------------------------------------------------------------
3 - 3 - 3 - 3 - 3 - 3 - 3 - 3 - 3 - 3
Box name: Int Box
22, 33, 44
Box name: Int Box
484, 1089, 1936
Perform *= operation on doubleboxs, first of not matching sizes then matching sizes
----------------------------------------------------------------
4 - 4 - 4 - 4 - 4 - 4 - 4 - 4 - 4 - 4
Empty Box
Box name: Double Box
1.5, 2.5, 3.5
Box name: Double Box
2.25, 6.25, 12.25
Perform += on intbox and doublebox and add a new item to it
----------------------------------------------------------------
5 - 5 - 5 - 5 - 5 - 5 - 5 - 5 - 5 - 5
Box name: Int Box
484, 1089, 1936, 999
Box name: Double Box
2.25, 6.25, 12.25, 999.999
*/