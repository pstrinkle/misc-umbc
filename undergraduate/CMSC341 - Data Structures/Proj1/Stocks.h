//---------------------------------------------------                   
// File       : Stocks.h
// Author     : Patrick Trinkle                                         
// Date       : February 2005                                        
// UMBC Email : tri1@umbc.edu                                           
// Project    : 1
// Section    :   
// Description: The Stocks Class used for Proj1                          
//---------------------------------------------------                    


#ifndef _Stocks_h
#define _Stocks_h

#include <string>
#include <iostream>
#include <iomanip>

#include <cstdlib>

using namespace std;

// const double RAND_MAX = 1.1;

class Stocks
{
  public:
   Stocks(string name = "unspecified", int numUnits = 0, double buyPrice = 0)
      :m_name(name), m_numUnits(numUnits), m_buyPrice(buyPrice), m_sellPrice(CalcSellPrice(buyPrice))
      {
	 // no code
      };

   ostream& Print(ostream& out) const;

   const double GetBuyPrice() const
      {
	 return m_buyPrice;
      };
   const double GetSellPrice() const
      {
	 return m_sellPrice;
      };
   const int GetNumUnits() const
      {
	 return m_numUnits;
      };
   const string GetName() const
      {
	 return m_name;
      };
   void SetNumUnits(int num);

  private:
   double CalcSellPrice(double buyPrice);
   string m_name;
   int m_numUnits;
   double m_buyPrice;
   double m_sellPrice;
};

ostream& operator<<(ostream& out, const Stocks& stock);

#endif
