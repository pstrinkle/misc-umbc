//---------------------------------------------------
// File       : TinkerToy.cpp
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 4
// Section    : 0101
// Description: Functions That access the
//              members of TinkerToy Class Used for Proj4
//---------------------------------------------------

#include "TinkerToy.h"
using namespace std;

// declare and set static variables
int TinkerToy::m_numdes = 0;
int TinkerToy::m_numcon = 0;

//---------------------------------------
// Copy Constructor
// PreConditions:
//         none
// PostConditions
//         a TinkerToy object
//---------------------------------------
TinkerToy::TinkerToy(const TinkerToy& rhs)
{
   // increment construction counter
   m_numcon++;
}

//---------------------------------------
// Destructor
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
TinkerToy::~TinkerToy()
{
   // increment destruction counter
   m_numdes++;
}

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         TinkerToy value set
//---------------------------------------
TinkerToy::TinkerToy(const string& color)
   :m_color(color)
{
   // set values and increment construction counter
   m_numcon++;
}

//---------------------------------------
// TinkerToy::operator=
// PreConditions:
//         none
// PostConditions
//         two identical toy objects
//---------------------------------------
TinkerToy& TinkerToy::operator=(const TinkerToy& rhs)
{
   // set value to be the same
   m_color = rhs.m_color;
   return (*this);
}

//---------------------------------------
// TinkerToy::GetColor
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
string TinkerToy::GetColor() const
{
   // return the color
   return m_color;
}

//---------------------------------------
// TinkerToy::NumConstructed
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
int TinkerToy::NumConstructed()
{
   // returns the construction counter
   return m_numcon;
}

//---------------------------------------
// TinkerToy::NumDestroyed
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
int TinkerToy::NumDestroyed()
{
   // returns the destruction counter
   return m_numdes;
}
