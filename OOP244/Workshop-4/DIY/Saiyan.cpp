/**********************************************************
 * Name: Kairat Orozobekov
 * Student ID: 104 998 190
 * Seneca email: korozobekov@myseneca.ca
 * Section: NBB
 **********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Saiyan.h"
using namespace std;

namespace sdds
{

    Saiyan::Saiyan(const char* name, int dob, int power)
    {
        set(name, dob, power);
    }

    Saiyan::Saiyan()
    {
        setEmpty();
    }

    Saiyan::~Saiyan()
    {
        delete[] this->m_name;
    }

    bool Saiyan::isSuper() const
    {
        return this->m_super;
    }

    bool Saiyan::isValid() const
    {
        return (this->m_power > 0);
    }

    void Saiyan::setEmpty()
    {
        this->m_name = nullptr;
        this->m_dob = 0;
        this->m_power = -1;
        this->m_super = false;
    }

    void Saiyan::display() const
    {
        if (this->m_dob > 2020 || this->m_power < 0)
        {
            cout << "Invalid Saiyan!" << endl;
        }
        else
        {
            cout << this->m_name << endl;
            cout << "DOB: " << this->m_dob << " Power: " << this->m_power << endl;
            if (this->m_super)
            {
                cout << "Super Saiyan Ability: Super Saiyan." << endl;
                cout << "Super Saiyan level is: " << this->m_level;
            }
            else
            {
                cout << "Super Saiyan Ability: Not super Saiyan." << endl;
            }
            cout << endl;
        }
    }

    void Saiyan::set(const char* name, int dob, int power, int level, bool super /* = false*/)
    {
        if (name == nullptr || strlen(name) == 0 || dob > 2020 || power <= 0 || level < 0)
        {
            setEmpty();
        }
        else
        {
            this->m_name = new char[MAX_NAME + 1];
            strncpy(this->m_name, name, MAX_NAME);
            this->m_dob = dob;
            this->m_level = level;
            this->m_power = power;
            if (super == true)
            {
                this->m_super = true;
            }
            else
            {
                this->m_super = false;
            }
        }
    }

    bool Saiyan::hasLost(Saiyan& other)
    {
        if (isValid() && other.isValid())
        {
            powerup();
            other.powerup();
            if (this->m_power > other.m_power)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    void Saiyan::powerup()
    {
        if (this->m_super != false)
        {
            this->m_power = this->m_power * (this->m_level + 1);
        }
    }
}

