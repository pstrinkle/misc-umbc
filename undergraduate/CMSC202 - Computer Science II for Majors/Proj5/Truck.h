//---------------------------------------------------
// File       : Truck.h
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Truck Class Template Used for Proj5
//---------------------------------------------------

#ifndef _Truck_h
#define _Truck_h

#include "DeliveryLog.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

template <class T>
class Truck
{
  public:
   Truck(int max = 1);
   void Deliver();
   const T& GetItem(int i) const;
   int NumItems() const;

   // retrieve the log
   DeliveryLog& GetLog();

   // operator +=
   const Truck<T>& operator+=(const T& item);

  private:
   vector<T> m_items;
   DeliveryLog m_Deliveries;
};

template <class T>
ostream& operator<<(ostream& out, Truck<T>& truck);


#include "Truck.cpp"

#endif
