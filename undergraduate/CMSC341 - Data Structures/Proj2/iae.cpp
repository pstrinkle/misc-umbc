//---------------------------------------------------                              
// File       : IAE.cpp                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The IAE Class used for Proj2                                      
//---------------------------------------------------


#ifndef IAE_CPP_
#define IAE_CPP_

#include "iae.h"

using namespace std;

template <class Object>
Iae<Object>::Iae()
{
   // no code
}

template <class Object>
Iae<Object>::Iae(const Iae& iae)
{
   m_theList = iae.m_theList;
}

template <class Object>
Iae<Object>::~Iae()
{
   // no code
}

template <class Object>
bool Iae<Object>::isEmpty() const
{
   return m_theList.isEmpty();
}

template <class Object>
void Iae<Object>::makeEmpty()
{
   m_theList.makeEmpty();
}

template <class Object>
void Iae<Object>::insertAtBack(const Object& x)
{
   m_theList.insert(x, m_theList.last());
}

template <class Object>
const Iae<Object>& Iae<Object>::operator=(const Iae& iae)
{
   if (this != &iae)
      m_theList = iae.m_theList;
   return *this;
}

template<class Object>
ListItr<Object> Iae<Object>::find(const Object& x)
{
   return m_theList.find(x);
}

template<class Object>
int Iae<Object>::GetTotal() const
{
   return m_theList.GetTotal();
}

template <class Object>
void Iae<Object>::ResetTotal()
{
   m_theList.ResetTotal();
}

#endif
