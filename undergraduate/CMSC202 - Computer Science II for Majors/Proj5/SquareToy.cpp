//---------------------------------------------------
// File       : SquareToy.cpp
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of SquareToy Class Used for Proj5
//---------------------------------------------------

#include "TinkerToy.h"
#include "SquareToy.h"

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         a SquareToy object
//---------------------------------------
SquareToy::SquareToy(const string& color, int side, int nrHoles)
   :TinkerToy::TinkerToy(color), m_side(side), m_nrHoles(nrHoles)
{
   // default constructor
}

//---------------------------------------
// SquareToy::Clone
// PreConditions:
//         none
// PostConditions
//         a cloned toy
//---------------------------------------
SquareToy* SquareToy::Clone() const
{
   return new SquareToy (*this);
}

//---------------------------------------
// SquareToy::operator=
// PreConditions:
//         none
// PostConditions
//         two identical squaretoy objects
//---------------------------------------
SquareToy& SquareToy::operator=(const SquareToy& rhs)
{
      if ( this != & rhs )
      {
	 // make identical
	 TinkerToy::operator=(rhs);
	 m_side = rhs.m_side;
	 m_nrHoles = rhs.m_nrHoles;
      }
      return (*this);
}

//---------------------------------------
// SquareToy::Print
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
void SquareToy::Print() const
{
   cout << GetColor() 
	<< " Square Toy(s) " 
	<< m_side 
	<< " x " 
	<< m_side 
	<< " x " 
	<< m_side 
	<< " with " 
	<< m_nrHoles 
	<< " holes";
}

//---------------------------------------
// SquareToy::Volume
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
double SquareToy::Volume() const
{
   // calculate the volume
   double volume, side;
   side = m_side;
   volume = m_side * m_side * m_side;
   return volume;
}

//---------------------------------------
// Destructor
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
SquareToy::~SquareToy()
{
}
