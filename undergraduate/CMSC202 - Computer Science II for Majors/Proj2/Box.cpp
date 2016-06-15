//---------------------------------------------------
// File       : Box.cpp
// Author     : Patrick Trinkle
// Date       : October 13 2004
// UMBC Email : tri1@umbc.edu
// Project    : 2
// Section    : 0101
// Description: Functions That access the
//              members of Box Class Used for Proj1
//---------------------------------------------------

#include "Box.h"
#include "RoundToy.h"

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         a box with initialized
//         dimensions
//---------------------------------------
Box::Box(int length, int width, int height)
   :m_length( length ), m_width( width ), m_height ( height )
{
   // inititalizes all the members of the new box structure
}

//---------------------------------------
// Box::Unused
// PreConditions:
//         none
// PostConditions
//         returns the unused volume of
//         the box structure
//---------------------------------------
double Box::Unused() const
{
   double boxVolume, volume, tempVolume, unusedVolume;
   boxVolume = m_length * m_width * m_height;
   //finds total box volume

   unsigned int numToys;
   volume = 0;
   numToys = m_toysinbox.size();
   // set up the for loop

   if ( numToys != 0 )
   {
      unsigned int i;

      for ( i = 0; i < numToys; i++ )
      {
         tempVolume = m_toysinbox.at(i).Volume();
         volume = volume + tempVolume;
         // takes the volume of each toy and totals them all up
      }

      unusedVolume =  boxVolume - volume;
      // calculates the leftover volume and then returns it in the next line

      return unusedVolume;

   }

   return boxVolume;
}

//---------------------------------------
// Box::Store
// PreConditions:
//         none
// PostConditions
//         None
//---------------------------------------
bool Box::Store(const RoundToy& toy)
{
   double unusedVolume, toyVolume, toyDiameter, toyRadius;
   unusedVolume = Unused();
   toyDiameter = toy.Diameter();
   toyRadius = toyDiameter / 2;
   toyVolume = ( static_cast<double>( 4 ) / static_cast<double>( 3 ) ) * PI * ( toyRadius * toyRadius * toyRadius );

   // gets the unused volume of the box and the volume of the toy in queue


   if ( toyVolume <= unusedVolume )
   {
      m_toysinbox.push_back(toy);
      // the toy is put in the box if it will fit volume wise
   }
   else
   {
      return false;
      // if this action is not completed a boolean false is returned otherwise it is true
   }

   return true;
}

//---------------------------------------
// Box::GetToy
// PreConditions:
//         none
// PostConditions
//         None
//---------------------------------------
const RoundToy& Box::GetToy(int i) const
{
   return m_toysinbox.at(i);
   // returns a reference to a toy for use in other classes
}

//---------------------------------------
// Box::NumToys
// PreConditions:
//         none
// PostConditions
//         None
//---------------------------------------
unsigned int Box::NumToys() const
{
   return m_toysinbox.size();
   // returns the number of toys in a box
}
