/***********************************************************************
// Name: Manav Alpeshbhai Zadafiya
// Seneca Student ID: 144095221
// Seneca email: mazadafiya@myseneca.ca
// Date of completion: 2024-04-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
***********************************************************************/

#include "Workstation.h"
using namespace std;
namespace seneca

{
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;
    void Workstation::fill(std::ostream &os)
    {
        if (m_orders.size() > 0)
        {
            m_orders.front().fillItem((Station &)(*this), os);
        }
    }
    bool Workstation::attemptToMoveOrder()
    {
        bool isMoved = false;
        if (m_orders.size() > 0)
        {

            if (m_orders.front().isItemFilled(getItemName()) || Station(*this).getQuantity() < 1)
            {
                isMoved = true;
                if (m_pNextStation)
                {
                    *m_pNextStation += (std::move(m_orders.front()));
                }
                else
                {
                    m_orders.at(0).isOrderFilled() ? g_completed.push_back(std::move(m_orders.front())) : g_incomplete.push_back(std::move(m_orders.front()));
                }
                m_orders.pop_front();
            }
        }
        return isMoved;
    }
    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }
    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    }
    void Workstation::display(std::ostream &os) const
    {
        if (m_pNextStation)
        {
            os << Station(*this).getItemName() << " --> " << Station(*m_pNextStation).getItemName() << endl;
        }
        else
        {
            os << Station(*this).getItemName() << " --> End of Line" << endl;
        }
    }
    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}