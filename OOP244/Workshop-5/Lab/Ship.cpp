/**********************************************************
 * Name: Kairat Orozobekov
 * Student ID: 104 998 190
 * Seneca email: korozobekov@myseneca.ca
 * Section: NBB
 **********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Ship.h"
#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

namespace sdds
{
    Ship::Ship()
    {
        setEmpty();
    }

    Ship::Ship(const char* type1, Engine* engines, int lenght)
    {
        if (sizeof(engines) <= 10 && strlen(type1) <= 7 && type1 != nullptr)
        {
            numb = lenght;
            strcpy(sh_type, type1);
            for (int i = 0; i < lenght; i++)
            {
                engine[i] = engines[i];
            }
        }
	else
        {
            setEmpty();
        }
    }

    void Ship::setEmpty()
    {
        numb = 0;
        sh_type[0] = '\0';
        Ship::engine[0] = Engine();
    }

    bool Ship::empty() const
    {
        if (numb > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Ship& Ship::operator+=(Engine e)
    {
        if (numb < 10 && strlen(sh_type) != 0)
        {
            numb++;
            engine[numb-1] = e;
        }
        else
        {
            cout << "The ship doesn't have a type! Engine cannot be added!" << endl;
        }
        return*this;
    }


    float Ship::calculatePower() const
    {
        float power = 0;
        for (int i = 0; i < numb; i++)
        {
            power += engine[i].get();
        }
        power *= 5;
        return power;
    }


    void Ship::display() const
    {   
        if (empty() == true)
        {
            cout << sh_type <<  "-" << setw (6) << fixed << setprecision(2) << calculatePower() << endl;
            for (int i = 0; i < numb; i++)
            {
                cout.setf(ios::fixed);
                cout.precision(2);
                engine[i].display();
            }
        } 
        else {
            cout << "No available data" << endl;
        }
    }

    bool operator==(const Ship& sh1, const Ship& sh2)
    {
        if (sh1.calculatePower() == sh2.calculatePower())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator<(const Ship& ship, double max)
    {
        if (ship.calculatePower() < max)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


}
