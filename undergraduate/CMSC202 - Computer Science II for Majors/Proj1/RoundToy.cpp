//---------------------------------------------------
// File       : RoundToy.cpp
// Author     : Patrick Trinkle
// Date       : September 26 2004
// UMBC Email : tri1@umbc.edu
// Project    : 1
// Section    : 0101
// Description: Functions That access the members of 
//              RoundToy  Struct Used for Proj1
//---------------------------------------------------

#include "RoundToy.h"

using namespace std;

//---------------------------------------
// RoundToyDiameter
// PreConditions:
//         the toy needs to have some
//         double as a diamter
// PostConditions
//         it retuns the diameter
//         associated with the toy
//---------------------------------------
double RoundToyDiameter(const RoundToy& toy)
{
   return toy.diameter;
   // simply returns the diameter of the toy
}

//---------------------------------------
// RoundToyColor
// PreConditions:
//         the toy needs to have some
//         valid color as a string
// PostConditions
//         it retuns the color
//         associated with the toy
//---------------------------------------
string RoundToyColor(const RoundToy& toy)
{
   return toy.color;
   // simply returns the color of the toy
}

//---------------------------------------
// RoundToyHoles
// PreConditions:
//         the toy needs to have some
//         valid integer of holes
// PostConditions
//         it retuns the number of holes
//         in the toy
//---------------------------------------
int RoundToyHoles(const RoundToy& toy)
{
   return toy.holes;
   // simply returns the number of holes
}

//---------------------------------------
// RoundToyVolume
// PreConditions:
//         the toy needs to have a valid
//         diameter, needs to be greater
//         than negative 1
// PostConditions
//         it calculates and returns a
//         nonnegative volume
//---------------------------------------
double RoundToyVolume(const RoundToy& toy)
{
   double volume, radius;
   radius = toy.diameter / 2;
   // finds radius with diameter

   volume = ( 4 / 3 ) * PI * ( radius * radius * radius );
   // calculates the volume of a sphere

   return volume;
   // returns the volume of the toy
}

//---------------------------------------
// RoundToyInit
// PreConditions:
//         the toy needs to exist and
//         you need to enter in
//         nonnegative values and a valid
//         color
// PostConditions
//         it sets all the members to the
//         values sent to the function
//---------------------------------------
void RoundToyInit(RoundToy& toy, double diameter, string color, int nrHoles)
{
   toy.diameter = diameter;
   toy.color = color;
   toy.holes = nrHoles;
   // initializes all the members of the new toy structure
}
