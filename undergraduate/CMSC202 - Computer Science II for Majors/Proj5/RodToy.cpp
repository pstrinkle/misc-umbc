//---------------------------------------------------
// File       : RodToy.cpp
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of RodToy Class Used for Proj5
//---------------------------------------------------

#include "TinkerToy.h"
#include "RodToy.h"

using namespace std;


//---------------------------------------
// Destructor
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
RodToy::~RodToy()
{
}

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         a RodToy object
//---------------------------------------
RodToy::RodToy(const string& color, int length)
   :TinkerToy::TinkerToy(color), m_length(length)
{
   // default constructor
}

//---------------------------------------
// RodToy::Clone
// PreConditions:
//         none
// PostConditions
//         a cloned toy
//---------------------------------------
RodToy* RodToy::Clone() const
{
   // clone the toy
   return new RodToy (*this);
}

//---------------------------------------
// RodToy::Print
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
void RodToy::Print() const
{
   cout << GetColor() << " Rod(s) with length " << m_length;
}

//---------------------------------------
// RodToy::Volume
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
double RodToy::Volume() const
{
   // calculate volume and return it

   double volume, length, radius;
   length = m_length;
   radius = ( 0.25 / 2.0 );
   volume = ( PI * radius * radius ) * length;
   return volume;
}

//---------------------------------------
// RodToy::operator=
// PreConditions:
//         none
// PostConditions
//         two identical rodtoy objects
//---------------------------------------
RodToy& RodToy::operator=(const RodToy& rhs)
{
   if ( this != & rhs )
   {
      // set them to be the same
      TinkerToy::operator=(rhs);
      m_length = rhs.m_length;
   }
   return (*this);
}
