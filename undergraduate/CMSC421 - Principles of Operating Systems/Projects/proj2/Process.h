//---------------------------------------------------
// File       : Process.h
// Author     : Patrick Trinkle
// Date       : April 17 2006
// UMBC Email : tri1@umbc.edu
// Project    : 2
//---------------------------------------------------

#include "Project2.h"
#include "Memory.h"

#ifndef _Process_h
#define _Process_h

using namespace std;

class Process
{
  public:
   Process(int size, int pid, int pageSize, Memory * mem, string filename)
      :m_pid(pid), m_pageSize(pageSize), m_mem(mem), m_filename(filename)
      {
	 for (int i = 0; i < size; ++i)
	    m_pagetbl.push_back(-1);
      }

   Process & operator=(const Process & rhs) {
      if ( this != &rhs )
      {
	 m_pid = rhs.m_pid;
	 m_pageSize = rhs.m_pageSize;
	 m_pagetbl = rhs.m_pagetbl;
	 m_mem = rhs.m_mem;
	 m_filename = rhs.m_filename;
	 m_loc = rhs.m_loc;
      }

      return *this;
   }

   Process(const Process & rhs) {
      if ( this != &rhs )
      {
	 m_pid = rhs.m_pid;
	 m_pageSize = rhs.m_pageSize;
	 m_pagetbl = rhs.m_pagetbl;
	 m_mem = rhs.m_mem;
	 m_filename = rhs.m_filename;
	 m_loc = rhs.m_loc;
      }
   }
   
   bool inMain() {
      return m_loc;
   }
   void nowInmain() {
      m_loc = true;
   }
   void nowInvirtual() {
      m_loc = false;
   }

   bool isValidPg(int pagenum) {
      return ( (unsigned)pagenum < m_pagetbl.size()) ? true: false;
   }
   int  getFrame(int pagenum) {
      return m_pagetbl.at(pagenum);
   }
   int  getPage(int logical) {
      return logical / m_pageSize;
   }
   int  calcOffset(int logical) {
      return logical % m_pageSize;
   }

   void run();

   vector<int> exportPgtbl() {
      return m_pagetbl;
   }
   void        importPgtbl(vector<int> pagetbl) {
      m_pagetbl = pagetbl;
   }

   int getPid() {
      return m_pid;
   }
   int getSize() {
      return m_pagetbl.size();
   }

  private:
   int m_pid;
   int m_pageSize;
   vector<int> m_pagetbl;
   Memory * m_mem;
   string m_filename;
   bool m_loc; // if in main: true
};

#endif
