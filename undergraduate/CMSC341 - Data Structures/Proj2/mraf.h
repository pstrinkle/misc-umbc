//---------------------------------------------------                              
// File       : MRAF.h                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The MRAF Class used for Proj2                                      
//---------------------------------------------------


#ifndef MRAF_H_
#define MRAF_H_

#include "List.h"

using namespace std;

template<class Object>
class Mraf
{
  public:
   Mraf();
   Mraf(const Mraf<Object>& mraf);
   ~Mraf();

   bool isEmpty() const;

   ListItr<Object> first() const;

   void makeEmpty();

   ListItr<Object> find(const Object& x);

   void insertAtFront(const Object& x);

   void remove(const Object& x);

   const Mraf& operator=(const Mraf<Object>& mraf);

   int GetTotal() const;

   void ResetTotal();

  private:
   List<Object> m_theList;
};

#include "mraf.cpp"

#endif
