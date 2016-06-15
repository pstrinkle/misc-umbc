//---------------------------------------------------
// File       : Box.cpp
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 3
// Section    : 0101
// Description: Functions That access the
//              members of Box Class Used for Proj3
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
   boxVolume = GetLength() * GetWidth() * GetHeight();

   volume = 0;
   // set up the for loop

   if ( NumToys() == 0 )
   {
      return boxVolume;
   }
   else
   {
      for ( unsigned int i = 0; i < NumToys(); i++ )
      {
         tempVolume = GetToy(i).Volume();
         volume += tempVolume;
         // takes the volume of each toy and totals them all up
      }

      unusedVolume =  boxVolume - volume;
      // calculates the leftover volume and then returns it in the next line
      return unusedVolume;

   }

   return boxVolume;
}

//---------------------------------------
// Box::operator+=
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
const Box Box::operator+=(const RoundToy& toy)
{
   m_toysinbox.push_back(toy);
   // added toy to box
   
   return *this;
}

//---------------------------------------
// Output operator
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
ostream& operator<<(ostream& out, const Box& box)
{
   // print boxes
   out << box.NumToys() << "    "
       << box.GetToy(0).Color();
   return out;
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

//---------------------------------------
// Box::GetHeight
// PreConditions:
//         none
// PostConditions
//         None
//---------------------------------------
int Box::GetHeight() const
{
   return m_height;
}

//---------------------------------------
// Box::GetLength
// PreConditions:
//         none
// PostConditions
//         None
//---------------------------------------
int Box::GetLength() const
{
   return m_length;
}

//---------------------------------------
// Box::GetWidth
// PreConditions:
//         none
// PostConditions
//         None
//---------------------------------------
int Box::GetWidth() const
{
   return m_width;
}
