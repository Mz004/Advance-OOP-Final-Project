/***********************************************************************
// Name: Manav Alpeshbhai Zadafiya
// Seneca Student ID: 144095221
// Seneca email: mazadafiya@myseneca.ca
// Date of completion: 2024-04-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
***********************************************************************/

#include "Station.h"

using namespace std;

namespace seneca
{
    size_t Station::m_widthField = 0;
    unsigned int Station::id_generator = 0;
    Station::Station(const std::string str)
    {
        m_stationId = ++id_generator;
        Utilities temp{};
        size_t next_pos = 0;
        bool more = false;

        m_itemName = temp.extractToken(str, next_pos, more);
        if (more) {
            try
            {
                m_serialNumber = std::stoi(temp.extractToken(str, next_pos, more));
            }
            catch (...)
            {
                m_serialNumber = 0;
            }
        }
        if (more) {
            try
            {
                m_noOfItems = std::stoi(temp.extractToken(str, next_pos, more));
            }
            catch (...)
            {
            }
        }
        if (more) {
            m_widthField = this->m_widthField < temp.getFieldWidth() ? temp.getFieldWidth() : this->m_widthField;
            m_description = temp.extractToken(str, next_pos, more);
        }

    }
    const std::string &Station::getItemName() const
    {
        return m_itemName;
    }
    size_t Station::getNextSerialNumber()
    {
        return m_serialNumber++;
    }
    size_t Station::getQuantity() const
    {
        return m_noOfItems;
    }
    void Station::updateQuantity()
    {
        if (m_noOfItems > 0)
        {
            m_noOfItems--;
        }
    }
    void Station::display(std::ostream &os, bool full) const
    {
        os << setw(3) <<setfill('0')<<right<< m_stationId << " | ";
        os << setw(Station::m_widthField+1)<<setfill(' ') <<left<< m_itemName << "| ";
        os << setw(6)<<setfill('0') <<right<< m_serialNumber <<setfill(' ')<< " | ";
        if (full)
        {
            os << right<<setw(4) << m_noOfItems << " | ";
            os << m_description;
        }
        os << endl;
    }
}