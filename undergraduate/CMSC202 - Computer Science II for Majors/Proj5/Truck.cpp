//---------------------------------------------------
// File       : Truck.cpp
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of Truck Class Used for Proj5
//---------------------------------------------------

#include "Truck.h"

#ifndef _Truck_cpp
#define _Truck_cpp

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         an object
//---------------------------------------
template <class T>
Truck<T>::Truck(int max)
{
   // values initialized
}

//---------------------------------------
// Truck::Deliver
// PreConditions:
//         none
// PostConditions
//         truck holds no boxes
//---------------------------------------
template <class T>
void Truck<T>::Deliver()
{   
   m_items.clear();
   // clears out truck box vector
}

//---------------------------------------
// Truck::GetLog
// PreConditions:
//         none
// PostConditions
//         returns deliverylog
//---------------------------------------
template <class T>
DeliveryLog& Truck<T>::GetLog()
{
   return m_Deliveries;
}

//---------------------------------------
// Truck::GetItem
// PreConditions:
//         valid index value
// PostConditions
//         returns requested box
//---------------------------------------
template <class T>
const T& Truck<T>::GetItem(int i) const
{
   return m_items.at(i);
}

//---------------------------------------
// Truck::operator+=
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
template <class T>
const Truck<T>& Truck<T>::operator+=(const T& item)
{
   m_items.push_back(item);
   // adds box
   return *this;
}

//---------------------------------------
// Truck::NumItems
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
template <class T>
int Truck<T>::NumItems() const
{
   int i = 0;
   unsigned int j = m_items.size();
   i = j;
   return i;
}

//---------------------------------------
// output operator
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
template <class T>
ostream& operator<<(ostream& out, Truck<T>& truck)
{
   out << "Current Load: " 
       << truck.NumItems() 
       << " items" 
       << endl;

   // print current load
   for ( int i = 0; i < truck.NumItems(); i++ )
   {
      out << "Item # "
	  << setw(2)
	  << i + 1 
	  << "  " 
	  << setw(3)
	  << truck.GetItem(i)
	  << endl;
   }
   
   // print delivery log
   out << truck.GetLog();

   return out;
}


#endif
