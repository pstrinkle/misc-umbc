#include "Memory.h"

using namespace std;

int Memory::allocateMFrame()
{
   int framenum = -1;

   if ( m_freeMFrames.size() > 0 )
   {
      int lastobject = m_freeMFrames.size() - 1;
      framenum = m_freeMFrames.at(lastobject);
      m_freeMFrames.pop_back();
   }

   return framenum;
}

int Memory::allocateVFrame()
{
   int framenum = -1;

   if ( m_freeVFrames.size() > 0 )
   {
      int lastobject = m_freeVFrames.size() - 1;
      framenum = m_freeVFrames.at(lastobject);
      m_freeVFrames.pop_back();
   }

   return framenum;
}


