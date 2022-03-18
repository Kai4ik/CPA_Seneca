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
            sh_type = new char[strlen(type1)+1];
            strcpy(sh_type, type1);
            engine = new Engine[lenght];
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

    Ship::~Ship()
    {
        delete[] engine;
        delete[] sh_type;
    }

    void Ship::setEmpty()
    {
        numb = 0;
        sh_type = nullptr;;
        engine=nullptr;
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
        if (numb < 10 && sh_type != nullptr)
        {
            Engine* temp_arr = new Engine[numb + 1];
            for (int i = 0; i < numb; i++)
            {
                temp_arr[i] = engine[i];
            }
            temp_arr[numb] = e;
            delete[] engine;
            numb++;
           // engine = nullptr;
            engine = temp_arr;
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
