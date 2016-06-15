//---------------------------------------------------
// File       : PaintCan.cpp
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of PaintCan Class Used for Proj5
//---------------------------------------------------

#include "PaintCan.h"

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         glue
//---------------------------------------
PaintCan::PaintCan(int gallons, const string& color)
   :m_gallons(gallons), m_color(color)
{
   // no code
}

//---------------------------------------
// Output operator
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
ostream& operator<<(ostream& out, const PaintCan& can)
{
   out << can.m_gallons << " Gallons of " << can.m_color << " paint.";
   return out;
}
