//---------------------------------------------------
// File       : RoundToy.cpp
// Author     : Patrick Trinkle
// Date       : October 13 2004
// UMBC Email : tri1@umbc.edu
// Project    : 2
// Section    : 0101
// Description: Functions That access the members of 
//              RoundToy Class Used for Proj2
//---------------------------------------------------

#include "RoundToy.h"

using namespace std;

//---------------------------------------
// RoundToy::Diameter
// PreConditions:
//         none
// PostConditions
//         it retuns the diameter
//         associated with the toy
//---------------------------------------
double RoundToy::Diameter() const
{
   return m_diameter;
   // simply returns the diameter of the toy
}

//---------------------------------------
// RoundToy::Color
// PreConditions:
//         none
// PostConditions
//         it retuns the color
//         associated with the toy
//---------------------------------------
string RoundToy::Color() const
{
   return m_color;
   // simply returns the color of the toy
}

//---------------------------------------
// RoundToy::Holes
// PreConditions:
//         none
// PostConditions
//         it retuns the number of holes
//         in the toy
//---------------------------------------
int RoundToy::Holes() const
{
   return m_holes;
   // simply returns the number of holes
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

   volume = ( 4 / 3 ) * PI * ( radius * radius * radius );
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
RoundToy::RoundToy(double diameter, string& color, int nrHoles)
   :m_diameter( diameter ), m_color( color ), m_holes ( nrHoles )
{
   // initializes all the members of the new toy structure
}
