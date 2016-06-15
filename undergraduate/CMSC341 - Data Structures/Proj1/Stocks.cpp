//---------------------------------------------------
// File       : Stockcs.cpp
// Author     : Patrick Trinkle
// Date       : February 2005
// UMBC Email : tri1@umbc.edu
// Project    : 1
// Section    : 0101
// Description: The Stocks Functions for Proj1
//---------------------------------------------------


#include "Stocks.h"

using namespace std;

ostream& operator<<(ostream& out, const Stocks& stock)
{
   stock.Print(out) << endl;
   return out;
}

ostream& Stocks::Print(ostream& out) const
{
   out << "   " << m_name << " " << m_numUnits << " " << m_buyPrice;
   return out;
}

void Stocks::SetNumUnits(int num)
{
   m_numUnits = num;
}

double Stocks::CalcSellPrice(double buyPrice)
{
   srand(12345);
   double r = 0;
   r = 0.9+0.2*rand()/RAND_MAX;
   return ( buyPrice * r );
}
