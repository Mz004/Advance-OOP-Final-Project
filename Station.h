/***********************************************************************
// Name: Manav Alpeshbhai Zadafiya
// Seneca Student ID: 144095221
// Seneca email: mazadafiya@myseneca.ca
// Date of completion: 2024-04-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
***********************************************************************/

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"

namespace seneca 
{
    class Station
    {
        int m_stationId{0};
        std::string m_itemName{};
        std::string m_description{};
        unsigned int m_serialNumber{};
        unsigned int m_noOfItems{};
        static size_t m_widthField;
        static unsigned int id_generator;

    public:
        Station(){};
        Station(const std::string str);

        const std::string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
    };

}
#endif // !SENECA_STATION_H