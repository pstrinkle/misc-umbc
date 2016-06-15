//---------------------------------------------------
// File       : Electronics.cpp
// Author     : Patrick Trinkle
// Date       : February 2005
// UMBC Email : tri1@umbc.edu
// Project    : 1
// Section    : 0101
// Description: The Electronics Functions for Proj1
//---------------------------------------------------


#include "Electronics.h"

using namespace std;

ostream& operator<<(ostream& out, const Electronics& elect)
{
   elect.Print(out);
   return out;
}

ostream& Electronics::Print(ostream& out) const
{
   out << "   " << m_name << " " << m_numUnits << " " << m_buyPrice;
   return out;
}

void Electronics::SetNumUnits(int num)
{
   m_numUnits = num;
}

double Electronics::CalcSellPrice(double buyPrice)
{
   return ( buyPrice * 1.1 );
}
