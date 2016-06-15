//---------------------------------------------------
// File       : Truck.cpp
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 3
// Section    : 0101
// Description: Functions That access the
//              members of Truck Class Used for Proj3
//---------------------------------------------------

#include "Truck.h"
#include "Box.h"
#include "RoundToy.h"
#include "DeliveryLog.h"

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         an object
//---------------------------------------
Truck::Truck()
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
void Truck::Deliver()
{   
   m_boxesintruck.clear();
   // clears out truck box vector
}

//---------------------------------------
// Truck::GetLog
// PreConditions:
//         none
// PostConditions
//         returns deliverylog
//---------------------------------------
DeliveryLog& Truck::GetLog()
{
   return m_Deliveries;
}

//---------------------------------------
// Truck::GetBox
// PreConditions:
//         valid index value
// PostConditions
//         returns requested box
//---------------------------------------
const Box& Truck::GetBox(int i) const
{
   return m_boxesintruck.at(i);
}

//---------------------------------------
// Truck::operator+=
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
const Truck Truck::operator+=(Box& box)
{
   m_boxesintruck.push_back(box);
   // adds box

   return *this;
}

//---------------------------------------
// output operator
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
ostream& operator<<(ostream& out, Truck& truck)
{
   out << "Current Load: " 
       << truck.NumBoxes() 
       << " boxes" 
       << endl;

   // print current load
   for ( int i = 0; i < truck.NumBoxes(); i++ )
   {
      out << "Box # " 
	  << i + 1 
	  << "  " 
	  << setw(3)
	  << truck.GetBox(i)
	  << endl;
   }
   
   // print delivery log
   out << truck.GetLog();

   return out;
}

//---------------------------------------
// Truck::NumBoxes
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
int Truck::NumBoxes() const
{
   int i = 0;
   unsigned int j = m_boxesintruck.size();
   i = j;
   return i;
}
