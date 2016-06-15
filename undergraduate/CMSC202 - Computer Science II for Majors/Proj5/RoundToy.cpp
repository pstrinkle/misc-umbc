//---------------------------------------------------
// File       : RoundToy.cpp
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the members of 
//              RoundToy Class Used for Proj5
//---------------------------------------------------

#include "RoundToy.h"

using namespace std;

//---------------------------------------
// RoundToy::Clone
// PreConditions:
//         none
// PostConditions
//         a cloned toy
//---------------------------------------
RoundToy* RoundToy::Clone() const
{
   //make clone
   return new RoundToy(*this);
}

//---------------------------------------
// RounddToy::Print
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
void RoundToy::Print() const
{
   cout << GetColor() << " Round Toy(s) with diameter " << m_diameter 
	<< " and " << m_nrHoles << " holes";
}

//---------------------------------------
// RoundToy::operator=
// PreConditions:
//         none
// PostConditions
//         two identical roundtoy objects
//---------------------------------------
RoundToy& RoundToy::operator=(const RoundToy& rhs)
{
   if ( this != & rhs )
   {
      // make identical!
      TinkerToy::operator=(rhs);
      m_diameter = rhs.m_diameter;
      m_nrHoles = rhs.m_nrHoles;
   }   
   return (*this);
}

//---------------------------------------
// Destructor
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
RoundToy::~RoundToy()
{
}

//---------------------------------------
// RoundToy::Volume
// PreConditions:
//         diameter needs to be greater
//         than -1
// PostConditions
//         it calculates and returns a
//         nonnegative volume
//---------------------------------------
double RoundToy::Volume() const
{
   double volume, radius;
   radius = m_diameter / 2;
   // finds radius with diameter

   volume = ( 4.0 / 3.0 ) * PI * ( radius * radius * radius );
   // calculates the volume of a sphere

   return volume;
   // returns the volume of the toy
}

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         it sets all the members to the
//         values sent to the function
//---------------------------------------
RoundToy::RoundToy(float diameter, const string& color, int nrHoles)
   :TinkerToy::TinkerToy(color), m_diameter( diameter ), m_nrHoles ( nrHoles )
{
   // initializes all the members of the new toy structure
}
