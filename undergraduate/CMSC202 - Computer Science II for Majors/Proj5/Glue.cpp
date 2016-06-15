//---------------------------------------------------
// File       : Glue.cpp
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of Glue Class Used for Proj5
//---------------------------------------------------

#include "Glue.h"


using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         glue
//---------------------------------------
Glue::Glue(const string& type)
   :m_type(type)
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
ostream& operator<<(ostream& out, const Glue& glue)
{
   out << glue.m_type;
   return out;
}
