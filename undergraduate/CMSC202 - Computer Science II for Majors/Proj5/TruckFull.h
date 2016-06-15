//---------------------------------------------------
// File       : TruckFull.h
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: The TruckFull Exception Class Template
//              Used for Proj5
//---------------------------------------------------

#ifndef _TruckFull_h
#define _TruckFull_h

#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

template <class T>
class TruckFull
{
   friend ostream& operator<< <>(ostream& out, const TruckFull<T>& exception);
   
  public:
   TruckFull(int max, const string& type, const T& item);

  private:
   int m_maxItems;
   string m_type;
   T m_item;
};

#include "TruckFull.cpp"

#endif
