//---------------------------------------------------
// File       : PidQueue.h
// Author     : Patrick Trinkle
// Date       : April 17 2006
// UMBC Email : tri1@umbc.edu
// Project    : 2
//---------------------------------------------------

#include "Project2.h"

#ifndef _PidQueue_h
#define _PidQueue_h

using namespace std;

class PidQueue
{
  public:

   void push_back(int pid) {
      m_pids.push_back(pid);
   }

   void move_to_front(int pid) {

      vector<int>::iterator iterator;
      
      for (iterator = m_pids.begin(); iterator != m_pids.end(); iterator++)
	 if (*iterator == pid)
	 {
	    m_pids.erase(iterator);
	    break;
	 }

      m_pids.insert(m_pids.begin(), pid);
   }

   void remove(int pid) {
      
      vector<int>::iterator iterator;

      for (iterator = m_pids.begin(); iterator != m_pids.end(); iterator++)
	 if (*iterator == pid)
	 {
	    m_pids.erase(iterator);
	    break;
	 }
   }

   int get_last() {
      return int(m_pids.back());
   }

   void print() {
      for (unsigned int i = 0; i < m_pids.size(); ++i)
	 cout << m_pids.at(i) << endl;
   }

   int getPid(int index) {
      return m_pids.at(index);
   }

   int getSize() {
      return m_pids.size();
   }

  private:
   vector<int> m_pids;
};

#endif
