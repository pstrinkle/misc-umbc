//---------------------------------------------------                   
// File       : Inventory.h
// Author     : Patrick Trinkle                                         
// Date       : February 2005                                        
// UMBC Email : tri1@umbc.edu                                           
// Project    : 1
// Section    :   
// Description: The Inventory Class used for Proj1                          
//---------------------------------------------------                    


#ifndef _Inventory_h
#define _Inventory_h

#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

#include "Proj1Aux.h"

using namespace std;

template<class T>
class Inventory
{
  public:
   Inventory(double cash = 0)
      :m_cash(cash)
      {
	 // no code
      };
  
   double GetCash() const
      {
	 return m_cash;
      };

   void SetCash(double cash)
      {
	 m_cash = cash;
      };

   int NumItems() const;

   const Inventory<T>& operator+=(const T& item);

   const Inventory<T>& operator-=(const T& item);

   ostream& Print(ostream& out) const;

  private:
   vector<T> m_items;
   double    m_cash;
};

template<class T>
ostream& operator<<(ostream& out, Inventory<T>& i);

#include "Inventory.cpp"

#endif
