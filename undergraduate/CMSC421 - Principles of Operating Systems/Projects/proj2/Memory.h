//---------------------------------------------------
// File       : Memory.h
// Author     : Patrick Trinkle
// Date       : April 17 2006
// UMBC Email : tri1@umbc.edu
// Project    : 2
//---------------------------------------------------

#include "Project2.h"

#ifndef _Memory_h
#define _Memory_h

using namespace std;

class Memory
{
  public:
   Memory(int size, int numMain, int numVirtual)
      :m_pageSize(size), m_mainSize(numMain), m_virtualSize(numVirtual)
      { 
	 m_mainMemory = (char * )malloc(sizeof(char) * m_pageSize * numMain);
	 m_virtualMemory = (char *)malloc(sizeof(char) * m_pageSize * numVirtual);

	 // build does not clear the garbage

	 build();
      }
   
   void purge() {
      free(m_mainMemory);
      free(m_virtualMemory);
      m_freeMFrames.clear();
      m_freeVFrames.clear();
   }

   int numPgsMain() {
      return m_mainSize;
   }
   int isFreeMain() {
      return m_freeMFrames.size();
   }
   int isFreeVirtual() {
      return m_freeVFrames.size();
   }
   int getpgSize() {
      return m_pageSize;
   }

   void setValue(int frame_id, int offset, int value) {
      m_mainMemory[frame_id * m_pageSize + offset] = (char) value;
   }
   int  getValue(int frame_id, int offset) {
      return (int) m_mainMemory[frame_id * m_pageSize + offset];
   }
   
   int allocateMFrame();
   int allocateVFrame();

   void deallocateM(int frame) {
      clearMframe(frame);
      m_freeMFrames.push_back(frame);
   }
   void deallocateV(int frame) {
      clearVframe(frame);
      m_freeVFrames.push_back(frame);
   }

   void cpVirttoMain(int virt, int main) {
      for (int i = 0; i < m_pageSize; ++i)
	 m_mainMemory[main * m_pageSize + i] = m_virtualMemory[virt * m_pageSize + i];
   }

   void cpMaintoVirt(int main, int virt) {
      for (int i = 0; i < m_pageSize; ++i)
	 m_virtualMemory[virt * m_pageSize + i] = m_mainMemory[main * m_pageSize + i];
   }

   void clearMframe(int frame) {
      for (int i = 0; i < m_pageSize; ++i)
	 m_mainMemory[(frame * m_pageSize) + i] = '0';
   }
   void clearVframe(int frame) {
      for (int i = 0; i < m_pageSize; ++i)
	 m_virtualMemory[(frame * m_pageSize) + i] = '0';
   }

  private:
   void build() {
      for (int i = 0; i < m_mainSize; ++i)
	 m_freeMFrames.push_back(i);

      for (int i = 0; i < m_virtualSize; ++i)
	 m_freeVFrames.push_back(i);
   }

   char * m_mainMemory;
   char * m_virtualMemory;

   vector<int>  m_freeMFrames;
   vector<int>  m_freeVFrames;

   int m_pageSize;
   int m_mainSize;
   int m_virtualSize;
};

#endif
