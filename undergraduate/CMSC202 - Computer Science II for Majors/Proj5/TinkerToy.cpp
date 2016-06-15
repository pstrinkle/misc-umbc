//---------------------------------------------------
// File       : TinkerToy.cpp
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of TinkerToy Class Used for Proj5
//---------------------------------------------------

#include "TinkerToy.h"
using namespace std;


//---------------------------------------
// Copy Constructor
// PreConditions:
//         none
// PostConditions
//         a TinkerToy object
//---------------------------------------
TinkerToy::TinkerToy(const TinkerToy& rhs)
{
   // no code
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
   // no code
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
   // no code
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
