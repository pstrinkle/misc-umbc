//---------------------------------------------------                   
// File       : Proj1Aux.h
// Author     : Patrick Trinkle                                         
// Date       : February 2005                                        
// UMBC Email : tri1@umbc.edu                                           
// Project    : 1
// Section    : 0101
// Description: The Exception Classes used for Proj1                          
//---------------------------------------------------                    


#ifndef _Proj1Aux_h
#define _Proj1Aux_h

#include <string>

using namespace std;

// class for not enough product to sell
class NoneToSell
{
  public:
   NoneToSell(string name = "unspecified");
   const string& Info() const;

  private:
   string m_name;
};

// class for not enough cash to buy
class NotEnoughCash
{
  public:
   NotEnoughCash();
};

#endif
