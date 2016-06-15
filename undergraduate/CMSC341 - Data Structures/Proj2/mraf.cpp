//---------------------------------------------------                              
// File       : MRAF.cpp                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The MRAF Class used for Proj2                                      
//---------------------------------------------------

#ifndef MRAF_CPP_
#define MRAF_CPP_

#include "mraf.h"

using namespace std;

template <class Object>
Mraf<Object>::Mraf()
{
   // no code
}

template <class Object>
Mraf<Object>::Mraf(const Mraf& mraf)
{
   m_theList = mraf.m_theList;
}

template <class Object>
ListItr<Object> Mraf<Object>::first() const
{
   return m_theList.first();
}

template <class Object>
Mraf<Object>::~Mraf()
{
   makeEmpty();
}

template <class Object>
bool Mraf<Object>::isEmpty() const
{
   return m_theList.isEmpty();
}

template <class Object>
void Mraf<Object>::makeEmpty()
{
   m_theList.makeEmpty();
}

template <class Object>
void Mraf<Object>::insertAtFront(const Object& x)
{
   m_theList.insert(x, m_theList.zeroth());
}

template <class Object>
const Mraf<Object>& Mraf<Object>::operator=(const Mraf& mraf)
{
   if (this != &mraf)
      m_theList = mraf.m_theList;
   return *this;
}

template<class Object>
void Mraf<Object>::remove(const Object& x)
{
   m_theList.remove(x);
}

template<class Object>
ListItr<Object> Mraf<Object>::find(const Object& x)
{
   return m_theList.find(x);
}

template<class Object>
int Mraf<Object>::GetTotal() const
{
   return m_theList.GetTotal();
}

template<class Object>
void Mraf<Object>::ResetTotal()
{
   m_theList.ResetTotal();
}


#endif
