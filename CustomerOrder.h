/***********************************************************************
// Name: Manav Alpeshbhai Zadafiya
// Seneca Student ID: 144095221
// Seneca email: mazadafiya@myseneca.ca
// Date of completion: 2024-04-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
***********************************************************************/

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Station.h"

namespace seneca
{
    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{ 0 };
        bool m_isFilled{ false };

        Item(const std::string& src) : m_itemName(src) {};
    };
    class CustomerOrder
    {
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{ 0 };
        Item** m_lstItem{ nullptr };
        static size_t m_widthField;

        void deallocate();

    public:
        CustomerOrder() {};
        CustomerOrder(const std::string& str);
        CustomerOrder(const CustomerOrder& rightHand);
        CustomerOrder(CustomerOrder&& rightHand) noexcept;
        ~CustomerOrder();

        CustomerOrder& operator=(const CustomerOrder& rightHand) = delete;
        CustomerOrder& operator=(CustomerOrder&& rightHand) noexcept;

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif  // !SENECA_CUSTOMERORDER_H