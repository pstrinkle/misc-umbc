//---------------------------------------------------
// File       : TruckFull.cpp
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of TruckFull Exception Class
//              Template Used for Proj5
//---------------------------------------------------

#include "TruckFull.h"

#ifndef _TruckFull_cpp
#define _TruckFull_cpp

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         an exception
//---------------------------------------
template <class T>
TruckFull<T>::TruckFull(int max, const string& type, const T& item)
   :m_maxItems(max), m_type(type), m_item(item)
{
   // no code
}

//---------------------------------------
// Output operator
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
template <class T>
ostream& operator<<(ostream& out, const TruckFull<T>& exception)
{
   out << "Maximum items " << exception.m_maxItems;
   out << " on truck of type " << exception.m_type;
   out << " of item " << exception.m_item;
   return out;
}


#endif
