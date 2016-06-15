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
#include "TinkerToy.h"

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
         tempVolume = GetToy(i) -> Volume();
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
const Box& Box::operator+=(TinkerToy* toy)
{
   // we need to make it copy the toy to which it is referring 
   m_toysinbox.push_back( toy->Clone() );
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
   // print box
   out << setw(3) << box.NumToys() << "    ";
   box.GetToy(0) -> Print();
   return out;
}

//---------------------------------------
// Box::GetToy
// PreConditions:
//         none
// PostConditions
//         None
//---------------------------------------
const TinkerToy* Box::GetToy(int i) const
{
   return m_toysinbox.at(i);
   // returns a base class pointer
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

//---------------------------------------
// Box::Box--Copy Constructor
// PreConditions:
//         none
// PostConditions:
//         none
//---------------------------------------
Box::Box(const Box& rhs)
{
   // set up variables
   m_toysinbox.resize( rhs.m_toysinbox.size() );
   m_length = rhs.m_length;
   m_width = rhs.m_width;
   m_height = rhs.m_height;

   // clone toys from one box to other
   if ( rhs.NumToys() > 0 )
   {
      for ( unsigned int i = 0; i < rhs.NumToys(); i++ )
      {
	 m_toysinbox[i] = rhs.m_toysinbox[i] -> Clone();
      }
   }
}

//---------------------------------------
// Box::operator=
// PreConditions:
//         none
// PostConditions:
//         none
//---------------------------------------
Box& Box::operator=(const Box& rhs)
{
   if ( this != &rhs )
   {
      // change variables
      m_length = rhs.m_length;
      m_width = rhs.m_width;
      m_height = rhs.m_height;

      // clone toys from one box to the other
      for ( unsigned int i = 0; i < NumToys(); i++ )
      {
	 m_toysinbox.at(i) = rhs.m_toysinbox.at(i)->Clone();
      }
   }
   return (*this);
}

//---------------------------------------
// Box::~Box--Destructor
// PreConditions:
//         none
// PostConditions:
//         none
//---------------------------------------
Box::~Box()
{
   for ( unsigned int i = 0; i < NumToys(); i++ )
   {
      delete m_toysinbox.at(i);
   }
   m_toysinbox.clear();
}
