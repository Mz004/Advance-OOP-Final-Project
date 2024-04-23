/***********************************************************************
// Name: Manav Alpeshbhai Zadafiya
// Seneca Student ID: 144095221
// Seneca email: mazadafiya@myseneca.ca
// Date of completion: 2024-04-04
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
***********************************************************************/


#include "LineManager.h"
using namespace std;
namespace seneca
{
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        Utilities temp{};
        size_t next_pos = 0;
        bool more = false;
        std::string line{};
        std::string c_name{};
        std::string n_name{};
        bool found = false;
        ifstream fin(file);
        if (fin.is_open()) // checking if file is open
        {

            while (!fin.eof() && m_activeLine.size() < stations.size()) // looping until end of file
            {
                getline(fin, line); // extracting a line from the file
                next_pos = 0;
                c_name = temp.extractToken(line, next_pos, more); // extracting first token
                if (more)                                         // checking if there is more token to extract
                {
                    n_name = temp.extractToken(line, next_pos, more); // extracting next station
                }
                else
                {
                    n_name.clear();
                }
                // adding stations to active line && setting next station
                for_each(stations.begin(), stations.end(), [&c_name, &n_name, this, &stations](Workstation *w)
                         {
                if (w->getItemName() == c_name)// checking if item name matches with the first token extracted
                {
                        if(!n_name.empty())//checking if next station token is not empty
                        {
                        for_each(stations.begin(), stations.end(), [&n_name,this,&w](Workstation *w2)
                         {

                        if (w2->getItemName() == n_name)// checking if next station token matches with item in next station of the itrator
                        {
                            // setting current itrator w2 as next station of w 
                        w->setNextStation(w2);
                        m_activeLine.push_back(w);// adding w to active line 
                        }
                        });
                        }
                        else
                        {
                            w->setNextStation();
                            m_activeLine.push_back(w);
                        }
                } });
            }
            // finding first station
            for_each(m_activeLine.begin(), m_activeLine.end(), [&found, this](Workstation *w)
                     { found = all_of(m_activeLine.begin(), m_activeLine.end(), [&w](Workstation *w2)
                                  { if(w2->getNextStation())
                                  {
                                    return w->getItemName() != w2->getNextStation()->getItemName();
                                  }
                                  else
                                  {
                                    return true;
                                  }
                                     });
                    if(found)
                    {
                        m_firstStation=w;
                    } });
        }
        else
        {
            throw "bad filename!";
        }
        fin.close();
        m_cntCustomerOrder = g_pending.size();
    }
    void LineManager::reorderStations()
    {
        size_t index = 0;
        swap(m_activeLine[0], *find(m_activeLine.begin(), m_activeLine.end(), m_firstStation));
        index++;
        while (index < m_activeLine.size())
        {
            if (m_activeLine[index]->getNextStation())
            {

                swap(m_activeLine[index + 1], *find(m_activeLine.begin(), m_activeLine.end(), m_activeLine[index]->getNextStation()));
            }
            index++;
        }
    }
    bool LineManager::run(std::ostream &os)
    {
        static int count{0};
        os << "Line Manager Iteration: " << ++count << endl;
        if (g_pending.size() > 0)
        {
            *m_firstStation += (std::move(g_pending.front()));
            g_pending.pop_front();
        }
        for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation *w)
                 { w->fill(os); });

        for (size_t i = 0; i < m_activeLine.size(); i++)
        {
            m_activeLine[i]->attemptToMoveOrder();
        }
        return g_completed.size()+g_incomplete.size()==m_cntCustomerOrder;
    }
    void LineManager::display(std::ostream &os) const
    {
        for (size_t i = 0; i < m_activeLine.size(); i++)
        {
            m_activeLine[i]->display(os);
        }
    }
}