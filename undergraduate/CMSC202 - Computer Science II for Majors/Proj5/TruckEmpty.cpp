//---------------------------------------------------
// File       : TruckEmpty.cpp
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of TruckEmpty Exception Class 
//              Used for Proj5
//---------------------------------------------------

#include "TruckEmpty.h"

#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         an exception
//---------------------------------------
TruckEmpty::TruckEmpty(int miles, const string& dest, const string& type)
   :m_mileage(miles), m_destination(dest), m_type(type)
{
   // no code
}

//---------------------------------------
// GetMiles()
// PreConditions:
//         none
// PostConditions
//         returns the miles
//---------------------------------------
int TruckEmpty::GetMiles() const
{
   return m_mileage;
}

//---------------------------------------
// What()
// PreConditions:
//         none
// PostConditions
//         returns the information of the
//         exception
//---------------------------------------
string TruckEmpty::What() const
{
   string info;
   info = "Empty Truck ";
   info += m_type;
   info += " destination : ";
   info += m_destination;

   return info;
}
