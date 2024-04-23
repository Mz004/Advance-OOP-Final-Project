/***********************************************************************
// Name: Manav Alpeshbhai Zadafiya
// Seneca Student ID: 144095221
// Seneca email: mazadafiya@myseneca.ca
// Date of completion: 2024-04-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
***********************************************************************/

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Workstation.h"

namespace seneca
{
    class LineManager
    {
        std::vector<Workstation *> m_activeLine;
        size_t m_cntCustomerOrder{0};
        Workstation *m_firstStation{nullptr};

    public:
        LineManager(){};
        LineManager(const std::string &file, const std::vector<Workstation *> &stations);

        void reorderStations();
        bool run(std::ostream &os);
        void display(std::ostream &os) const;
    };
}
#endif // !SENECA_LINEMANAGER_H